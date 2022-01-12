#include "stdafx.h"
#include "W_PluginAttr_HighConsumption.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		类：		属性说明窗口 高消耗.cpp
		所属模块：	信息模块
		功能：		属性说明窗口。

		使用方法：
				>打开窗口
					W_PluginAttr_HighConsumption d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_HighConsumption::W_PluginAttr_HighConsumption(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定

	//-----------------------------------
	//----ui初始化
	this->m_p_Performance = new P_ScriptHelp_Performance(this);
	ui.verticalLayout_highConsumption->addWidget(this->m_p_Performance);

	TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_HighConsumption::~W_PluginAttr_HighConsumption(){
}


/*-------------------------------------------------
		控件 - 显示信息 - 高消耗
*/
void W_PluginAttr_HighConsumption::showInformation_highConsumption(QString pluginName){
	this->setWindowTitle(pluginName + "属性");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_Performance->setData(nullptr);
		return; 
	}
	this->m_p_Performance->setData(detail->getPerformance());
}