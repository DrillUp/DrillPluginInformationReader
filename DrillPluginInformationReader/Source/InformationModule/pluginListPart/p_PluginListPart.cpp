#include "stdafx.h"
#include "p_PluginListPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		����б� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					
-----==========================================================-----
*/
P_PluginListPart::P_PluginListPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_pluginMode, 30);

	//-----------------------------------
	//----�¼���

}

P_PluginListPart::~P_PluginListPart(){
}


/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginListPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginListPart::putUiToData(){
	//�����ޣ�
}