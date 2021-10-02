#include "stdafx.h"
#include "p_ScriptHelp_Docs.h"

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
		块 - 设置数据
*/
void P_ScriptHelp_Docs::setData(C_ScriptHelp_Docs* data){

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