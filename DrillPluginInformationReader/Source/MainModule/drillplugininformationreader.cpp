#include "stdafx.h"
#include "drillplugininformationreader.h"

#include "Source/ProjectModule/storageGlobal/s_IniManager.h"
#include "about/w_SoftwareAbout.h"

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

	// > UI读取
	this->ui_loadConfig();
	this->refreshNav();

	//-----------------------------------
	//----ui初始化
	this->m_P_InformationPart = new P_InformationPart(ui.widget_information);
	QVBoxLayout* layout = new QVBoxLayout(ui.widget_information);
	layout->setMargin(6);
	layout->addWidget(this->m_P_InformationPart);

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_rmmv, &QToolButton::clicked, this, &DrillPluginInformationReader::btn_selectProject);
	connect(ui.toolButton_Import, &QToolButton::clicked, this, &DrillPluginInformationReader::btn_importProject);
	connect(ui.toolButton_userManual, &QToolButton::clicked, this, &DrillPluginInformationReader::openUserManual);
	connect(ui.toolButton_about, &QToolButton::clicked, this, &DrillPluginInformationReader::openAbout);

}

/* --------------------------------------------------------------
		控件 - 刷新导航栏内容
*/
void DrillPluginInformationReader::refreshNav(){

	if (this->m_temp_data.isNull() || this->m_temp_data.isProjectExist() == false){
		ui.lineEdit->setText("");
		ui.toolButton_Import->setEnabled(false);
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

	QString docx = sPath + "/help/关于插件信息读取器.docx";
	if (QFileInfo(docx).exists()){
		QDesktopServices::openUrl(QUrl("file:/" + docx)); 
	}else{
		QMessageBox::warning(this, "错误", "文档\"关于插件信息读取器.docx\"不见了。", QMessageBox::Yes);
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
	C_RmmvProjectData temp = this->callRmmvSelect();
	if (temp.isNull()){ return; }

	this->m_temp_data = temp;
	this->refreshNav();
}
/*-------------------------------------------------
		工程 - 导入工程
*/
void DrillPluginInformationReader::btn_importProject(){

	// > 标题修改
	this->setWindowTitle("插件信息读取器（DrillPluginInformationReader） - " + this->m_temp_data.getName());
	
	// > 全局工程参数变化
	S_RmmvDataContainer::getInstance()->modify(this->m_temp_data);
}

/*-------------------------------------------------
		工程 - 选择rmmv工程
*/
C_RmmvProjectData DrillPluginInformationReader::callRmmvSelect(){
	QFileDialog fd;
	fd.setWindowTitle("打开rmmv工程");
	fd.setAcceptMode(QFileDialog::AcceptOpen);		//对话框类型（打开/保存）（保存会有文件覆盖提示）
	fd.setDirectory(".");							//默认目录
	fd.setNameFilters(QStringList()					//文件格式
		<< "rmmv工程文件(*.rpgproject)"
		);
	fd.setViewMode(QFileDialog::Detail);

	if (fd.exec() == QDialog::Accepted) {
		if (fd.selectedFiles().empty()) {
			//（没有选择文件进入的情况）
			return C_RmmvProjectData();
		}
		QString file_path = fd.selectedFiles().at(0);

		C_RmmvProjectData data = C_RmmvProjectData();
		data.initFromFile(file_path);
		return data;
	}
	else {
		//（点击关闭或者取消操作的情况）
		return C_RmmvProjectData();
	}
}


/* --------------------------------------------------------------
		事件 - 窗口切换大小事件
*/
void DrillPluginInformationReader::resizeEvent(QResizeEvent *event){

	QSize size = event->size();
	if (size.width() + 100 < QApplication::desktop()->width() &&
		size.height() + 80 < QApplication::desktop()->height()){
		this->m_last_uiSize = size;		//（最大化时不存值，也不存过大的值）
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

	// > 【工程数据存储 - 全局】
	QJsonObject project_obj = S_RmmvDataContainer::getInstance()->getAllDataOfJsonObject();
	S_IniManager::getInstance()->setConfig("PIR_Project", QJsonDocument(project_obj).toJson(QJsonDocument::Compact));
}