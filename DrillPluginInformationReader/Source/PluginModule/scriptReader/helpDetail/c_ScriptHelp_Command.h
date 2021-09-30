#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-指令 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Command{

	public:
		C_ScriptHelp_Command();
		~C_ScriptHelp_Command();

	//-----------------------------------
	//----数据
	public:
		QStringList pluginCommand;		//全部插件指令
		QStringList pluginNote;			//全部插件注释

};
