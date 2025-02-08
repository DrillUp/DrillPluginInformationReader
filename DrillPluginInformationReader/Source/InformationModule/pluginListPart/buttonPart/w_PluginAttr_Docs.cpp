#include "stdafx.h"
#include "W_PluginAttr_Docs.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/Utils/Common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		����˵������ ����ĵ�.cpp
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�

		ʹ�÷�����
				>�򿪴���
					W_PluginAttr_Docs d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_Docs::W_PluginAttr_Docs(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���

	//-----------------------------------
	//----ui��ʼ��
	this->m_p_docs = new P_ScriptHelp_Docs(this);
	ui.verticalLayout_docs->addWidget(this->m_p_docs);

	TTool::_chinese_(ui.buttonBox);
}

W_PluginAttr_Docs::~W_PluginAttr_Docs(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - �����ĵ�
*/
void W_PluginAttr_Docs::showInformation_word(QString pluginName){
	this->setWindowTitle(pluginName + "����");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_docs->setData(nullptr);
		return; 
	}
	this->m_p_docs->setData(detail->getDocs());
}