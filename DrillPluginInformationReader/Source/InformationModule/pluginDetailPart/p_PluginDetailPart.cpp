#include "stdafx.h"
#include "p_PluginDetailPart.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
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
	this->m_p_ScriptHelp_PluginRelation = new P_ScriptHelp_PluginRelation();
	this->m_p_ScriptHelp_Subsection = new P_ScriptHelp_Subsection();
	this->m_p_ScriptHelp_Src = new P_ScriptHelp_Src();
	this->m_p_ScriptHelp_Command = new P_ScriptHelp_Command();
	this->m_p_ScriptHelp_Knowledge = new P_ScriptHelp_Knowledge();
	this->m_p_ScriptHelp_Performance = new P_ScriptHelp_Performance();

	ui.verticalLayout_EffectScope->addWidget(this->m_p_ScriptHelp_EffectScope);
	ui.verticalLayout_PluginRelation->addWidget(this->m_p_ScriptHelp_PluginRelation);
	ui.verticalLayout_Subsection->addWidget(this->m_p_ScriptHelp_Subsection);
	ui.verticalLayout_Src->addWidget(this->m_p_ScriptHelp_Src);
	ui.verticalLayout_Command->addWidget(this->m_p_ScriptHelp_Command);
	ui.verticalLayout_Knowledge->addWidget(this->m_p_ScriptHelp_Knowledge);
	ui.verticalLayout_Performance->addWidget(this->m_p_ScriptHelp_Performance);
	
	//ui.splitter->handle(1)->setAttribute(Qt::WA_Hover, true);
	//（水平分割布局会破坏 子类中 大量QLabel+换行 形成的稳定布局结构。 ）

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_editPlugin, &QPushButton::clicked, this, &P_PluginDetailPart::btn_editPlugin);

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
	C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();

	// > 基本信息
	ui.lineEdit_pluginName->setText(plugin_name);
	ui.lineEdit_desc->setText(annotation.getPlugindesc());
	ui.lineEdit_author->setText(annotation.getAuthor());
	// > 基本信息 - 介绍（分页说明 - 介绍）
	if (detail != nullptr){
		QString introduction = detail->getSubsection()->getHeader().introduction;
		if (introduction == ""){
			ui.label_introduction_title->setVisible(false);
			ui.label_introduction_context->setVisible(false);
		}else{
			ui.label_introduction_context->setText(introduction);
			ui.label_introduction_title->setVisible(true);
			ui.label_introduction_context->setVisible(true);
		}
	}

	// > 原文
	ui.plainTextEdit_orgHelp->setPlainText(annotation.getHelp());

	// > 控件组
	if (detail != nullptr){
		// > 作用域
		this->m_p_ScriptHelp_EffectScope->setData(detail->getEffectScope());
		// > 分页说明
		this->m_p_ScriptHelp_Subsection->setData(detail->getSubsection());
		// > 资源路径
		this->m_p_ScriptHelp_Src->setData(detail->getSrc());
		// > 插件扩展
		this->m_p_ScriptHelp_PluginRelation->setData(detail->getPluginRelation());
		// > 指令
		this->m_p_ScriptHelp_Command->setData(detail->getCommand());
		// > 知识点
		C_ScriptHelp_Knowledge* knowledge = detail->getKnowledge();
		this->m_p_ScriptHelp_Knowledge->setData(detail->getKnowledge());
		if (knowledge == nullptr || knowledge->isNull()){
			ui.groupBox_Knowledge->setVisible(false);
		}else{
			ui.groupBox_Knowledge->setVisible(true);
		}
		// > 插件性能

	}
}
/*-------------------------------------------------
		控件 - 编辑插件
*/
void P_PluginDetailPart::btn_editPlugin(){
	if (this->m_curPluginName == ""){ return; }

	QFileInfo file_info = S_RmmvDataContainer::getInstance()->getRmmvFile_Plugin(this->m_curPluginName);
	QDesktopServices::openUrl(QUrl("file:/" + file_info.absoluteFilePath()));
}

/*-------------------------------------------------
		块 - 用户自定义UI读取
*/
void P_PluginDetailPart::ui_loadConfig(){
	//（暂无）
}
/*-------------------------------------------------
		块 - 用户自定义UI存储
*/
void P_PluginDetailPart::ui_saveConfig(){
	//（暂无）
}