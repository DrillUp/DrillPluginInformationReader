#include "stdafx.h"
#include "W_PluginAttr_HasTool.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/Utils/Common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		����˵������ С����֧��.cpp
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�

		ʹ�÷�����
				>�򿪴���
					W_PluginAttr_HasTool d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_HasTool::W_PluginAttr_HasTool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���

	//-----------------------------------
	//----ui��ʼ��
	//this->m_p_HasTool = new P_ScriptHelp_HasTool(this);
	//ui.verticalLayout_HasTool->addWidget(this->m_p_HasTool);
	//
	//TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_HasTool::~W_PluginAttr_HasTool(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - �����ĵ�

void W_PluginAttr_HasTool::showInformation_word(QString pluginName){
	this->setWindowTitle(pluginName + "����");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_HasTool->setData(nullptr);
		return; 
	}
	this->m_p_HasTool->setData(detail->getHasTool());
	}*/