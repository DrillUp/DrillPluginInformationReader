#include "stdafx.h"
#include "p_ScriptHelp_Docs.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件文档 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_Docs::P_ScriptHelp_Docs(QWidget *parent)
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

P_ScriptHelp_Docs::~P_ScriptHelp_Docs(){
}


/*-------------------------------------------------
		控件 - 清除标签
*/
void P_ScriptHelp_Docs::clearAllLabel(){

	// > 断开连接
	for (int i = this->m_labelTank.count()-1; i >=0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){ continue; }
		disconnect(label);
		ui.groupBox_main->layout()->removeWidget(label);
		ui.groupBox_relative->layout()->removeWidget(label);
		label->deleteLater();
	}
	this->m_labelTank.clear();
	
}
/*-------------------------------------------------
		控件 - 链接被点击
*/
void P_ScriptHelp_Docs::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}
/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_Docs::setData(C_ScriptHelp_Docs* data){
	this->clearAllLabel();

	// > 主要文档
	if (data->main_docx.count() > 0){
		for (int i = 0; i < data->main_docx.count(); i++){
			QString temp_data = data->main_docx.at(i);
			temp_data = "◆ " + temp_data;
			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, ui.groupBox_main);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			ui.groupBox_main->layout()->addWidget(label);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Docs::linkClicked_docs);
		}
	}else{
		QLabel* label = new QLabel("无", ui.groupBox_main);
		ui.groupBox_main->layout()->addWidget(label);
		this->m_labelTank.append(label);
	}

	// > 相关文档
	if (data->relative_docx.count() > 0){
		for (int i = 0; i < data->relative_docx.count(); i++){
			QString temp_data = data->relative_docx.at(i);
			temp_data = "◆ " + temp_data;
			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, ui.groupBox_relative);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			ui.groupBox_relative->layout()->addWidget(label);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Docs::linkClicked_docs);
		}
	}
	else{
		QLabel* label = new QLabel("无", ui.groupBox_relative);
		ui.groupBox_relative->layout()->addWidget(label);
		this->m_labelTank.append(label);
	}
	
}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_Docs::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_Docs::putUiToData(){
	//（暂无）
}