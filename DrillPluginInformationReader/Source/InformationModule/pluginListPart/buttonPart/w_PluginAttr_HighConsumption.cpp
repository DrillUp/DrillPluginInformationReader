#include "stdafx.h"
#include "W_PluginAttr_HighConsumption.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		����˵������ ������.cpp
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�

		ʹ�÷�����
				>�򿪴���
					W_PluginAttr_HighConsumption d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_HighConsumption::W_PluginAttr_HighConsumption(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���

	//-----------------------------------
	//----ui��ʼ��
	//this->m_p_HighConsumption = new P_ScriptHelp_HighConsumption(this);
	//ui.verticalLayout_HighConsumption->addWidget(this->m_p_HighConsumption);

	TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_HighConsumption::~W_PluginAttr_HighConsumption(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ������

void W_PluginAttr_HighConsumption::showInformation_word(QString pluginName){
	this->setWindowTitle(pluginName + "����");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_HighConsumption->setData(nullptr);
		return; 
	}
	this->m_p_HighConsumption->setData(detail->getHighConsumption());
}*/