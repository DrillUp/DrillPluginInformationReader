#include "stdafx.h"
#include "p_PluginAttr_ButtonPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������� ��ť��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		˵����		���������ʾ�õİ�ť�顣
-----==========================================================-----
*/
P_PluginAttr_ButtonPart::P_PluginAttr_ButtonPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----��ʼ��ui
	ui.toolButton_src->setIcon(QIcon(QRC_IconSrcPath + "/menu/ExportImage.png"));

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_src, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_src);

}

P_PluginAttr_ButtonPart::~P_PluginAttr_ButtonPart(){
}


/*-------------------------------------------------
		�ؼ� - ��Դ��ť
*/
void P_PluginAttr_ButtonPart::btn_src(){
	
}


/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginAttr_ButtonPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginAttr_ButtonPart::putUiToData(){
	//�����ޣ�
}