#include "stdafx.h"
#include "drillplugininformationreader.h"

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
	//----�¼���
	connect(ui.toolButton_userManual, &QToolButton::clicked, this, &DrillPluginInformationReader::openUserManual);
	connect(ui.toolButton_about, &QToolButton::clicked, this, &DrillPluginInformationReader::openAbout);

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