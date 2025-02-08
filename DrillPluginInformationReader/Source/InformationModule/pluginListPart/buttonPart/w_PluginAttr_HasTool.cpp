#include "stdafx.h"
#include "W_PluginAttr_HasTool.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/Utils/Common/TTool.h"


/*
-----==========================================================-----
		类：		属性说明窗口 小工具支持.cpp
		所属模块：	信息模块
		功能：		属性说明窗口。

		使用方法：
				>打开窗口
					W_PluginAttr_HasTool d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_HasTool::W_PluginAttr_HasTool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定

	//-----------------------------------
	//----ui初始化
	//this->m_p_HasTool = new P_ScriptHelp_HasTool(this);
	//ui.verticalLayout_HasTool->addWidget(this->m_p_HasTool);
	//
	//TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_HasTool::~W_PluginAttr_HasTool(){
}


/*-------------------------------------------------
		控件 - 显示信息 - 帮助文档

void W_PluginAttr_HasTool::showInformation_word(QString pluginName){
	this->setWindowTitle(pluginName + "属性");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_HasTool->setData(nullptr);
		return; 
	}
	this->m_p_HasTool->setData(detail->getHasTool());
	}*/