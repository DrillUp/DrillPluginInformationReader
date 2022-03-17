#include "stdafx.h"
#include "p_OtherFunctionPart.h"

#include "Source/InformationModule/otherFunctionPart/pluginBatchDelete/w_PluginBatchDeletePart.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		�������� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������ܵı༭��ṹ��
					
-----==========================================================-----
*/
P_OtherFunctionPart::P_OtherFunctionPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	ui.groupBox_2->setVisible(false);	//�����ش���ӣ�

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_showUnusedPlugin, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_PluginBatchDelete);
	connect(ui.toolButton_showDesignTip, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_DesignTipGenerator);

}

P_OtherFunctionPart::~P_OtherFunctionPart(){
}


/*-------------------------------------------------
		�ؼ� - ѡ�� ����δʹ�õĲ��
*/
void P_OtherFunctionPart::btn_PluginBatchDelete(){
	W_PluginBatchDeletePart d(this);
	d.exec();
}
/*-------------------------------------------------
		�ؼ� - ѡ�� ���������
*/
void P_OtherFunctionPart::btn_DesignTipGenerator(){
	emit selected_DesignTipGenerator();
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_OtherFunctionPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_OtherFunctionPart::putUiToData(){
	//�����ޣ�
}