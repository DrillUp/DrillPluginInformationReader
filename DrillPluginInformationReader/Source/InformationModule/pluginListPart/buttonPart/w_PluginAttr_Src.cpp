#include "stdafx.h"
#include "W_PluginAttr_Src.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		����˵������ ��Դ·��.cpp
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�

		ʹ�÷�����
				>�򿪴���
					W_PluginAttr_Src d;
					d.exec();
-----==========================================================-----
*/
W_PluginAttr_Src::W_PluginAttr_Src(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���

	//-----------------------------------
	//----ui��ʼ��
	this->m_p_src = new P_ScriptHelp_Src(this);
	ui.verticalLayout_src->addWidget(this->m_p_src);

	TTool::_chinese_(ui.buttonBox);

}

W_PluginAttr_Src::~W_PluginAttr_Src(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ��Դ·��
*/
void W_PluginAttr_Src::showInformation_src(QString pluginName){
	this->setWindowTitle(pluginName + "����");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_src->setData(nullptr);
		return;
	}
	this->m_p_src->setData(detail->getSrc());
}