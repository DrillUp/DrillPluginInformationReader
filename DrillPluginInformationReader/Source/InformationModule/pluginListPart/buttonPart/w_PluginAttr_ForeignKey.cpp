#include "stdafx.h"
#include "W_PluginAttr_ForeignKey.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		类：		属性说明窗口 外键.cpp
		所属模块：	信息模块
		功能：		属性说明窗口。

		使用方法：
				>打开窗口
					W_PluginAttr_ForeignKey d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_ForeignKey::W_PluginAttr_ForeignKey(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定

	//-----------------------------------
	//----ui初始化
	//this->m_p_ForeignKey = new P_ScriptHelp_ForeignKey(this);
	//ui.verticalLayout_ForeignKey->addWidget(this->m_p_ForeignKey);
	//
	//TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_ForeignKey::~W_PluginAttr_ForeignKey(){
}


/*-------------------------------------------------
		控件 - 显示信息 - 帮助文档

void W_PluginAttr_ForeignKey::showInformation_word(QString pluginName){
	this->setWindowTitle(pluginName + "属性");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_ForeignKey->setData(nullptr);
		return; 
	}
	this->m_p_ForeignKey->setData(detail->getForeignKey());
	}*/