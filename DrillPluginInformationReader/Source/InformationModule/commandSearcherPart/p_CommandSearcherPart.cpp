#include "stdafx.h"
#include "p_CommandSearcherPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		ָ�������� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					
-----==========================================================-----
*/
P_CommandSearcherPart::P_CommandSearcherPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_commandType, 30);

	//-----------------------------------
	//----�¼���

}

P_CommandSearcherPart::~P_CommandSearcherPart(){
}


/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_CommandSearcherPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_CommandSearcherPart::putUiToData(){
	//�����ޣ�
}