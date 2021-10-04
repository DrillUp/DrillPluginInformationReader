#include "stdafx.h"
#include "W_PluginAttrComment.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
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
	this->m_p_docs = new P_ScriptHelp_Docs(this);
	ui.verticalLayout_docs->addWidget(this->m_p_docs);

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

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_docs->setData(nullptr);
		return; 
	}
	this->m_p_docs->setData(detail->getDocs());
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

