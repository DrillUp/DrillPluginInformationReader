﻿#include "stdafx.h"
#include "W_SoftwareFirstTip.h"

#include "../drillplugininformationreader.h"
#include "Source/ProjectModule/StorageGlobal/S_IniManager.h"
#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		类：		首页提示框.cpp
		所属模块：	主窗体模块
		功能：		首页提示框。

		使用方法：
				> 打开窗口
					W_SoftwareFirstTip d;
					d.exec();
-----==========================================================-----
*/

W_SoftwareFirstTip::W_SoftwareFirstTip(QWidget *parent)
	: QDialog(parent)
{
	W_SoftwareFirstTip::cur_instance = this;
	ui.setupUi(this);
	this->_init();
}
W_SoftwareFirstTip::~W_SoftwareFirstTip(){
}
/*-------------------------------------------------
		单例
*/
W_SoftwareFirstTip* W_SoftwareFirstTip::cur_instance = NULL;
W_SoftwareFirstTip* W_SoftwareFirstTip::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new W_SoftwareFirstTip(DrillPluginInformationReader::getInstance());
	}
	return cur_instance;
}
/*-------------------------------------------------
		初始化
*/
void W_SoftwareFirstTip::_init() {

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton, &QToolButton::clicked, this, &W_SoftwareFirstTip::openUserManual);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptData()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(rejectData()));

	//-----------------------------------
	//----ui初始化
	TTool::_chinese_(ui.buttonBox);

	
}


/* --------------------------------------------------------------
		控件 - 用户手册
*/
void W_SoftwareFirstTip::openUserManual() {
	QString sPath = qApp->applicationDirPath();

	QString docx = sPath + "/help/关于插件信息查看器.docx";
	if (QFileInfo(docx).exists()){
		QDesktopServices::openUrl(QUrl("file:/" + docx)); 
	}else{
		QMessageBox::warning(this, "错误", "文档\"关于插件信息查看器.docx\"不见了。", QMessageBox::Yes);
	}

}


/* --------------------------------------------------------------
		窗口 - 提交数据
*/
void W_SoftwareFirstTip::acceptData(){
	//(无操作)

	this->accept();
}
/* --------------------------------------------------------------
		窗口 - 取消数据
*/
void W_SoftwareFirstTip::rejectData(){

	if (ui.checkBox->isChecked() == true){
		S_IniManager::getInstance()->setConfig("PIR_NoMoreFirstTip", "true");
	}

	this->reject();
}
/* --------------------------------------------------------------
		窗口 - 窗口关闭事件（点击关闭按钮）
*/
void W_SoftwareFirstTip::closeEvent(QCloseEvent *event){
	this->rejectData();
	event->accept();
}