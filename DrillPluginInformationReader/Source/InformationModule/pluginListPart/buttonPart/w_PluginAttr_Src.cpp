#include "stdafx.h"
#include "W_PluginAttr_Src.h"

#include "Source/RmmvInteractiveModule/InformationData/S_InformationDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/Utils/Common/TTool.h"


/*
-----==========================================================-----
		类：		属性说明窗口 资源路径.cpp
		所属模块：	信息模块
		功能：		属性说明窗口。

		使用方法：
				>打开窗口
					W_PluginAttr_Src d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_Src::W_PluginAttr_Src(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定

	//-----------------------------------
	//----ui初始化
	this->m_p_src = new P_ScriptHelp_Src(this);
	ui.verticalLayout_src->addWidget(this->m_p_src);

	TTool::_chinese_(ui.buttonBox);

}

W_PluginAttr_Src::~W_PluginAttr_Src(){
}


/*-------------------------------------------------
		控件 - 显示信息 - 资源路径
*/
void W_PluginAttr_Src::showInformation_src(QString pluginName){
	this->setWindowTitle(pluginName + "属性");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_src->setData(nullptr);
		return;
	}
	this->m_p_src->setData(detail->getSrc());
}