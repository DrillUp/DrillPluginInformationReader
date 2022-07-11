#include "stdafx.h"
#include "p_ScriptHelp_Performance.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件性能 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_Performance::P_ScriptHelp_Performance(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----控件初始化
	this->setData(nullptr);		//（初始没有任何数据）

	//-----------------------------------
	//----事件绑定
	//（无）

}

P_ScriptHelp_Performance::~P_ScriptHelp_Performance(){
}

/*-------------------------------------------------
		控件 - 链接被点击
*/
void P_ScriptHelp_Performance::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}
/*-------------------------------------------------
		控件 - 给消耗文本上色
*/
QString P_ScriptHelp_Performance::decorateCostColor(QString cost){
	QString cost_str = cost;
	double cost_value = cost_str.replace(QRegExp("[^0-9e\\.]+"), "").toDouble();	//（筛选数字）
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
		块 - 设置数据
*/
void P_ScriptHelp_Performance::setData(C_ScriptHelp_Performance* data){

	// > 全为空情况
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

	// > 性能属性
	ui.label_workingType->setText(data->working_type);
	ui.label_timeComplexity->setText(data->time_complexity);


	// > 性能测试 - 删除控件
	QLayout* layout_test = ui.groupBox_test->layout();
	QLayoutItem *child_test;
	while ((child_test = layout_test->takeAt(0)) != 0){
		child_test->widget()->deleteLater();
	}

	// > 性能测试 - 测试列表
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

		// > 测试方法（有则显示）
		if (c_test.text_method != ""){
			QLabel* label_method1 = new QLabel("测试方法" + QString::number(i + 1) + "：", group);
			QLabel* label_method2 = new QLabel(c_test.text_method.trimmed(), group);
			label_method2->setWordWrap(true);
			label_method2->setTextInteractionFlags(label_method2->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label_method2->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label_method1, cur_row, 0, 1, 1);
			layout->addWidget(label_method2, cur_row, 1, 1, 1);
			cur_row += 1;
		}

		// > 测试结果
		QLabel* label_result1 = new QLabel("测试结果" + QString::number(i + 1) + "：", group);
		layout->addWidget(label_result1, cur_row, 0, 1, 1);

		// > 测试结果详细
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


	// > 性能说明 - 删除控件
	QLayout* layout_note = ui.groupBox_note->layout();
	QLayoutItem *child_note;
	while ((child_note = layout_note->takeAt(0)) != 0){
		child_note->widget()->deleteLater();
	}

	// > 性能说明 - 说明内容
	QStringList data_list = data->context_note;
	for (int j = 0; j < data_list.count(); j++){
		QString temp_data = data_list.at(j);
		temp_data = "◆ " + temp_data;

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
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_Performance::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_Performance::putUiToData(){
	//（暂无）
}