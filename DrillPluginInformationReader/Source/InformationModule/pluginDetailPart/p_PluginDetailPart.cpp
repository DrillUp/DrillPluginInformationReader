#include "stdafx.h"
#include "p_PluginDetailPart.h"

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

	ui.plainTextEdit_orgHelp->setPlainText(annotation.getHelp());
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