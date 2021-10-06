#include "stdafx.h"
#include "p_ScriptHelp_Src.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		资源路径 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_Src::P_ScriptHelp_Src(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	this->m_labelTank = QList<QLabel*>();

	//-----------------------------------
	//----事件绑定
	connect(ui.label_context, &QLabel::linkActivated, this, &P_ScriptHelp_Src::linkClicked_specific_pluginListing);

}

P_ScriptHelp_Src::~P_ScriptHelp_Src(){
}

/*-------------------------------------------------
		控件 - 清空全部子控件
*/
void P_ScriptHelp_Src::clearAllChild(){

	// > 断开连接
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
		控件 - 链接被点击
*/
void P_ScriptHelp_Src::linkClicked_src(QString data){
	S_LinkDirector::getInstance()->openLink_Src(data);
}
/*-------------------------------------------------
		控件 - 链接"插件清单.xlsx"被点击
*/
void P_ScriptHelp_Src::linkClicked_specific_pluginListing(QString data){
	S_LinkDirector::getInstance()->openLink_specific_pluginListing();
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_Src::setData(C_ScriptHelp_Src* data){
	this->clearAllChild();
	if (data == nullptr){
		ui.stackedWidget->setCurrentIndex(0); 
		ui.label_context->setVisible(false);		//（防止撑开）
		ui.plainTextEdit_sample->setVisible(false);
		return;
	}

	// > 主要文档
	if (data->src_list.count() > 0){
		ui.stackedWidget->setCurrentIndex(1);
		ui.label_context->setVisible(true);
		ui.plainTextEdit_sample->setVisible(true);
		
		// > 路径
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

		// > 内容
		QString context = data->context;
		context = S_LinkDirector::getInstance()->signATag_specific_pluginListing(context);
		context = S_LinkDirector::getInstance()->signBrTag(context);
		context = S_LinkDirector::getInstance()->signPTag(context);
		ui.label_context->setText(context);
		ui.plainTextEdit_sample->setPlainText(data->example);

	}else{
		ui.stackedWidget->setCurrentIndex(0);
		ui.label_context->setVisible(false);		//（防止撑开）
		ui.plainTextEdit_sample->setVisible(false);
	}
}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_Src::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_Src::putUiToData(){
	//（暂无）
}