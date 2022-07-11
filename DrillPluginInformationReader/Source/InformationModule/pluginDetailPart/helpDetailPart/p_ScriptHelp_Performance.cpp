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
	//----�ؼ���ʼ��
	this->setData(nullptr);		//����ʼû���κ����ݣ�

	//-----------------------------------
	//----�¼���
	//���ޣ�

}

P_ScriptHelp_Performance::~P_ScriptHelp_Performance(){
}

/*-------------------------------------------------
		�ؼ� - ���ӱ����
*/
void P_ScriptHelp_Performance::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}
/*-------------------------------------------------
		�ؼ� - �������ı���ɫ
*/
QString P_ScriptHelp_Performance::decorateCostColor(QString cost){
	QString cost_str = cost;
	double cost_value = cost_str.replace(QRegExp("[^0-9e\\.]+"), "").toDouble();	//��ɸѡ���֣�
	QString result = "";
	if (cost_value >= 120){
		result.append("<span style=\"background-color:#CC6C6A;\">");
	}else if (cost_value >= 80){
		result.append("<span style=\"background-color:#E6B8B7;\">");
	}else if (cost_value >= 40){
		result.append("<span style=\"background-color:#F2DCDB;\">");
	}else{
		result.append("<span style=\"background-color:#CEF9DB;\">");
	}
	result.append("  ");
	result.append(cost);
	result.append("  ");
	result.append("</span>");
	return result;
}
/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_Performance::setData(C_ScriptHelp_Performance* data){

	// > ȫΪ�����
	if (data == nullptr || data->isNull()){
		ui.label_noData->setVisible(true);
		ui.groupBox_attr->setVisible(false);
		ui.groupBox_test->setVisible(false);
		ui.groupBox_note->setVisible(false);
		return;
	}

	ui.label_noData->setVisible(false);
	ui.groupBox_attr->setVisible(true);
	ui.groupBox_test->setVisible(true);
	ui.groupBox_note->setVisible(true);

	// > ��������
	ui.label_workingType->setText(data->working_type);
	ui.label_timeComplexity->setText(data->time_complexity);


	// > ���ܲ��� - ɾ���ؼ�
	QLayout* layout_test = ui.groupBox_test->layout();
	QLayoutItem *child_test;
	while ((child_test = layout_test->takeAt(0)) != 0){
		child_test->widget()->deleteLater();
	}

	// > ���ܲ��� - �����б�
	QList<C_ScriptHelp_PerformanceTest> test_list = data->test_list;
	for (int i = 0; i < test_list.count(); i++){
		C_ScriptHelp_PerformanceTest c_test = test_list.at(i);
		QWidget* group = new QWidget(this);
		QGridLayout* layout = new QGridLayout(group);
		layout->setSpacing(0);
		layout->setMargin(0);
		layout->setColumnStretch(0, 0);
		layout->setColumnStretch(1, 1);
		group->setLayout(layout);
		int cur_row = 0;

		// > ���Է�����������ʾ��
		if (c_test.text_method != ""){
			QLabel* label_method1 = new QLabel("���Է���" + QString::number(i + 1) + "��", group);
			QLabel* label_method2 = new QLabel(c_test.text_method.trimmed(), group);
			label_method2->setWordWrap(true);
			label_method2->setTextInteractionFlags(label_method2->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label_method2->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label_method1, cur_row, 0, 1, 1);
			layout->addWidget(label_method2, cur_row, 1, 1, 1);
			cur_row += 1;
		}

		// > ���Խ��
		QLabel* label_result1 = new QLabel("���Խ��" + QString::number(i + 1) + "��", group);
		layout->addWidget(label_result1, cur_row, 0, 1, 1);

		// > ���Խ����ϸ
		for (int j = 0; j < c_test.detail_list.count(); j++){
			C_ScriptHelp_PerformanceTestDetail d = c_test.detail_list.at(j);
			QString cost = d.cost_text;
			QString condition = d.condition_text;

			condition.append(this->decorateCostColor(cost));
			QLabel* label_2 = new QLabel(condition, group);
			label_2->setWordWrap(true);
			label_2->setTextInteractionFlags(label_2->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label_2->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label_2, cur_row, 1, 1, 1);
			cur_row += 1;
		}

		layout_test->addWidget(group);
	}


	// > ����˵�� - ɾ���ؼ�
	QLayout* layout_note = ui.groupBox_note->layout();
	QLayoutItem *child_note;
	while ((child_note = layout_note->takeAt(0)) != 0){
		child_note->widget()->deleteLater();
	}

	// > ����˵�� - ˵������
	QStringList data_list = data->context_note;
	for (int j = 0; j < data_list.count(); j++){
		QString temp_data = data_list.at(j);
		temp_data = "�� " + temp_data;

		temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
		temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);
		temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
		QLabel* label = new QLabel(temp_data, ui.groupBox_note);
		label->setWordWrap(true);
		label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
		label->setCursor(QCursor(Qt::IBeamCursor));
		layout_note->addWidget(label);
		connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Performance::linkClicked_docs);
	}

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