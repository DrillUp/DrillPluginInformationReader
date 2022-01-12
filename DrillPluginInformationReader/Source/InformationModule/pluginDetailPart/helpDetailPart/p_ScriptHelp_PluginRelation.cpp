#include "stdafx.h"
#include "p_ScriptHelp_PluginRelation.h"

#include "drillplugininformationreader.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件扩展 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_PluginRelation::P_ScriptHelp_PluginRelation(QWidget *parent)
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

P_ScriptHelp_PluginRelation::~P_ScriptHelp_PluginRelation(){
}


/*-------------------------------------------------
		控件 - 清空全部子控件
*/
void P_ScriptHelp_PluginRelation::clearAllChild(){

	// > 断开连接
	for (int i = this->m_labelTank.count()-1; i >=0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){continue;}
		disconnect(label);
	}
	this->m_labelTank.clear();

	// > 删除下面的全部控件
	QLayout* layout = ui.verticalLayout_main;
	QLayoutItem *child;
	while ((child = layout->takeAt(0)) != 0){
		child->widget()->deleteLater();
	}
}
/*-------------------------------------------------
		控件 - 链接被点击
*/
void P_ScriptHelp_PluginRelation::linkClicked_plugin(QString data){
	DrillPluginInformationReader::getInstance()->showPluginDetail(data);
}
/*-------------------------------------------------
		控件 - 创建群组控件
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
		块 - 设置数据
*/
void P_ScriptHelp_PluginRelation::setData(C_ScriptHelp_PluginRelation* data){
	this->clearAllChild();

	// > 全为空情况
	if (data == nullptr || data->isNull()){
		ui.stackedWidget->setCurrentIndex(0);
		ui.page_2->setVisible(false);
		return;
	}
	ui.page_2->setVisible(true);
	ui.stackedWidget->setCurrentIndex(1);

	// > 主内容 底板控件
	QStringList main_list = data->getMainContext();
	if (main_list.count() > 0){
		QWidget* group = new QWidget(this);
		group->setObjectName("P_ScriptHelp_QWidget");
		QVBoxLayout* layout = new QVBoxLayout(group);
		layout->setMargin(0);
		layout->setSpacing(6);
		group->setLayout(layout);

		// > 主内容说明
		QLabel* label = new QLabel(main_list.join("\n"), group);
		label->setWordWrap(true);
		label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
		layout->addWidget(label);
		this->m_labelTank.append(label);

		ui.verticalLayout_main->addWidget(group);
	}

	// > 扩展组 基于
	QStringList data_baseOn_list = data->getContextByBaseOn();
	if (data_baseOn_list.count() > 0){
		this->addGroupWidget("基于", data_baseOn_list);
	}

	// > 扩展组 可作用于
	QStringList data_effectTo_list = data->getContextByEffectTo();
	if (data_effectTo_list.count() > 0){
		this->addGroupWidget("可作用于", data_effectTo_list);
	}

	// > 扩展组 可被扩展
	QStringList data_beingExtend_list = data->getContextByBeingExtend();
	if (data_beingExtend_list.count() > 0){
		this->addGroupWidget("可被扩展", data_beingExtend_list);
	}

	// > 扩展组 其它
	QStringList data_Other_list = data->getContextByOther();
	if (data_Other_list.count() > 0){
		this->addGroupWidget("其他", data_Other_list);
	}

}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_PluginRelation::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_PluginRelation::putUiToData(){
	//（暂无）
}