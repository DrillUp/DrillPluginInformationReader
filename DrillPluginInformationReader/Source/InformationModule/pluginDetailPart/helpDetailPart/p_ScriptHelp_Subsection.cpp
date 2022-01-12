#include "stdafx.h"
#include "p_ScriptHelp_Subsection.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		�ֶ�˵�� �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
-----==========================================================-----
*/
P_ScriptHelp_Subsection::P_ScriptHelp_Subsection(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_labelTank = QList<QLabel*>();

	//-----------------------------------
	//----�ؼ���ʼ��
	this->setData(nullptr);		//����ʼû���κ����ݣ�

	//-----------------------------------
	//----�¼���
	//���ޣ�

}

P_ScriptHelp_Subsection::~P_ScriptHelp_Subsection(){
}

/*-------------------------------------------------
		�ؼ� - ���ȫ���ӿؼ�
*/
void P_ScriptHelp_Subsection::clearAllChild(){

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
void P_ScriptHelp_Subsection::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}

/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_Subsection::setData(C_ScriptHelp_Subsection* data){
	this->clearAllChild();

	// > ȫΪ�����
	if (data == nullptr || data->isSubsectionNull() ){
		QLabel* label = new QLabel("���û���κ�����˵����");
		label->setAlignment(Qt::AlignCenter);
		this->layout()->addWidget(label);
		return;
	}

	// > ���� �װ�ؼ�
	QStringList main_list = data->getMainContext();
	if (main_list.count() > 0){
		QWidget* group = new QWidget(this);
		group->setObjectName("P_ScriptHelp_QWidget");
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setMargin(0);
		layout->setSpacing(6);
		group->setLayout(layout);

		// > ���� - �����б�
		QStringList condition_list = data->getHeader().condition;
		for (int i = 0; i < condition_list.count(); i++){
			QString temp_data = condition_list.at(i);
			temp_data = S_LinkDirector::getInstance()->signLtGtTag(temp_data);
			temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);

			// > ��ӱ�ǩ
			QLabel* label = new QLabel(temp_data, group);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label);
			this->m_labelTank.append(label);
		}

		// > �������б�
		for (int i = 0; i < main_list.count(); i++){
			QString temp_data = main_list.at(i);
			temp_data = S_LinkDirector::getInstance()->signLtGtTag(temp_data);
			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);	//���ĵ����ӣ�
			temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);

			// > ��ӱ�ǩ
			QLabel* label = new QLabel(temp_data, group);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Subsection::linkClicked_docs);
		}
		this->layout()->addWidget(group);
	}

	// > С�½� �װ�ؼ�
	QStringList title_list = data->getAllTitle();
	for (int i = 0; i < title_list.count(); i++){
		QString title = title_list.at(i);
		QGroupBox* group = new QGroupBox(this);
		group->setTitle(title);
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setSpacing(1);
		group->setLayout(layout);

		// > С�½��б�
		QStringList data_list = data->getPageContextByTitle(title);
		for (int j = 0; j < data_list.count(); j++){
			QString temp_data = data_list.at(j);
			temp_data = "�� " + temp_data;

			temp_data = S_LinkDirector::getInstance()->signLtGtTag(temp_data);
			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
			temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, group);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Subsection::linkClicked_docs);

			//QStringList temp_list = temp_data.split("\n");	//��ֱ�Ӱ������е������Label��
			//for (int k = 0; k < temp_list.count(); k++){
			//	QString str = temp_list.at(k);
			//	str = S_LinkDirector::getInstance()->signLtGtTag(str);
			//	str = S_LinkDirector::getInstance()->signATag_Docs(str);
			//	QLabel* label = new QLabel(str, group);
			//	label->setWordWrap(true);
			//	label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			//	label->setCursor(QCursor(Qt::IBeamCursor));
			//	layout->addWidget(label);
			//	this->m_labelTank.append(label);
			//	connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Subsection::linkClicked);
			//}
		}
		this->layout()->addWidget(group);
	}

}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_Subsection::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_Subsection::putUiToData(){
	//�����ޣ�
}