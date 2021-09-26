#include "stdafx.h"
#include "p_InformationPart.h"

#include "pluginListPart/p_PluginListPart.h"
#include "pluginDetailPart/p_PluginDetailPart.h"
#include "commandSearcherPart/p_CommandSearcherPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		信息模块 主编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					
-----==========================================================-----
*/
P_InformationPart::P_InformationPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----控件初始化
	this->m_p_pluginListPart = new P_PluginListPart(parent);
	this->m_p_pluginDetailPart = new P_PluginDetailPart(parent);
	this->m_p_commandSearcherPart = new P_CommandSearcherPart(parent);

	// > 可折叠选项卡
	this->m_p_FoldableTabRelater = new P_FoldableTabRelater(ui.tabWidget);	//（ui中的只是示意，该工具类会重建tab）
	this->m_p_FoldableTabRelater->addPart(" 插件列表  ", this->m_p_pluginListPart);
	this->m_p_FoldableTabRelater->addPart(" 插件详细信息  ", this->m_p_pluginDetailPart);
	this->m_p_FoldableTabRelater->addPart(" 指令搜索器  ", this->m_p_commandSearcherPart);

	//-----------------------------------
	//----事件绑定

}

P_InformationPart::~P_InformationPart(){
}


/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_InformationPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_InformationPart::putUiToData(){
	//（暂无）
}