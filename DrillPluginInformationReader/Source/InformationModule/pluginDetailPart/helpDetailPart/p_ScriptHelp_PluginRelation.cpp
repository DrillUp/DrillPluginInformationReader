#include "stdafx.h"
#include "p_ScriptHelp_PluginRelation.h"

#include "drillplugininformationreader.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		�����չ �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
-----==========================================================-----
*/
P_ScriptHelp_PluginRelation::P_ScriptHelp_PluginRelation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�ؼ���ʼ��
	this->setData(nullptr);		//����ʼû���κ����ݣ�

	//-----------------------------------
	//----�¼���
	//���ޣ�

}

P_ScriptHelp_PluginRelation::~P_ScriptHelp_PluginRelation(){
}


/*-------------------------------------------------
		�ؼ� - ���ȫ���ӿؼ�
*/
void P_ScriptHelp_PluginRelation::clearAllChild(){

	// > �Ͽ�����
	for (int i = this->m_labelTank.count()-1; i >=0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){continue;}
		disconnect(label);
	}
	this->m_labelTank.clear();

	// > ɾ�������ȫ���ؼ�
	QLayout* layout = ui.verticalLayout_main;
	QLayoutItem *child;
	while ((child = layout->takeAt(0)) != 0){
		child->widget()->deleteLater();
	}
}
/*-------------------------------------------------
		�ؼ� - ���ӱ����
*/
void P_ScriptHelp_PluginRelation::linkClicked_plugin(QString data){
	DrillPluginInformationReader::getInstance()->showPluginDetail(data);
}
/*-------------------------------------------------
		�ؼ� - ����Ⱥ��ؼ�
*/
void P_ScriptHelp_PluginRelation::addGroupWidget(QString title, QStringList context){
	QGroupBox* group = new QGroupBox(this);
	group->setTitle(title);
	QVBoxLayout* layout = new QVBoxLayout(group);
	layout->setSpacing(1);
	group->setLayout(layout);

	QString temp_data = context.join("\n");
	temp_data = S_LinkDirector::getInstance()->signLtGtTag(temp_data);
	temp_data = S_LinkDirector::getInstance()->signATag_Plugin(temp_data);
	temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);
	temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
	QLabel* label = new QLabel(temp_data, group);
	label->setWordWrap(true);
	label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
	layout->addWidget(label);
	this->m_labelTank.append(label);
	connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_PluginRelation::linkClicked_plugin);

	ui.verticalLayout_main->addWidget(group);
}


/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_PluginRelation::setData(C_ScriptHelp_PluginRelation* data){
	this->clearAllChild();

	// > ȫΪ�����
	if (data == nullptr || data->isNull()){
		ui.stackedWidget->setCurrentIndex(0);
		ui.page_2->setVisible(false);
		return;
	}
	ui.page_2->setVisible(true);
	ui.stackedWidget->setCurrentIndex(1);

	// > ������ �װ�ؼ�
	QStringList main_list = data->getMainContext();
	if (main_list.count() > 0){
		QWidget* group = new QWidget(this);
		group->setObjectName("P_ScriptHelp_QWidget");
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setMargin(0);
		layout->setSpacing(6);
		group->setLayout(layout);

		// > ������˵��
		QLabel* label = new QLabel(main_list.join("\n"), group);
		label->setWordWrap(true);
		label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
		layout->addWidget(label);
		this->m_labelTank.append(label);

		ui.verticalLayout_main->addWidget(group);
	}

	// > ��չ�� ����
	QStringList data_baseOn_list = data->getContextByBaseOn();
	if (data_baseOn_list.count() > 0){
		this->addGroupWidget("����", data_baseOn_list);
	}

	// > ��չ�� ��������
	QStringList data_effectTo_list = data->getContextByEffectTo();
	if (data_effectTo_list.count() > 0){
		this->addGroupWidget("��������", data_effectTo_list);
	}

	// > ��չ�� �ɱ���չ
	QStringList data_beingExtend_list = data->getContextByBeingExtend();
	if (data_beingExtend_list.count() > 0){
		this->addGroupWidget("�ɱ���չ", data_beingExtend_list);
	}

	// > ��չ�� ����
	QStringList data_Other_list = data->getContextByOther();
	if (data_Other_list.count() > 0){
		this->addGroupWidget("����", data_Other_list);
	}

}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_PluginRelation::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_PluginRelation::putUiToData(){
	//�����ޣ�
}