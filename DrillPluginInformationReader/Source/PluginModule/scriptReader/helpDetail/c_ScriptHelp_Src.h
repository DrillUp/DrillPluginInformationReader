#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-资源路径 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Src{

	public:
		C_ScriptHelp_Src();
		~C_ScriptHelp_Src();

	//-----------------------------------
	//----数据
	public:
		QStringList src_list;		//资源路径
		QString context;			//路径说明
		QString example;			//举例说明

	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 资源路径 字符串
		void readSrc(QStringList src_contextRows);

};
