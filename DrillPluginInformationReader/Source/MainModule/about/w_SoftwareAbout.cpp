#include "stdafx.h"
#include "W_SoftwareAbout.h"

#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		类：		关于窗口.cpp
		所属模块：	主窗体模块
		功能：		关于窗口。

		使用方法：
				>打开窗口
					W_SoftwareAbout d;
					d.exec();

-----==========================================================-----
*/
W_SoftwareAbout::W_SoftwareAbout(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton, &QToolButton::clicked, this, &W_SoftwareAbout::openUserManual);

	//-----------------------------------
	//----ui初始化
	TTool::_chinese_(ui.buttonBox);

	QString version = "v1.00";
	ui.label_title->setText("插件信息读取器（" + version + "）");

}

W_SoftwareAbout::~W_SoftwareAbout(){
}


/* --------------------------------------------------------------
		控件 - 用户手册
*/
void W_SoftwareAbout::openUserManual() {
	QString sPath = qApp->applicationDirPath();

	QString docx = sPath + "/help/关于插件信息读取器.docx";
	if (QFileInfo(docx).exists()){
		QDesktopServices::openUrl(QUrl("file:/" + docx)); 
	}else{
		QMessageBox::warning(this, "错误", "文档\"关于插件信息读取器.docx\"不见了。", QMessageBox::Yes);
	}

}