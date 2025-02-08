#include "stdafx.h"
#include "C_ScriptHelp_EffectScope.h"

#include "S_Const_EffectScope.h"

/*
-----==========================================================-----
		类：		帮助数据-作用域 数据类.cpp
		作者：		drill_up
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
bool C_ScriptHelp_EffectScope::isEnableSceneMap(){
	return this->scope_list.contains(S_Const_EffectScope::getInstance()->getSceneName_Map());
}
/*-------------------------------------------------
		数据 - 可作用于战斗界面
*/
bool C_ScriptHelp_EffectScope::isEnableSceneBattle(){
	return this->scope_list.contains(S_Const_EffectScope::getInstance()->getSceneName_Battle());
}
/*-------------------------------------------------
		数据 - 可作用于菜单界面
*/
bool C_ScriptHelp_EffectScope::isEnableSceneMenu(){
	return this->scope_list.contains(S_Const_EffectScope::getInstance()->getSceneName_Menu());
}
/*-------------------------------------------------
		数据 - 可作用于界面
*/
bool C_ScriptHelp_EffectScope::isEnableScene(QString scene_name){
	return this->scope_list.contains(scene_name);
}
/*-------------------------------------------------
		数据 - 获取作用域
*/
QStringList C_ScriptHelp_EffectScope::getEnabledScene(){
	return this->scope_list;
}
/*-------------------------------------------------
		数据 - 除此三种类型以外的界面
*/
QStringList C_ScriptHelp_EffectScope::getOtherScene(){
	QStringList result = QStringList();
	for (int i = 0; i < this->scope_list.count(); i++){
		QString data = this->scope_list.at(i);
		if (data == S_Const_EffectScope::getInstance()->getSceneName_Map()){ continue; }
		if (data == S_Const_EffectScope::getInstance()->getSceneName_Battle()){ continue; }
		if (data == S_Const_EffectScope::getInstance()->getSceneName_Menu()){ continue; }
		result.append(data);
	}
	return result;
}

