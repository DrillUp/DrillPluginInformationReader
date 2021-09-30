#include "stdafx.h"
#include "c_ScriptHelp_Command.h"


/*
-----==========================================================-----
		类：		帮助数据-指令 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Command::C_ScriptHelp_Command(){
	this->pluginCommand = QStringList();
	this->pluginNote = QStringList();
}
C_ScriptHelp_Command::~C_ScriptHelp_Command(){
}


