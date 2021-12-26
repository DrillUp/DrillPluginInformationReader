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
	//----初始化参数


	//-----------------------------------
	//----控件初始化

	//-----------------------------------
	//----事件绑定

}

P_ScriptHelp_Performance::~P_ScriptHelp_Performance(){
}

/*-------------------------------------------------
		控件 - 清空全部子控件
*/
void P_ScriptHelp_Performance::clearAllChild(){

	// > 断开连接
	for (int i = this->m_labelTank.count()-1; i >=0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){continue;}
		disconnect(label);
	}
	this->m_labelTank.clear();

	// > 删除下面的全部控件
	QLayout* layout = this->layout();
	QLayoutItem *child;
	while ((child = layout->takeAt(0)) != 0){
		child->widget()->deleteLater();
	}
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_Performance::setData(C_ScriptHelp_Performance* data){
	this->clearAllChild();

	// > 全为空情况
	if (data == nullptr || data->isNull()){
		QLabel* label = new QLabel("插件没有插件性能说明。");
		label->setAlignment(Qt::AlignCenter);
		this->layout()->addWidget(label);
		return;
	}

	// > 测试结果 底板控件
	//QList<C_ScriptHelp_PerformanceTest> c_test_list = data->getTestList();
	//for (int i = 0; i < c_test_list.count(); i++){
	//	C_ScriptHelp_PerformanceTest c_test = c_test_list.at(i);
	//	QGroupBox* group = new QGroupBox(this);
	//	QVBoxLayout* layout = new QVBoxLayout(group);
	//	layout->setSpacing(2);
	//
	//}

	// > 说明内容 底板控件
	/*
	QGroupBox* group = new QGroupBox(this);
	QVBoxLayout* layout = new QVBoxLayout(group);
	layout->setSpacing(2);
	group->setTitle(c_group.group_name);
	group->setLayout(layout);

	for (int j = 0; j < data->context_note.count(); j++){
		QString temp_data = data->context_note.at(j);
		temp_data = "◆ " + temp_data;

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