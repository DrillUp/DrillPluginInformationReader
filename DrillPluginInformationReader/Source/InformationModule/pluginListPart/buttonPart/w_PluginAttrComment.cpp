#include "stdafx.h"
#include "W_PluginAttrComment.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		����˵������.cpp
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�

		ʹ�÷�����
				>�򿪴���
					W_PluginAttrComment d;
					d.exec();

-----==========================================================-----
*/
W_PluginAttrComment::W_PluginAttrComment(QWidget *parent)
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

W_PluginAttrComment::~W_PluginAttrComment(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - �����ĵ�
*/
void W_PluginAttrComment::showInformation_word(QString pluginName){
	ui.stackedWidget->setCurrentIndex(0);
	this->setWindowTitle(pluginName + "����");

	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(pluginName);
	if (detail == nullptr){
		this->m_p_docs->setData(nullptr);
		return; 
	}
	this->m_p_docs->setData(detail->getDocs());
}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ��Դ·��
*/
void W_PluginAttrComment::showInformation_src(QString pluginName){
	ui.stackedWidget->setCurrentIndex(1);
	this->setWindowTitle(pluginName + "����");

}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ������
*/
void W_PluginAttrComment::showInformation_highConsumption(QString pluginName){
	ui.stackedWidget->setCurrentIndex(2);
	this->setWindowTitle(pluginName + "����");

}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - С����֧��
*/
void W_PluginAttrComment::showInformation_hasTool(QString pluginName){
	ui.stackedWidget->setCurrentIndex(3);
	this->setWindowTitle(pluginName + "����");

}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ���
*/
void W_PluginAttrComment::showInformation_foreignKey(QString pluginName){
	ui.stackedWidget->setCurrentIndex(4);
	this->setWindowTitle(pluginName + "����");

}

