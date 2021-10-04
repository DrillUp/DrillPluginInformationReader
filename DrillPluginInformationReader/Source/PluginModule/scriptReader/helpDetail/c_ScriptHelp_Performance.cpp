#include "stdafx.h"
#include "c_ScriptHelp_Performance.h"


/*
-----==========================================================-----
		类：		帮助数据-插件性能 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Performance::C_ScriptHelp_Performance(){
	this->performance = QStringList();
	this->note = QStringList();
}
C_ScriptHelp_Performance::~C_ScriptHelp_Performance(){
}



//数据 - 是否高消耗
bool C_ScriptHelp_Performance::isHighCost(){
	return false;
}
//数据 - 是否中消耗
bool C_ScriptHelp_Performance::isMiddleCost(){
	return false;
}
//数据 - 是否低消耗
bool C_ScriptHelp_Performance::isLowCost(){
	return false;
}