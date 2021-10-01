#include "stdafx.h"
#include "p_PluginDetailPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件信息 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					
-----==========================================================-----
*/
P_PluginDetailPart::P_PluginDetailPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	this->m_curPluginName = "";

	//-----------------------------------
	//----控件初始化

	//-----------------------------------
	//----事件绑定

}

P_PluginDetailPart::~P_PluginDetailPart(){
}


/*-------------------------------------------------
		控件 - 显示指定插件详细信息
*/
void P_PluginDetailPart::showPluginDetail(QString plugin_name){
	if (plugin_name == ""){ return; }
	if (this->m_curPluginName == plugin_name){ return; }
	this->m_curPluginName = plugin_name;

	C_ScriptAnnotation annotation = S_InformationDataContainer::getInstance()->getAnnotation(plugin_name);

	ui.plainTextEdit_orgHelp->setPlainText(annotation.getHelp());
}

/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_PluginDetailPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_PluginDetailPart::putUiToData(){
	//（暂无）
}