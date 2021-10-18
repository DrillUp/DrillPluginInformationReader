#include "stdafx.h"
#include "c_ScriptHelp_PluginRelation.h"


/*
-----==========================================================-----
		类：		帮助数据-插件扩展 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_PluginRelation::C_ScriptHelp_PluginRelation(){
	this->base = QStringList();
	this->beingExtend = QStringList();
	this->effectTo = QStringList();
}
C_ScriptHelp_PluginRelation::~C_ScriptHelp_PluginRelation(){
}


/*-------------------------------------------------
		数据 - 读取 插件扩展 字符串
*/
void C_ScriptHelp_PluginRelation::readPluginRelation(QString relation_context){


	//...
}
