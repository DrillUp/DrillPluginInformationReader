#include "stdafx.h"
#include "p_DesignTipGeneratorPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������������ �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������������ı༭��ṹ��

		˵����		�˿ؼ��鴴����ֱ�Ӵӵ�ǰ �Ѷ�ȡ�Ĳ������ �н�����
-----==========================================================-----
*/
P_DesignTipGeneratorPart::P_DesignTipGeneratorPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_data = C_DesignTipGenerator();
	this->m_data.initData();		//��������ֱ�Ӵӵ�ǰ �Ѷ�ȡ�Ĳ������ �н�����

	//-----------------------------------
	//----�ؼ���ʼ��
	this->m_cellTank = QList<P_DesignTip_Cell*>();

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_generate, &QPushButton::clicked, this, &P_DesignTipGeneratorPart::doGenerate);

	this->doGenerate();
}

P_DesignTipGeneratorPart::~P_DesignTipGeneratorPart(){
}

/*-------------------------------------------------
		�ؼ� - ����ؼ���
*/
void P_DesignTipGeneratorPart::clearCells(){
	for (int i = this->m_cellTank.count()-1; i >= 0; i--){
		P_DesignTip_Cell* cell = this->m_cellTank.at(i);
		ui.verticalLayout_tip->removeWidget(cell);
		cell->deleteLater();
	}
	this->m_cellTank.clear();
}
/*-------------------------------------------------
		�ؼ� - ִ������
*/
void P_DesignTipGeneratorPart::doGenerate(){
	this->clearCells();

	// > ������ظ�������
	int ran_count = ui.spinBox->value();
	QList<int> indexOrg_list;
	QList<int> indexRan_list;
	for (int i = 0; i < this->m_data.count();i++){
		indexOrg_list.append(i);
	}
	for (int i = 0; i < ran_count; i++){
		if (this->m_data.count() == 0){ break; }
		int ran = qrand() % this->m_data.count();
		indexRan_list.append(indexOrg_list.at(ran));
		indexOrg_list.removeAt(ran);
	}

	// > ��ӿؼ�
	for (int i = 0; i < indexRan_list.count(); i++){
		C_DesignTip_Cell c_cell = this->m_data.getCellByIndex(i);
		P_DesignTip_Cell* p_cell = new P_DesignTip_Cell();
		p_cell->setData(c_cell);
		ui.verticalLayout_tip->addWidget(p_cell);
	}
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_DesignTipGeneratorPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_DesignTipGeneratorPart::putUiToData(){
	//�����ޣ�
}