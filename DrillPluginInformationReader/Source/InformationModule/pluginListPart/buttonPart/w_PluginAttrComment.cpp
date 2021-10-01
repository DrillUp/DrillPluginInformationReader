#include "stdafx.h"
#include "W_PluginAttrComment.h"

#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		类：		属性说明窗口.cpp
		所属模块：	信息模块
		功能：		属性说明窗口。

		使用方法：
				>打开窗口
					W_PluginAttrComment d;
					d.exec();

-----==========================================================-----
*/
W_PluginAttrComment::W_PluginAttrComment(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定

	//-----------------------------------
	//----ui初始化
	TTool::_chinese_(ui.buttonBox);

}

W_PluginAttrComment::~W_PluginAttrComment(){
}


/*-------------------------------------------------
		控件 - 显示信息 - 帮助文档
*/
void W_PluginAttrComment::showInformation_word(QString pluginName){
	ui.stackedWidget->setCurrentIndex(0);
	this->setWindowTitle(pluginName + "属性");
}
/*-------------------------------------------------
		控件 - 显示信息 - 资源路径
*/
void W_PluginAttrComment::showInformation_src(QString pluginName){
	ui.stackedWidget->setCurrentIndex(1);
	this->setWindowTitle(pluginName + "属性");

}
/*-------------------------------------------------
		控件 - 显示信息 - 高消耗
*/
void W_PluginAttrComment::showInformation_highConsumption(QString pluginName){
	ui.stackedWidget->setCurrentIndex(2);
	this->setWindowTitle(pluginName + "属性");

}
/*-------------------------------------------------
		控件 - 显示信息 - 小工具支持
*/
void W_PluginAttrComment::showInformation_hasTool(QString pluginName){
	ui.stackedWidget->setCurrentIndex(3);
	this->setWindowTitle(pluginName + "属性");

}
/*-------------------------------------------------
		控件 - 显示信息 - 外键
*/
void W_PluginAttrComment::showInformation_foreignKey(QString pluginName){
	ui.stackedWidget->setCurrentIndex(4);
	this->setWindowTitle(pluginName + "属性");

}

