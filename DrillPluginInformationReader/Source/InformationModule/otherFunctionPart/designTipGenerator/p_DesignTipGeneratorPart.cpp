#include "stdafx.h"
#include "p_DesignTipGeneratorPart.h"

#include "Source/Utils/Common/TTool.h"

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
	this->m_indexOrgTank = QList<int>();

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_generate, &QPushButton::clicked, this, &P_DesignTipGeneratorPart::doGenerate);
	connect(ui.toolButton_resetAll, &QPushButton::clicked, this, &P_DesignTipGeneratorPart::resetAll);

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
		�ؼ� - ���¿�ʼȫ��
*/
void P_DesignTipGeneratorPart::resetAll(){
	this->resetIndexTank();
	this->doGenerate();
}
/*-------------------------------------------------
		�ؼ� - ��������
*/
void P_DesignTipGeneratorPart::resetIndexTank(){
	this->m_indexOrgTank.clear();
	for (int i = 0; i < this->m_data.count(); i++){
		this->m_indexOrgTank.append(i);
	}
}
/*-------------------------------------------------
		�ؼ� - ˢ�½���
*/
void P_DesignTipGeneratorPart::refreshProcess(){
	QString msg = "";
	msg.append("(");
	msg.append(QString::number(this->m_data.count() - m_indexOrgTank.count()));
	msg.append("/");
	msg.append(QString::number(this->m_data.count()));
	msg.append(")");
	ui.label_process->setText(msg);
}
/*-------------------------------------------------
		�ؼ� - ִ������
*/
void P_DesignTipGeneratorPart::doGenerate(){
	this->clearCells();

	// > ���������������¿�ʼ
	if (this->m_indexOrgTank.count() == 0){
		this->resetIndexTank();
	}

	// > ������ظ�������
	int ran_count = ui.spinBox->value();
	QList<int> curRan_list;
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	for (int i = 0; i < ran_count; i++){
		if (this->m_data.count() == 0){ break; }
		if (this->m_indexOrgTank.count() == 0){ break; }
		int ran = qrand() % this->m_indexOrgTank.count();
		curRan_list.append(this->m_indexOrgTank.at(ran));
		this->m_indexOrgTank.removeAt(ran);
	}
	//qDebug() << curRan_list;��������б�

	// > ��ӿؼ�
	for (int i = 0; i < curRan_list.count(); i++){
		int index = curRan_list.at(i);
		C_DesignTip_Cell c_cell = this->m_data.getCellByIndex(index);
		P_DesignTip_Cell* p_cell = new P_DesignTip_Cell();
		p_cell->setData(c_cell);
		this->m_cellTank.append(p_cell);
		ui.verticalLayout_tip->addWidget(p_cell);
	}

	// > ��¼�����
	this->refreshProcess();
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