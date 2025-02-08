#include "stdafx.h"
#include "W_PluginAttr_Docs.h"

#include "Source/RmmvInteractiveModule/InformationData/S_InformationDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/Utils/Common/TTool.h"


/*
-----==========================================================-----
		类：		属性说明窗口 插件文档.cpp
		所属模块：	信息模块
		功能：		属性说明窗口。

		使用方法：
				>打开窗口
					W_PluginAttr_Docs d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_Docs::W_PluginAttr_Docs(QWidget *parent)
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

W_PluginAttr_Docs::~W_PluginAttr_Docs(){
}


/*-------------------------------------------------
		控件 - 显示信息 - 帮助文档
*/
void W_PluginAttr_Docs::showInformation_word(QString pluginName){
	this->setWindowTitle(pluginName + "属性");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_docs->setData(nullptr);
		return; 
	}
	this->m_p_docs->setData(detail->getDocs());
}