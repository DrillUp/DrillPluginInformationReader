#include "stdafx.h"
#include "drillplugininformationreader.h"

#include "about/w_SoftwareAbout.h"
#include "birthDayTip/w_SoftwareBirthDayTip.h"
#include "Source/ProjectModule/storageGlobal/s_IniManager.h"
#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/InformationModule/pluginListPart/p_PluginListPart.h"
#include "Source/InformationModule/commandSearcherPart/p_CommandSearcherPart.h"


/*
-----==========================================================-----
		类：		主窗体.cpp
		作者：		drill_up
		所属模块：	主窗体模块
		功能：		程序进入后的主控制窗口。
					
-----==========================================================-----
*/
DrillPluginInformationReader::DrillPluginInformationReader(QWidget *parent)
	: QMainWindow(parent)
{
	this->m_inited = false;
	DrillPluginInformationReader::cur_instance = this;
	ui.setupUi(this);
	this->_init();
}

DrillPluginInformationReader::~DrillPluginInformationReader(){
}


/*-------------------------------------------------
		单例
*/
DrillPluginInformationReader* DrillPluginInformationReader::cur_instance = NULL;
DrillPluginInformationReader* DrillPluginInformationReader::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new DrillPluginInformationReader(NULL);
	}
	return cur_instance;
}
/*-------------------------------------------------
		初始化
*/
void DrillPluginInformationReader::_init() {

	//-----------------------------------
	//----最大化/最小化
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	flags |= Qt::WindowMaximizeButtonHint;
	flags |= Qt::WindowMinimizeButtonHint;
	this->setWindowFlags(flags);

	//-----------------------------------
	//----ui初始化
	S_RmmvDataContainer::getInstance();
	S_PluginDataContainer::getInstance();
	S_InformationDataContainer::getInstance();
	S_LinkDirector::getInstance();

	//-----------------------------------
	//----ui初始化
	this->m_P_InformationPart = new P_InformationPart(ui.widget_information);
	QVBoxLayout* layout = new QVBoxLayout(ui.widget_information);
	layout->setMargin(6);
	layout->addWidget(this->m_P_InformationPart);

	this->m_tip = new W_LoadingTip("插件读取中...", this);

	// > 字体
	//ui.main_widget->setStyleSheet("font: 75 9pt \"黑体\";");
	ui.main_widget->setStyleSheet("font: 75 9pt;");		//用默认的宋体+缩小粗体

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_rmmv, &QToolButton::clicked, this, &DrillPluginInformationReader::btn_selectProject);
	connect(ui.toolButton_Import, &QToolButton::clicked, this, &DrillPluginInformationReader::btn_importProject);
	connect(ui.toolButton_userManual, &QToolButton::clicked, this, &DrillPluginInformationReader::openUserManual);
	connect(ui.toolButton_about, &QToolButton::clicked, this, &DrillPluginInformationReader::openAbout);

	//qDebug() << S_LinkDirector::getInstance()->getDocDir();
	//qDebug() << S_LinkDirector::getInstance()->getDataAllDocDirName();

	// > UI读取
	this->ui_loadConfig();
	this->refreshNav();
	this->setWindowTitle(QString("插件信息查看器") + DRILL_VERSION + "（DrillPluginInformationReader）");

	// > UI读取后 - 自动导入工程
	if (this->m_temp_data.isNull() == false &&
		this->m_temp_data.isProjectExist() == true &&
		ui.checkBox_autoLoad->isChecked()){
		this->btn_importProject();
	}

	this->m_inited = true;


	// > 生日彩蛋
	W_SoftwareBirthDayTip d(this);
	if (d.isInBirthDay()){
		d.exec();
	}
}

/* --------------------------------------------------------------
		控件 - 显示指定插件详细信息
*/
void DrillPluginInformationReader::showPluginDetail(QString plugin_name){
	this->m_P_InformationPart->showPluginDetail(plugin_name);
}
/* --------------------------------------------------------------
		控件 - 刷新导航栏内容
*/
void DrillPluginInformationReader::refreshNav(){

	if (this->m_temp_data.isNull() || this->m_temp_data.isProjectExist() == false){
		ui.lineEdit->setText("");
		ui.toolButton_Import->setEnabled(false);
		ui.widget_information->setEnabled(false);	//（取消选择后强制置灰）
	}else{
		ui.lineEdit->setText(this->m_temp_data.getName());
		ui.toolButton_Import->setEnabled(true);
	}
}
/* --------------------------------------------------------------
		控件 - 用户手册
*/
void DrillPluginInformationReader::openUserManual() {
	QString sPath = qApp->applicationDirPath();

	QString docx = sPath + "/help/关于插件信息查看器.docx";
	if (QFileInfo(docx).exists()){
		QDesktopServices::openUrl(QUrl("file:/" + docx)); 
	}else{
		QMessageBox::warning(this, "错误", "文档\"关于插件信息查看器.docx\"不见了。", QMessageBox::Yes);
	}

}
/* --------------------------------------------------------------
		控件 - 关于...
*/
void DrillPluginInformationReader::openAbout() {
	W_SoftwareAbout d(this);
	d.exec();
}


/*-------------------------------------------------
		工程 - 选择工程
*/
void DrillPluginInformationReader::btn_selectProject(){
	C_RmmvProjectData temp = C_RmmvProjectData::callRmmvSelectDialog();
	if (temp.isNull()){ return; }

	this->m_temp_data = temp;
	this->refreshNav();

	// > 自动导入工程
	if (this->m_temp_data.isNull() == false && 
		this->m_temp_data.isProjectExist() == true && 
		ui.checkBox_autoLoad->isChecked()){
		this->btn_importProject();
	}
}
/*-------------------------------------------------
		工程 - 导入工程
*/
void DrillPluginInformationReader::btn_importProject(){
	this->m_tip->show();

	// > 标题修改
	this->setWindowTitle(QString("插件信息查看器") + DRILL_VERSION + "（DrillPluginInformationReader） - " + this->m_temp_data.getName());
	ui.widget_information->setEnabled(true);
	
	// > 全局工程参数变化
	S_RmmvDataContainer::getInstance()->modify(this->m_temp_data);

	// > 读取插件文件
	QFileInfo plugin_info = S_RmmvDataContainer::getInstance()->getRmmvFile_PluginsData();
	QFile plugin_file(plugin_info.absoluteFilePath());
	if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "错误", "未找到plugins.js文件。", QMessageBox::Yes);
		return;
	}
	QString plugin_context = plugin_file.readAll();
	
	// > 全部数据初始化
	S_PluginDataContainer::getInstance()->loadPluginData(plugin_context);
	S_InformationDataContainer::getInstance()->loadAllAnnotationData();
	plugin_file.close(); 

	// > 强制刷新
	this->m_P_InformationPart->m_p_pluginListPart->rebuildTable();	

	this->m_tip->close();
}



/* --------------------------------------------------------------
		事件 - 窗口切换大小事件
*/
void DrillPluginInformationReader::resizeEvent(QResizeEvent *event){
	if (this->m_inited == false){ return; }

	QSize size = event->size();
	if (size.width() + 100 < QApplication::desktop()->width() &&
		size.height() + 80 < QApplication::desktop()->height()){
		this->m_last_uiSize = size;		//（最大化时不存值，也不存过大的值）
	}

	// > 刷新插件列表的目录列
	if (this->m_P_InformationPart &&
		this->m_P_InformationPart->m_p_pluginListPart ){
		this->m_P_InformationPart->m_p_pluginListPart->refreshHorizontalSize(this->geometry().width() - 120);
	}

	event->accept();
}
/* --------------------------------------------------------------
		事件 - 窗口关闭事件（点击关闭按钮）
*/
void DrillPluginInformationReader::closeEvent(QCloseEvent *event){

	// > UI保存
	this->ui_saveConfig();

	event->accept();
}

/* --------------------------------------------------------------
		窗口 - 用户自定义UI读取
*/
void DrillPluginInformationReader::ui_loadConfig(){

	// > 窗口高宽
	QString ww = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Width");
	QString hh = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Height");
	if (ww != "" && hh != "" && ww.toInt() >0 && hh.toInt() >0){
		this->resize(ww.toInt(), hh.toInt());
	}

	// > 窗口位置（暂不用）
	//QString xx = S_IniManager::getInstance()->getConfig("PIR_MainWindow_X");
	//QString yy = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Y");
	//if (xx != "" && yy != ""){
	//	this->move(xx.toInt(), yy.toInt());
	//}

	// > 最大化
	QString config = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Maximized");
	if (config == "true"){
		this->showMaximized();
	}

	// > 自动读取的勾选项
	QString config2 = S_IniManager::getInstance()->getConfig("PIR_AutoLoad");
	ui.checkBox_autoLoad->setChecked(config2 == "true");

	// > 子控件的UI读取
	if (this->m_P_InformationPart != nullptr){
		this->m_P_InformationPart->m_p_pluginListPart->ui_loadConfig();
		this->m_P_InformationPart->m_p_commandSearcherPart->ui_loadConfig();
	}

	// > 【工程数据读取 - 全局】
	QString project_str = S_IniManager::getInstance()->getConfig("PIR_Project");
	if (project_str != ""){
		QJsonDocument jsonDocument = QJsonDocument::fromJson(project_str.toUtf8());
		QJsonObject project_obj = jsonDocument.object();
		S_RmmvDataContainer::getInstance()->setAllDataFromJsonObject(project_obj);

		this->m_temp_data = S_RmmvDataContainer::getInstance()->getRmmvProjectData();
	}
}
/* --------------------------------------------------------------
		窗口 - 用户自定义UI存储
*/
void DrillPluginInformationReader::ui_saveConfig(){

	// > 窗口高宽
	S_IniManager::getInstance()->setConfig("PIR_MainWindow_Width",QString::number(this->m_last_uiSize.width()));
	S_IniManager::getInstance()->setConfig("PIR_MainWindow_Height", QString::number(this->m_last_uiSize.height()));

	// > 窗口位置（暂不用）
	//S_IniManager::getInstance()->setConfig("PIR_MainWindow_X", QString::number(this->x()));
	//S_IniManager::getInstance()->setConfig("PIR_MainWindow_Y", QString::number(this->y()));

	// > 最大化
	if (this->isMaximized() == true){
		S_IniManager::getInstance()->setConfig("PIR_MainWindow_Maximized", "true");
	}else{
		S_IniManager::getInstance()->setConfig("PIR_MainWindow_Maximized", "false");
	}

	// > 自动读取的勾选项
	if (ui.checkBox_autoLoad->isChecked() == true){
		S_IniManager::getInstance()->setConfig("PIR_AutoLoad", "true");
	}else{
		S_IniManager::getInstance()->setConfig("PIR_AutoLoad", "false");
	}

	// > 子控件的UI存储
	if (this->m_P_InformationPart != nullptr){
		this->m_P_InformationPart->m_p_pluginListPart->ui_saveConfig();
		this->m_P_InformationPart->m_p_commandSearcherPart->ui_saveConfig();
	}

	// > 【工程数据存储 - 全局】
	QJsonObject project_obj = S_RmmvDataContainer::getInstance()->getAllDataOfJsonObject();
	S_IniManager::getInstance()->setConfig("PIR_Project", QJsonDocument(project_obj).toJson(QJsonDocument::Compact));
}