#include "stdafx.h"
#include "p_PluginDetailPart.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		�����Ϣ �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					
-----==========================================================-----
*/
P_PluginDetailPart::P_PluginDetailPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_curPluginName = "";

	//-----------------------------------
	//----�ؼ���ʼ��
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
	//��ˮƽ�ָ�ֻ��ƻ� ������ ����QLabel+���� �γɵ��ȶ����ֽṹ�� ��

	//-----------------------------------
	//----�¼���

}

P_PluginDetailPart::~P_PluginDetailPart(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾָ�������ϸ��Ϣ
*/
void P_PluginDetailPart::showPluginDetail(QString plugin_name){
	if (plugin_name == ""){ return; }
	if (this->m_curPluginName == plugin_name){ return; }
	this->m_curPluginName = plugin_name;

	C_ScriptAnnotation annotation = S_InformationDataContainer::getInstance()->getAnnotation(plugin_name);

	// > ������Ϣ
	ui.lineEdit_pluginName->setText(plugin_name);
	ui.lineEdit_desc->setText(annotation.getPlugindesc());
	ui.lineEdit_author->setText(annotation.getAuthor());

	// > ԭ��
	ui.plainTextEdit_orgHelp->setPlainText(annotation.getHelp());

	C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();
	if (detail != nullptr){
		// > ������
		this->m_p_ScriptHelp_EffectScope->setData(detail->getEffectScope());
		// > ��ҳ˵��
		this->m_p_ScriptHelp_Subsection->setData(detail->getSubsection());
	}
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginDetailPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginDetailPart::putUiToData(){
	//�����ޣ�
}