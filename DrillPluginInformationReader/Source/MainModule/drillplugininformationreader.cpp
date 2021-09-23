#include "stdafx.h"
#include "drillplugininformationreader.h"

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
	//----事件绑定
	connect(ui.toolButton_userManual, &QToolButton::clicked, this, &DrillPluginInformationReader::openUserManual);
	connect(ui.toolButton_about, &QToolButton::clicked, this, &DrillPluginInformationReader::openAbout);

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