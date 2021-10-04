#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-插件性能 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Performance{

	public:
		C_ScriptHelp_Performance();
		~C_ScriptHelp_Performance();

	//-----------------------------------
	//----数据
	public:
		QStringList performance;		//插件性能
		QStringList note;				//插件性能说明
	public:
								//数据 - 是否高消耗
		bool isHighCost();
								//数据 - 是否中消耗
		bool isMiddleCost();
								//数据 - 是否低消耗
		bool isLowCost();

};
