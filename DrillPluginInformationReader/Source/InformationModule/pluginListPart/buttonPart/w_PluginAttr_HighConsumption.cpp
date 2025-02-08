#include "stdafx.h"
#include "W_PluginAttr_HighConsumption.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/Utils/Common/TTool.h"


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
	this->m_p_Performance = new P_ScriptHelp_Performance(this);
	ui.verticalLayout_highConsumption->addWidget(this->m_p_Performance);

	TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_HighConsumption::~W_PluginAttr_HighConsumption(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ������
*/
void W_PluginAttr_HighConsumption::showInformation_highConsumption(QString pluginName){
	this->setWindowTitle(pluginName + "����");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_Performance->setData(nullptr);
		return; 
	}
	this->m_p_Performance->setData(detail->getPerformance());
}