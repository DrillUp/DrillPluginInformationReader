#include "stdafx.h"
#include "p_ScriptHelp_Knowledge.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		指令 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_Knowledge::P_ScriptHelp_Knowledge(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----控件初始化
	this->clearAllChild();

	//-----------------------------------
	//----事件绑定

}

P_ScriptHelp_Knowledge::~P_ScriptHelp_Knowledge(){
}

/*-------------------------------------------------
		控件 - 清空全部子控件
*/
void P_ScriptHelp_Knowledge::clearAllChild(){

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
		控件 - 链接被点击
*/
void P_ScriptHelp_Knowledge::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_Knowledge::setData(C_ScriptHelp_Knowledge* data){
	this->clearAllChild();

	// > 全为空情况
	if (data == nullptr || data->isNull()){
		QLabel* label = new QLabel("插件没有任何知识点说明。");
		label->setAlignment(Qt::AlignCenter);
		this->layout()->addWidget(label);
		return;
	}

	// > 知识点 底板控件
	QList<C_ScriptHelp_KnowledgeGroup> c_group_list = data->getGroupList();
	for (int i = 0; i < c_group_list.count(); i++){
		C_ScriptHelp_KnowledgeGroup c_group = c_group_list.at(i);
		QGroupBox* group = new QGroupBox(this);
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setSpacing(2);
		group->setTitle(c_group.group_name);
		group->setLayout(layout);

		// > 内容全文
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

		// > 空行
		QStringList data_list2 = c_group.context_note;
		if (data_list2.count() > 0){
			QWidget* widget_empty = new QWidget(group);
			widget_empty->setMinimumHeight(10);
			layout->addWidget(widget_empty);
		}

		// > 说明内容
		for (int j = 0; j < data_list2.count(); j++){
			QString temp_data = data_list2.at(j);
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
	}
}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_Knowledge::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_Knowledge::putUiToData(){
	//（暂无）
}