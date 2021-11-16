#include "stdafx.h"
#include "p_ScriptHelp_Command.h"

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
P_ScriptHelp_Command::P_ScriptHelp_Command(QWidget *parent)
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

P_ScriptHelp_Command::~P_ScriptHelp_Command(){
}

/*-------------------------------------------------
		�ؼ� - ���ȫ���ӿؼ�
*/
void P_ScriptHelp_Command::clearAllChild(){

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
void P_ScriptHelp_Command::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}

/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_Command::setData(C_ScriptHelp_Command* data){
	this->clearAllChild();

	// > ȫΪ�����
	if (data == nullptr || data->isNull()){
		QLabel* label = new QLabel("���û���κ�ָ��˵����");
		label->setAlignment(Qt::AlignCenter);
		this->layout()->addWidget(label);
		return;
	}

	// > ָ���� �װ�ؼ�
	QList<C_ScriptHelp_CommandGroup> c_group_list = data->getGroupList();
	for (int i = 0; i < c_group_list.count(); i++){
		C_ScriptHelp_CommandGroup c_group = c_group_list.at(i);
		QGroupBox* group = new QGroupBox(this);
		group->setTitle(c_group.getGroupFullName());
		QGridLayout* layout = new QGridLayout(group);
		layout->setSpacing(2);
		layout->setColumnStretch(1, 1);
		group->setLayout(layout);

		// > ָ����
		int cur_row = 0;
		QStringList tag_list = c_group.getGrid_TagList();
		QStringList command_list = c_group.getGrid_CommandList();
		for (int j = 0; j < tag_list.count(); j++){
			QString tag = tag_list.at(j);
			QString command = command_list.at(j);

			// > ָ�� - ��ǩͷ
			QLabel* label_tag = new QLabel(tag, group);
			label_tag->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
			layout->addWidget(label_tag, cur_row, 0, 1, 1);
			this->m_labelTank.append(label_tag);

			// > ָ�� - ����ָ��
			if (command != ""){
				QLabel* label_command = new QLabel(command, group);
				label_command->setWordWrap(true);
				label_command->setTextInteractionFlags(label_command->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
				label_command->setStyleSheet("background-color: rgb(255, 255, 255);");
				layout->addWidget(label_command, cur_row, 1, 1, 1);
				this->m_labelTank.append(label_command);
			}

			cur_row += 1;
		}

		// > ����
		QWidget* widget_empty = new QWidget(group);
		widget_empty->setMinimumHeight(10);
		layout->addWidget(widget_empty, cur_row, 0, 1, 2);
		cur_row += 1;

		// > ָ����˵������
		QStringList data_list = c_group.note_context;
		for (int j = 0; j < data_list.count(); j++){
			QString temp_data = data_list.at(j);
			temp_data = "�� " + temp_data;

			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
			temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, group);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			layout->addWidget(label, cur_row, 0, 1, 2);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Command::linkClicked_docs);
			cur_row += 1;
		}
		this->layout()->addWidget(group);
	}
}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_Command::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_Command::putUiToData(){
	//�����ޣ�
}