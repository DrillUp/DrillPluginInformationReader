#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-插件扩展 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_PluginRelation{

	public:
		C_ScriptHelp_PluginRelation();
		~C_ScriptHelp_PluginRelation();

	//-----------------------------------
	//----数据
	public:
		QStringList base;			//插件扩展 - 基于
		QStringList beingExtend;	//插件扩展 - 可被扩展/可扩展
		QStringList effectTo;		//插件扩展 - 可作用于/作用于
	public:

};
