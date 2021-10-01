#include "stdafx.h"
#include "p_PluginAttr_ButtonPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件属性 按钮块.cpp
		作者：		drill_up
		所属模块：	信息模块

		说明：		插件属性显示用的按钮块。
-----==========================================================-----
*/
P_PluginAttr_ButtonPart::P_PluginAttr_ButtonPart(W_PluginAttrComment* w, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	this->m_w_PluginAttrComment = w;

	//-----------------------------------
	//----初始化ui
	ui.toolButton_src->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_src.png"));
	ui.toolButton_word->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_word.png"));
	ui.toolButton_highConsumption->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_highConsumption.png"));
	ui.toolButton_hasTool->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_hasTool.png"));
	ui.toolButton_foreignKey->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_foreignKey.png"));

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_word, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_word);
	connect(ui.toolButton_src, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_src);
	connect(ui.toolButton_highConsumption, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_highConsumption);
	connect(ui.toolButton_hasTool, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_hasTool);
	connect(ui.toolButton_foreignKey, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_foreignKey);

}

P_PluginAttr_ButtonPart::~P_PluginAttr_ButtonPart(){
}

/*-------------------------------------------------
		控件 - 设置当前插件名
*/
void P_PluginAttr_ButtonPart::setPluginName(QString pluginName){
	this->m_pluginName = pluginName;
	this->refreshBtnVisible();
}
/*-------------------------------------------------
		控件 - 获取当前插件名
*/
QString P_PluginAttr_ButtonPart::getPluginName(){
	return this->m_pluginName;
}
/*-------------------------------------------------
		控件 - 根据属性显示按钮
*/
void P_PluginAttr_ButtonPart::refreshBtnVisible(){
	//...
}

/*-------------------------------------------------
		控件 - 资源按钮
*/
void P_PluginAttr_ButtonPart::btn_word(){
	this->m_w_PluginAttrComment->showInformation_word(this->m_pluginName);
	this->m_w_PluginAttrComment->show();
}
void P_PluginAttr_ButtonPart::btn_src(){
	this->m_w_PluginAttrComment->showInformation_src(this->m_pluginName);
	this->m_w_PluginAttrComment->show();
}
void P_PluginAttr_ButtonPart::btn_highConsumption(){
	this->m_w_PluginAttrComment->showInformation_highConsumption(this->m_pluginName);
	this->m_w_PluginAttrComment->show();
}
void P_PluginAttr_ButtonPart::btn_hasTool(){
	this->m_w_PluginAttrComment->showInformation_hasTool(this->m_pluginName);
	this->m_w_PluginAttrComment->show();
}
void P_PluginAttr_ButtonPart::btn_foreignKey(){
	this->m_w_PluginAttrComment->showInformation_foreignKey(this->m_pluginName);
	this->m_w_PluginAttrComment->show();
}


/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_PluginAttr_ButtonPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_PluginAttr_ButtonPart::putUiToData(){
	//（暂无）
}