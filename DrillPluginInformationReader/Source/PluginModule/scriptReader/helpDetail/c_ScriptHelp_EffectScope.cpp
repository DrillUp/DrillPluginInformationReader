#include "stdafx.h"
#include "c_ScriptHelp_EffectScope.h"


/*
-----==========================================================-----
		类：		帮助数据-作用域 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_EffectScope::C_ScriptHelp_EffectScope(){
	this->scope_list = QStringList();
	this->comments = "";
}
C_ScriptHelp_EffectScope::~C_ScriptHelp_EffectScope(){
}

/*-------------------------------------------------
		数据 - 可作用于地图界面
*/
bool C_ScriptHelp_EffectScope::isEnableSenceMap(){
	return this->scope_list.contains("地图界面");
}
/*-------------------------------------------------
		数据 - 可作用于战斗界面
*/
bool C_ScriptHelp_EffectScope::isEnableSenceBattle(){
	return this->scope_list.contains("战斗界面");
}
/*-------------------------------------------------
		数据 - 可作用于菜单界面
*/
bool C_ScriptHelp_EffectScope::isEnableSenceMenu(){
	return this->scope_list.contains("菜单界面");
}
/*-------------------------------------------------
		数据 - 除此三种类型以外的界面
*/
QStringList C_ScriptHelp_EffectScope::getOtherSence(){
	QStringList result = QStringList();
	for (int i = 0; i < this->scope_list.count(); i++){
		QString data = this->scope_list.at(i);
		if (data == "地图界面"){ continue; }
		if (data == "战斗界面"){ continue; }
		if (data == "菜单界面"){ continue; }
		result.append(data);
	}
	return result;
}

