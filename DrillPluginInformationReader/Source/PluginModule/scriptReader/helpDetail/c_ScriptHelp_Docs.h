#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-插件文档 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Docs{

	public:
		C_ScriptHelp_Docs();
		~C_ScriptHelp_Docs();

	//-----------------------------------
	//----数据
	public:
		QStringList main_docx;		//主要帮助文档
		QStringList relative_docx;	//相关帮助文档

};
