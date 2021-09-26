#include "stdafx.h"
#include "drillplugininformationreader.h"

#include "Source/ProjectModule/storageGlobal/s_IniManager.h"
#include "about/w_SoftwareAbout.h"

/*
-----==========================================================-----
		�ࣺ		������.cpp
		���ߣ�		drill_up
		����ģ�飺	������ģ��
		���ܣ�		��������������ƴ��ڡ�
					
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
		����
*/
DrillPluginInformationReader* DrillPluginInformationReader::cur_instance = NULL;
DrillPluginInformationReader* DrillPluginInformationReader::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new DrillPluginInformationReader(NULL);
	}
	return cur_instance;
}
/*-------------------------------------------------
		��ʼ��
*/
void DrillPluginInformationReader::_init() {

	//-----------------------------------
	//----���/��С��
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	flags |= Qt::WindowMaximizeButtonHint;
	flags |= Qt::WindowMinimizeButtonHint;
	this->setWindowFlags(flags);

	//-----------------------------------
	//----ui��ʼ��
	S_RmmvDataContainer::getInstance();

	// > UI��ȡ
	this->ui_loadConfig();
	this->refreshNav();

	//-----------------------------------
	//----ui��ʼ��
	this->m_P_InformationPart = new P_InformationPart(ui.widget_information);
	QVBoxLayout* layout = new QVBoxLayout(ui.widget_information);
	layout->setMargin(6);
	layout->addWidget(this->m_P_InformationPart);

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_rmmv, &QToolButton::clicked, this, &DrillPluginInformationReader::btn_selectProject);
	connect(ui.toolButton_Import, &QToolButton::clicked, this, &DrillPluginInformationReader::btn_importProject);
	connect(ui.toolButton_userManual, &QToolButton::clicked, this, &DrillPluginInformationReader::openUserManual);
	connect(ui.toolButton_about, &QToolButton::clicked, this, &DrillPluginInformationReader::openAbout);

}

/* --------------------------------------------------------------
		�ؼ� - ˢ�µ���������
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
		�ؼ� - �û��ֲ�
*/
void DrillPluginInformationReader::openUserManual() {
	QString sPath = qApp->applicationDirPath();

	QString docx = sPath + "/help/���ڲ����Ϣ��ȡ��.docx";
	if (QFileInfo(docx).exists()){
		QDesktopServices::openUrl(QUrl("file:/" + docx)); 
	}else{
		QMessageBox::warning(this, "����", "�ĵ�\"���ڲ����Ϣ��ȡ��.docx\"�����ˡ�", QMessageBox::Yes);
	}

}
/* --------------------------------------------------------------
		�ؼ� - ����...
*/
void DrillPluginInformationReader::openAbout() {
	W_SoftwareAbout d(this);
	d.exec();
}


/*-------------------------------------------------
		���� - ѡ�񹤳�
*/
void DrillPluginInformationReader::btn_selectProject(){
	C_RmmvProjectData temp = this->callRmmvSelect();
	if (temp.isNull()){ return; }

	this->m_temp_data = temp;
	this->refreshNav();
}
/*-------------------------------------------------
		���� - ���빤��
*/
void DrillPluginInformationReader::btn_importProject(){

	// > �����޸�
	this->setWindowTitle("�����Ϣ��ȡ����DrillPluginInformationReader�� - " + this->m_temp_data.getName());
	
	// > ȫ�ֹ��̲����仯
	S_RmmvDataContainer::getInstance()->modify(this->m_temp_data);
}

/*-------------------------------------------------
		���� - ѡ��rmmv����
*/
C_RmmvProjectData DrillPluginInformationReader::callRmmvSelect(){
	QFileDialog fd;
	fd.setWindowTitle("��rmmv����");
	fd.setAcceptMode(QFileDialog::AcceptOpen);		//�Ի������ͣ���/���棩����������ļ�������ʾ��
	fd.setDirectory(".");							//Ĭ��Ŀ¼
	fd.setNameFilters(QStringList()					//�ļ���ʽ
		<< "rmmv�����ļ�(*.rpgproject)"
		);
	fd.setViewMode(QFileDialog::Detail);

	if (fd.exec() == QDialog::Accepted) {
		if (fd.selectedFiles().empty()) {
			//��û��ѡ���ļ�����������
			return C_RmmvProjectData();
		}
		QString file_path = fd.selectedFiles().at(0);

		C_RmmvProjectData data = C_RmmvProjectData();
		data.initFromFile(file_path);
		return data;
	}
	else {
		//������رջ���ȡ�������������
		return C_RmmvProjectData();
	}
}


/* --------------------------------------------------------------
		�¼� - �����л���С�¼�
*/
void DrillPluginInformationReader::resizeEvent(QResizeEvent *event){

	QSize size = event->size();
	if (size.width() + 100 < QApplication::desktop()->width() &&
		size.height() + 80 < QApplication::desktop()->height()){
		this->m_last_uiSize = size;		//�����ʱ����ֵ��Ҳ��������ֵ��
	}

	event->accept();
}
/* --------------------------------------------------------------
		�¼� - ���ڹر��¼�������رհ�ť��
*/
void DrillPluginInformationReader::closeEvent(QCloseEvent *event){

	// > UI����
	this->ui_saveConfig();

	event->accept();
}

/* --------------------------------------------------------------
		���� - �û��Զ���UI��ȡ
*/
void DrillPluginInformationReader::ui_loadConfig(){

	// > ���ڸ߿�
	QString ww = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Width");
	QString hh = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Height");
	if (ww != "" && hh != "" && ww.toInt() >0 && hh.toInt() >0){
		this->resize(ww.toInt(), hh.toInt());
	}

	// > ����λ�ã��ݲ��ã�
	//QString xx = S_IniManager::getInstance()->getConfig("PIR_MainWindow_X");
	//QString yy = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Y");
	//if (xx != "" && yy != ""){
	//	this->move(xx.toInt(), yy.toInt());
	//}

	// > ���
	QString config = S_IniManager::getInstance()->getConfig("PIR_MainWindow_Maximized");
	if (config == "true"){
		this->showMaximized();
	}

	// > ���������ݶ�ȡ - ȫ�֡�
	QString project_str = S_IniManager::getInstance()->getConfig("PIR_Project");
	if (project_str != ""){
		QJsonDocument jsonDocument = QJsonDocument::fromJson(project_str.toUtf8());
		QJsonObject project_obj = jsonDocument.object();
		S_RmmvDataContainer::getInstance()->setAllDataFromJsonObject(project_obj);

		this->m_temp_data = S_RmmvDataContainer::getInstance()->getRmmvProjectData();
	}
}
/* --------------------------------------------------------------
		���� - �û��Զ���UI�洢
*/
void DrillPluginInformationReader::ui_saveConfig(){

	// > ���ڸ߿�
	S_IniManager::getInstance()->setConfig("PIR_MainWindow_Width",QString::number(this->m_last_uiSize.width()));
	S_IniManager::getInstance()->setConfig("PIR_MainWindow_Height", QString::number(this->m_last_uiSize.height()));

	// > ����λ�ã��ݲ��ã�
	//S_IniManager::getInstance()->setConfig("PIR_MainWindow_X", QString::number(this->x()));
	//S_IniManager::getInstance()->setConfig("PIR_MainWindow_Y", QString::number(this->y()));

	// > ���
	if (this->isMaximized() == true){
		S_IniManager::getInstance()->setConfig("PIR_MainWindow_Maximized", "true");
	}else{
		S_IniManager::getInstance()->setConfig("PIR_MainWindow_Maximized", "false");
	}

	// > ���������ݴ洢 - ȫ�֡�
	QJsonObject project_obj = S_RmmvDataContainer::getInstance()->getAllDataOfJsonObject();
	S_IniManager::getInstance()->setConfig("PIR_Project", QJsonDocument(project_obj).toJson(QJsonDocument::Compact));
}