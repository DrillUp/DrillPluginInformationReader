#include "stdafx.h"
#include "p_ScriptHelp_Knowledge.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		ָ�� �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
-----==========================================================-----
*/
P_ScriptHelp_Knowledge::P_ScriptHelp_Knowledge(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	this->clearAllChild();

	//-----------------------------------
	//----�¼���

}

P_ScriptHelp_Knowledge::~P_ScriptHelp_Knowledge(){
}

/*-------------------------------------------------
		�ؼ� - ���ȫ���ӿؼ�
*/
void P_ScriptHelp_Knowledge::clearAllChild(){

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
		�ؼ� - ���ӱ����
*/
void P_ScriptHelp_Knowledge::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}

/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_Knowledge::setData(C_ScriptHelp_Knowledge* data){
	this->clearAllChild();

	// > ȫΪ�����
	if (data == nullptr || data->isNull()){
		QLabel* label = new QLabel("���û���κ�֪ʶ��˵����");
		label->setAlignment(Qt::AlignCenter);
		this->layout()->addWidget(label);
		return;
	}

	// > ֪ʶ�� �װ�ؼ�
	QList<C_ScriptHelp_KnowledgeGroup> c_group_list = data->getGroupList();
	for (int i = 0; i < c_group_list.count(); i++){
		C_ScriptHelp_KnowledgeGroup c_group = c_group_list.at(i);
		QGroupBox* group = new QGroupBox(this);
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setSpacing(2);
		group->setTitle(c_group.group_name);
		group->setLayout(layout);

		// > ����ȫ��
		QStringList data_list = c_group.context_data;
		for (int j = 0; j < data_list.count(); j++){
			QString temp_data = data_list.at(j);
			QLabel* label = new QLabel(temp_data, group);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label);
			this->m_labelTank.append(label);
		}

		// > ����
		QStringList data_list2 = c_group.context_note;
		if (data_list2.count() > 0){
			QWidget* widget_empty = new QWidget(group);
			widget_empty->setMinimumHeight(10);
			layout->addWidget(widget_empty);
		}

		// > ˵������
		for (int j = 0; j < data_list2.count(); j++){
			QString temp_data = data_list2.at(j);
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
	}
}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_Knowledge::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_Knowledge::putUiToData(){
	//�����ޣ�
}