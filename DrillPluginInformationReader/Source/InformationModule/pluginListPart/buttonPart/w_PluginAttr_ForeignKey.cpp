#include "stdafx.h"
#include "W_PluginAttr_ForeignKey.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		����˵������ ���.cpp
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�

		ʹ�÷�����
				>�򿪴���
					W_PluginAttr_ForeignKey d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_ForeignKey::W_PluginAttr_ForeignKey(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���

	//-----------------------------------
	//----ui��ʼ��
	//this->m_p_ForeignKey = new P_ScriptHelp_ForeignKey(this);
	//ui.verticalLayout_ForeignKey->addWidget(this->m_p_ForeignKey);
	//
	//TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_ForeignKey::~W_PluginAttr_ForeignKey(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - �����ĵ�

void W_PluginAttr_ForeignKey::showInformation_word(QString pluginName){
	this->setWindowTitle(pluginName + "����");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_ForeignKey->setData(nullptr);
		return; 
	}
	this->m_p_ForeignKey->setData(detail->getForeignKey());
	}*/