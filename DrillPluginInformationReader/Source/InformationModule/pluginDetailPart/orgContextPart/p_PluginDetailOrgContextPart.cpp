#include "stdafx.h"
#include "p_PluginDetailOrgContextPart.h"

#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		ԭ��չ�� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	ԭ��չ���ı༭��ṹ��
-----==========================================================-----
*/
P_PluginDetailOrgContextPart::P_PluginDetailOrgContextPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}

P_PluginDetailOrgContextPart::~P_PluginDetailOrgContextPart(){
}

/*-------------------------------------------------
		�ؼ� - �����ı�
*/
void P_PluginDetailOrgContextPart::setContext(QString context){
	ui.plainTextEdit->setPlainText(context);
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginDetailOrgContextPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginDetailOrgContextPart::putUiToData(){
	//�����ޣ�
}