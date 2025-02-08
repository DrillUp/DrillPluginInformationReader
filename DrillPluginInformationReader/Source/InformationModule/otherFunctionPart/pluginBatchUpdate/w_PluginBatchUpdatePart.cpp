#include "stdafx.h"
#include "W_PluginBatchUpdatePart.h"

#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		���²�� ����.cpp
		���ߣ�		drill_up
		����ģ�飺	����ģ��

		���ܣ�		���²���Ĵ��ڡ�

		ʹ�÷�����
				>������д����
					W_PluginBatchUpdatePart d(this);
					d.exec();
-----==========================================================-----
*/

W_PluginBatchUpdatePart::W_PluginBatchUpdatePart(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_p_PluginBatchUpdatePart = new P_PluginBatchUpdatePart(this);
	ui.verticalLayout_part->addWidget(this->m_p_PluginBatchUpdatePart);

	//-----------------------------------
	//----�¼���
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &W_PluginBatchUpdatePart::acceptData);

	//-----------------------------------
	//----��ʼ��ui
	TTool::_chinese_(ui.buttonBox);
}

W_PluginBatchUpdatePart::~W_PluginBatchUpdatePart(){
}


/*-------------------------------------------------
		���� - �������� -> ui����
*/
void W_PluginBatchUpdatePart::putDataToUi() {
	this->m_p_PluginBatchUpdatePart->putDataToUi();
};
/*-------------------------------------------------
		���� - ui���� -> ��������
*/
void W_PluginBatchUpdatePart::putUiToData() {
	this->m_p_PluginBatchUpdatePart->putUiToData();
};
/*-------------------------------------------------
		���� - �ύ���ݣ�У�飩
*/
void W_PluginBatchUpdatePart::acceptData(){
	this->putUiToData();
	this->accept();
};