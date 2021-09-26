#include "stdafx.h"
#include "p_InformationPart.h"

#include "pluginListPart/p_PluginListPart.h"
#include "pluginDetailPart/p_PluginDetailPart.h"
#include "commandSearcherPart/p_CommandSearcherPart.h"

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

	// > ���۵�ѡ�
	this->m_p_FoldableTabRelater = new P_FoldableTabRelater(ui.tabWidget);	//��ui�е�ֻ��ʾ�⣬�ù�������ؽ�tab��
	this->m_p_FoldableTabRelater->addPart(" ����б�  ", this->m_p_pluginListPart);
	this->m_p_FoldableTabRelater->addPart(" �����ϸ��Ϣ  ", this->m_p_pluginDetailPart);
	this->m_p_FoldableTabRelater->addPart(" ָ��������  ", this->m_p_commandSearcherPart);

	//-----------------------------------
	//----�¼���

}

P_InformationPart::~P_InformationPart(){
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