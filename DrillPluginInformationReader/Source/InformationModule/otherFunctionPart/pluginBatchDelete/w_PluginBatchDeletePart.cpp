#include "stdafx.h"
#include "W_PluginBatchDeletePart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������ ����.cpp
		���ߣ�		drill_up
		����ģ�飺	����ģ��

		���ܣ�		�������Ĵ��ڡ�

		ʹ�÷�����
				>������д����
					W_PluginBatchDeletePart d(this);
					d.exec();
-----==========================================================-----
*/

W_PluginBatchDeletePart::W_PluginBatchDeletePart(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_p_PluginBatchDeletePart = new P_PluginBatchDeletePart(this);
	ui.verticalLayout_part->addWidget(this->m_p_PluginBatchDeletePart);

	//-----------------------------------
	//----�¼���
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &W_PluginBatchDeletePart::acceptData);

	//-----------------------------------
	//----��ʼ��ui
	TTool::_chinese_(ui.buttonBox);
}

W_PluginBatchDeletePart::~W_PluginBatchDeletePart(){
}


/*-------------------------------------------------
		���� - �������� -> ui����
*/
void W_PluginBatchDeletePart::putDataToUi() {
	this->m_p_PluginBatchDeletePart->putDataToUi();
};
/*-------------------------------------------------
		���� - ui���� -> ��������
*/
void W_PluginBatchDeletePart::putUiToData() {
	this->m_p_PluginBatchDeletePart->putUiToData();
};
/*-------------------------------------------------
		���� - �ύ���ݣ�У�飩
*/
void W_PluginBatchDeletePart::acceptData(){
	this->putUiToData();
	this->accept();
};