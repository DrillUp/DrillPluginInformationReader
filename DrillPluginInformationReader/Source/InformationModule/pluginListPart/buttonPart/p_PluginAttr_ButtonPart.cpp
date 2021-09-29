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
P_PluginAttr_ButtonPart::P_PluginAttr_ButtonPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----初始化ui
	ui.toolButton_src->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_src.png"));
	ui.toolButton_word->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_word.png"));
	ui.toolButton_highConsumption->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_highConsumption.png"));
	ui.toolButton_hasTool->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_hasTool.png"));

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_src, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_src);

}

P_PluginAttr_ButtonPart::~P_PluginAttr_ButtonPart(){
}


/*-------------------------------------------------
		控件 - 资源按钮
*/
void P_PluginAttr_ButtonPart::btn_src(){
	
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