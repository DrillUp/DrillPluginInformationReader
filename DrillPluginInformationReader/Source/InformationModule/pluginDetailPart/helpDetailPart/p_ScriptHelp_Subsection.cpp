#include "stdafx.h"
#include "p_ScriptHelp_Subsection.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		分段说明 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_Subsection::P_ScriptHelp_Subsection(QWidget *parent)
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

P_ScriptHelp_Subsection::~P_ScriptHelp_Subsection(){
}

/*-------------------------------------------------
		控件 - 清空全部子控件
*/
void P_ScriptHelp_Subsection::clearAllChild(){

	// > 断开连接
	for (int i = 0; i < this->m_labelTank.count(); i++){
		disconnect(this->m_labelTank.at(i));
	}

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
void P_ScriptHelp_Subsection::linkClicked(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_Subsection::setData(C_ScriptHelp_Subsection* data){
	this->clearAllChild();
	if (data == nullptr){ return; }

	// > 主内容
	QStringList main_list = data->getMainContext();
	if (main_list.count() > 0){
		QWidget* group = new QWidget(this);
		group->setObjectName("P_ScriptHelp_QWidget");
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setMargin(0);
		layout->setSpacing(6);
		group->setLayout(layout);

		for (int i = 0; i < main_list.count(); i++){
			QString temp_data = main_list.at(i);
			temp_data = S_LinkDirector::getInstance()->signLink_Docs(temp_data);

			// > 添加标签
			QLabel* label = new QLabel(temp_data, group);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			layout->addWidget(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Subsection::linkClicked);
		}
		this->layout()->addWidget(group);
	}

	// > 小章节
	QStringList title_list = data->getAllTitle();
	for (int i = 0; i < title_list.count(); i++){
		QString title = title_list.at(i);
		QGroupBox* group = new QGroupBox(this);
		group->setTitle(title);
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setSpacing(1);
		group->setLayout(layout);

		// > 小章节列表
		QStringList data_list = data->getPageContextByTitle(title);
		for (int j = 0; j < data_list.count(); j++){
			QString temp_data = data_list.at(j);
			temp_data = "> " + temp_data;

			QStringList temp_list = temp_data.split("\n");	//（直接把所有换行单独提取出来）
			for (int k = 0; k < temp_list.count(); k++){
				QString str = temp_list.at(k);
				str = S_LinkDirector::getInstance()->signLink_Docs(str);
				QLabel* label = new QLabel(str, group);
				label->setWordWrap(true);
				label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
				layout->addWidget(label);
				connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Subsection::linkClicked);
			}
		}
		this->layout()->addWidget(group);
	}
	
}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_Subsection::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_Subsection::putUiToData(){
	//（暂无）
}