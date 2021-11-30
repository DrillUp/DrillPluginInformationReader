#include "stdafx.h"
#include "p_PluginDetailPart.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
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
	//��ˮƽ�ָ�ֻ��ƻ� ������ ����QLabel+���� �γɵ��ȶ����ֽṹ�� ��

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_editPlugin, &QPushButton::clicked, this, &P_PluginDetailPart::btn_editPlugin);

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
	C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();

	// > ������Ϣ
	ui.lineEdit_pluginName->setText(plugin_name);
	ui.lineEdit_desc->setText(annotation.getPlugindesc());
	ui.lineEdit_author->setText(annotation.getAuthor());
	// > ������Ϣ - ���ܣ���ҳ˵�� - ���ܣ�
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

	// > ԭ��
	ui.plainTextEdit_orgHelp->setPlainText(annotation.getHelp());

	// > �ؼ���
	if (detail != nullptr){
		// > ������
		this->m_p_ScriptHelp_EffectScope->setData(detail->getEffectScope());
		// > ��ҳ˵��
		this->m_p_ScriptHelp_Subsection->setData(detail->getSubsection());
		// > ��Դ·��
		this->m_p_ScriptHelp_Src->setData(detail->getSrc());
		// > �����չ
		this->m_p_ScriptHelp_PluginRelation->setData(detail->getPluginRelation());
		// > ָ��
		this->m_p_ScriptHelp_Command->setData(detail->getCommand());
		// > ֪ʶ��
		C_ScriptHelp_Knowledge* knowledge = detail->getKnowledge();
		this->m_p_ScriptHelp_Knowledge->setData(detail->getKnowledge());
		if (knowledge == nullptr || knowledge->isNull()){
			ui.groupBox_Knowledge->setVisible(false);
		}else{
			ui.groupBox_Knowledge->setVisible(true);
		}
		// > �������

	}
}
/*-------------------------------------------------
		�ؼ� - �༭���
*/
void P_PluginDetailPart::btn_editPlugin(){
	if (this->m_curPluginName == ""){ return; }

	QFileInfo file_info = S_RmmvDataContainer::getInstance()->getRmmvFile_Plugin(this->m_curPluginName);
	QDesktopServices::openUrl(QUrl("file:/" + file_info.absoluteFilePath()));
}

/*-------------------------------------------------
		�� - �û��Զ���UI��ȡ
*/
void P_PluginDetailPart::ui_loadConfig(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - �û��Զ���UI�洢
*/
void P_PluginDetailPart::ui_saveConfig(){
	//�����ޣ�
}