#include "stdafx.h"
#include "p_InformationPart.h"

#include "pluginListPart/p_PluginListPart.h"
#include "pluginDetailPart/p_PluginDetailPart.h"
#include "pluginDetailPart/orgContextPart/p_PluginDetailOrgContextPart.h"
#include "commandSearcherPart/p_CommandSearcherPart.h"
#include "otherFunctionPart/p_OtherFunctionPart.h"
#include "otherFunctionPart/designTipGenerator/p_DesignTipGeneratorPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��Ϣģ�� ���༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					
-----==========================================================-----
*/
P_InformationPart::P_InformationPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	this->m_p_pluginListPart = new P_PluginListPart(parent);
	this->m_p_pluginDetailPart = new P_PluginDetailPart(parent);
	this->m_p_commandSearcherPart = new P_CommandSearcherPart(parent);
	this->m_p_otherFunctionPart = new P_OtherFunctionPart(parent);
	this->m_p_DesignTipGenerator = nullptr;
	this->m_p_pluginDetailOrgContextPart = nullptr;

	// > ���۵�ѡ�
	this->m_p_FoldableTabRelater = new P_FoldableTabRelater(ui.tabWidget);	//��ui�е�ֻ��ʾ�⣬�ù�������ؽ�tab��
	this->m_p_FoldableTabRelater->addPart(" ����б�  ", this->m_p_pluginListPart);
	this->m_p_FoldableTabRelater->addPart(" �����ϸ��Ϣ  ", this->m_p_pluginDetailPart);
	this->m_p_FoldableTabRelater->addPart(" ָ��������  ", this->m_p_commandSearcherPart);
	this->m_p_FoldableTabRelater->addPart(" ��������  ", this->m_p_otherFunctionPart);

	//-----------------------------------
	//----�¼���
	connect(this->m_p_pluginListPart, &P_PluginListPart::pluginTriggered, this, &P_InformationPart::showPluginDetail);
	connect(this->m_p_otherFunctionPart, &P_OtherFunctionPart::selected_DesignTipGenerator, this, &P_InformationPart::selectPart_DesignTipGenerator);
	connect(this->m_p_pluginDetailPart, &P_PluginDetailPart::selected_PluginDetailOrgContextPart, this, &P_InformationPart::selectPart_PluginDetailOrgContextPart);

}

P_InformationPart::~P_InformationPart(){
}

/*-------------------------------------------------
		�ؼ� - ��ʾָ�������ϸ��Ϣ
*/
void P_InformationPart::showPluginDetail(QString plugin_name){
	
	// > ��ʾ����
	this->m_p_pluginDetailPart->showPluginDetail(plugin_name);

	// > �л�����ǩҳ
	this->m_p_FoldableTabRelater->selectTab(" �����ϸ��Ϣ  ");
}

/*-------------------------------------------------
		�ؼ� - ѡ�� ���������
*/
void P_InformationPart::selectPart_DesignTipGenerator(){
	if (this->m_p_DesignTipGenerator == nullptr){
		this->createPart_DesignTipGenerator();
	}
	this->m_p_FoldableTabRelater->selectTab(" ���������  ");
}
/*-------------------------------------------------
		�ؼ� - ���� ���������
*/
void P_InformationPart::createPart_DesignTipGenerator(){
	this->m_p_DesignTipGenerator = new P_DesignTipGeneratorPart();
	this->m_p_FoldableTabRelater->addPart(" ���������  ", this->m_p_DesignTipGenerator);
}
/*-------------------------------------------------
		�ؼ� - ѡ�� ԭ��չ��
*/
void P_InformationPart::selectPart_PluginDetailOrgContextPart(){
	if (this->m_p_pluginDetailOrgContextPart == nullptr){
		this->createPart_PluginDetailOrgContextPart();
	}
	this->m_p_FoldableTabRelater->selectTab(" ���ԭ��  ");
}
/*-------------------------------------------------
		�ؼ� - ���� ԭ��չ��
*/
void P_InformationPart::createPart_PluginDetailOrgContextPart(){
	this->m_p_pluginDetailOrgContextPart = new P_PluginDetailOrgContextPart();
	this->m_p_FoldableTabRelater->addPart(" ���ԭ��  ", this->m_p_pluginDetailOrgContextPart);

	// > �����ź�
	connect(this->m_p_pluginDetailPart, &P_PluginDetailPart::orgContextChanged, this->m_p_pluginDetailOrgContextPart, &P_PluginDetailOrgContextPart::setContext);
}


/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_InformationPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_InformationPart::putUiToData(){
	//�����ޣ�
}