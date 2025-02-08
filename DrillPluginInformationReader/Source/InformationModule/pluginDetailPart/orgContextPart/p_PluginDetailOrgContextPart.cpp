#include "stdafx.h"
#include "p_PluginDetailOrgContextPart.h"

#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		类：		原文展开 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	原文展开的编辑块结构。
-----==========================================================-----
*/
P_PluginDetailOrgContextPart::P_PluginDetailOrgContextPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}

P_PluginDetailOrgContextPart::~P_PluginDetailOrgContextPart(){
}

/*-------------------------------------------------
		控件 - 设置文本
*/
void P_PluginDetailOrgContextPart::setContext(QString context){
	ui.plainTextEdit->setPlainText(context);
}

/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_PluginDetailOrgContextPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_PluginDetailOrgContextPart::putUiToData(){
	//（暂无）
}