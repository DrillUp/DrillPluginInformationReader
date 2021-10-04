#include "stdafx.h"
#include "p_ScriptHelp_Docs.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		����ĵ� �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
-----==========================================================-----
*/
P_ScriptHelp_Docs::P_ScriptHelp_Docs(QWidget *parent)
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

P_ScriptHelp_Docs::~P_ScriptHelp_Docs(){
}


/*-------------------------------------------------
		�ؼ� - �����ǩ
*/
void P_ScriptHelp_Docs::clearAllLabel(){

	// > �Ͽ�����
	for (int i = this->m_labelTank.count()-1; i >=0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){ continue; }
		disconnect(label);
		ui.groupBox_main->layout()->removeWidget(label);
		ui.groupBox_relative->layout()->removeWidget(label);
		label->deleteLater();
	}
	this->m_labelTank.clear();
	
}
/*-------------------------------------------------
		�ؼ� - ���ӱ����
*/
void P_ScriptHelp_Docs::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}
/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_Docs::setData(C_ScriptHelp_Docs* data){
	this->clearAllLabel();

	// > ��Ҫ�ĵ�
	if (data->main_docx.count() > 0){
		for (int i = 0; i < data->main_docx.count(); i++){
			QString temp_data = data->main_docx.at(i);
			temp_data = "�� " + temp_data;
			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, ui.groupBox_main);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			ui.groupBox_main->layout()->addWidget(label);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Docs::linkClicked_docs);
		}
	}else{
		QLabel* label = new QLabel("��", ui.groupBox_main);
		ui.groupBox_main->layout()->addWidget(label);
		this->m_labelTank.append(label);
	}

	// > ����ĵ�
	if (data->relative_docx.count() > 0){
		for (int i = 0; i < data->relative_docx.count(); i++){
			QString temp_data = data->relative_docx.at(i);
			temp_data = "�� " + temp_data;
			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, ui.groupBox_relative);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			ui.groupBox_relative->layout()->addWidget(label);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Docs::linkClicked_docs);
		}
	}
	else{
		QLabel* label = new QLabel("��", ui.groupBox_relative);
		ui.groupBox_relative->layout()->addWidget(label);
		this->m_labelTank.append(label);
	}
	
}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_Docs::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_Docs::putUiToData(){
	//�����ޣ�
}