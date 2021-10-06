#include "stdafx.h"
#include "p_ScriptHelp_Src.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��Դ·�� �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
-----==========================================================-----
*/
P_ScriptHelp_Src::P_ScriptHelp_Src(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_labelTank = QList<QLabel*>();

	//-----------------------------------
	//----�¼���
	connect(ui.label_context, &QLabel::linkActivated, this, &P_ScriptHelp_Src::linkClicked_specific_pluginListing);

}

P_ScriptHelp_Src::~P_ScriptHelp_Src(){
}

/*-------------------------------------------------
		�ؼ� - ���ȫ���ӿؼ�
*/
void P_ScriptHelp_Src::clearAllChild(){

	// > �Ͽ�����
	for (int i = this->m_labelTank.count() - 1; i >= 0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){ continue; }
		disconnect(label);
		ui.groupBox_src->layout()->removeWidget(label);
		label->deleteLater();
	}
	this->m_labelTank.clear();

}
/*-------------------------------------------------
		�ؼ� - ���ӱ����
*/
void P_ScriptHelp_Src::linkClicked_src(QString data){
	S_LinkDirector::getInstance()->openLink_Src(data);
}
/*-------------------------------------------------
		�ؼ� - ����"����嵥.xlsx"�����
*/
void P_ScriptHelp_Src::linkClicked_specific_pluginListing(QString data){
	S_LinkDirector::getInstance()->openLink_specific_pluginListing();
}

/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_Src::setData(C_ScriptHelp_Src* data){
	this->clearAllChild();
	if (data == nullptr){
		ui.stackedWidget->setCurrentIndex(0); 
		ui.label_context->setVisible(false);		//����ֹ�ſ���
		ui.plainTextEdit_sample->setVisible(false);
		return;
	}

	// > ��Ҫ�ĵ�
	if (data->src_list.count() > 0){
		ui.stackedWidget->setCurrentIndex(1);
		ui.label_context->setVisible(true);
		ui.plainTextEdit_sample->setVisible(true);
		
		// > ·��
		for (int i = 0; i < data->src_list.count(); i++){
			QString temp_data = data->src_list.at(i);
			temp_data = S_LinkDirector::getInstance()->signATag_Src(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, ui.groupBox_src);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			ui.groupBox_src->layout()->addWidget(label);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Src::linkClicked_src);
		}

		// > ����
		QString context = data->context;
		context = S_LinkDirector::getInstance()->signATag_specific_pluginListing(context);
		context = S_LinkDirector::getInstance()->signBrTag(context);
		context = S_LinkDirector::getInstance()->signPTag(context);
		ui.label_context->setText(context);
		ui.plainTextEdit_sample->setPlainText(data->example);

	}else{
		ui.stackedWidget->setCurrentIndex(0);
		ui.label_context->setVisible(false);		//����ֹ�ſ���
		ui.plainTextEdit_sample->setVisible(false);
	}
}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_Src::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_Src::putUiToData(){
	//�����ޣ�
}