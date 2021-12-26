#include "stdafx.h"
#include "p_ScriptHelp_Performance.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������� �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
-----==========================================================-----
*/
P_ScriptHelp_Performance::P_ScriptHelp_Performance(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��

	//-----------------------------------
	//----�¼���

}

P_ScriptHelp_Performance::~P_ScriptHelp_Performance(){
}

/*-------------------------------------------------
		�ؼ� - ���ȫ���ӿؼ�
*/
void P_ScriptHelp_Performance::clearAllChild(){

	// > �Ͽ�����
	for (int i = this->m_labelTank.count()-1; i >=0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){continue;}
		disconnect(label);
	}
	this->m_labelTank.clear();

	// > ɾ�������ȫ���ؼ�
	QLayout* layout = this->layout();
	QLayoutItem *child;
	while ((child = layout->takeAt(0)) != 0){
		child->widget()->deleteLater();
	}
}

/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_Performance::setData(C_ScriptHelp_Performance* data){
	this->clearAllChild();

	// > ȫΪ�����
	if (data == nullptr || data->isNull()){
		QLabel* label = new QLabel("���û�в������˵����");
		label->setAlignment(Qt::AlignCenter);
		this->layout()->addWidget(label);
		return;
	}

	// > ���Խ�� �װ�ؼ�
	//QList<C_ScriptHelp_PerformanceTest> c_test_list = data->getTestList();
	//for (int i = 0; i < c_test_list.count(); i++){
	//	C_ScriptHelp_PerformanceTest c_test = c_test_list.at(i);
	//	QGroupBox* group = new QGroupBox(this);
	//	QVBoxLayout* layout = new QVBoxLayout(group);
	//	layout->setSpacing(2);
	//
	//}

	// > ˵������ �װ�ؼ�
	/*
	QGroupBox* group = new QGroupBox(this);
	QVBoxLayout* layout = new QVBoxLayout(group);
	layout->setSpacing(2);
	group->setTitle(c_group.group_name);
	group->setLayout(layout);

	for (int j = 0; j < data->context_note.count(); j++){
		QString temp_data = data->context_note.at(j);
		temp_data = "�� " + temp_data;

		temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
		temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);
		temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
		QLabel* label = new QLabel(temp_data, group);
		label->setWordWrap(true);
		label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
		label->setCursor(QCursor(Qt::IBeamCursor));
		layout->addWidget(label);
		this->m_labelTank.append(label);
		connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Knowledge::linkClicked_docs);
	}
	this->layout()->addWidget(group);
	*/

}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_Performance::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_Performance::putUiToData(){
	//�����ޣ�
}