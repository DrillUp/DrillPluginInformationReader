#include "stdafx.h"
#include "C_ScriptHelp_Src.h"


/*
-----==========================================================-----
		类：		帮助数据-资源路径 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Src::C_ScriptHelp_Src(){
	this->src_list = QStringList();				//资源路径
	this->context = QString();					//路径说明
	this->example = QString();					//举例说明
}
C_ScriptHelp_Src::~C_ScriptHelp_Src(){
}

