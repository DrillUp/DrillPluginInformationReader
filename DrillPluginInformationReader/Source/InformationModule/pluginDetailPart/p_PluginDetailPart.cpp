#include "stdafx.h"
#include "p_PluginDetailPart.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
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
	this->m_p_ScriptHelp_EffectScope = new P_ScriptHelp_EffectScope();
	this->m_p_ScriptHelp_Subsection = new P_ScriptHelp_Subsection();
	this->m_p_ScriptHelp_Src = new P_ScriptHelp_Src();
	this->m_p_ScriptHelp_Command = new P_ScriptHelp_Command();
	this->m_p_ScriptHelp_Performance = new P_ScriptHelp_Performance();
	this->m_p_ScriptHelp_PluginRelation = new P_ScriptHelp_PluginRelation();

	ui.verticalLayout_EffectScope->addWidget(this->m_p_ScriptHelp_EffectScope);
	ui.verticalLayout_Subsection->addWidget(this->m_p_ScriptHelp_Subsection);
	ui.verticalLayout_Src->addWidget(this->m_p_ScriptHelp_Src);
	ui.verticalLayout_Command->addWidget(this->m_p_ScriptHelp_Command);
	ui.verticalLayout_Performance->addWidget(this->m_p_ScriptHelp_Performance);
	ui.verticalLayout_PluginRelation->addWidget(this->m_p_ScriptHelp_PluginRelation);
	
	//ui.splitter->handle(1)->setAttribute(Qt::WA_Hover, true);
	//（水平分割布局会破坏 子类中 大量QLabel+换行 形成的稳定布局结构。 ）

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

	// > 基本信息
	ui.lineEdit_pluginName->setText(plugin_name);
	ui.lineEdit_desc->setText(annotation.getPlugindesc());
	ui.lineEdit_author->setText(annotation.getAuthor());

	// > 原文
	ui.plainTextEdit_orgHelp->setPlainText(annotation.getHelp());

	C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();
	if (detail != nullptr){
		// > 作用域
		this->m_p_ScriptHelp_EffectScope->setData(detail->getEffectScope());
		// > 分页说明
		this->m_p_ScriptHelp_Subsection->setData(detail->getSubsection());
	}
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