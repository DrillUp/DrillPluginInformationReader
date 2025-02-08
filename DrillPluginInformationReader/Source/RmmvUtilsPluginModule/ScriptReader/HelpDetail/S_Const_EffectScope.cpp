#include "stdafx.h"
#include "S_Const_EffectScope.h"

/*
-----==========================================================-----
		类：		帮助数据-作用域 常量值.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		常量值在这单例中可以直接获取。
-----==========================================================-----
*/
S_Const_EffectScope::S_Const_EffectScope(){

	// > 界面名称
	this->m_sceneNameList = QStringList() << "地图界面" << "战斗界面" << "菜单界面" << "STG界面";

	// > 界面关键字
	this->m_sceneKeyMatrix = QList<QList<QString>>();
	this->m_sceneKeyMatrix << (QStringList() << "地图界面" << "物体" << "事件" << "玩家" );
	this->m_sceneKeyMatrix << (QStringList() << "战斗界面" << "单位" << "敌人" << "角色");
	this->m_sceneKeyMatrix << (QStringList() << "菜单界面" << "控件" );
	this->m_sceneKeyMatrix << (QStringList() << "STG界面" << "机组" << "敌机" << "自机");

}
S_Const_EffectScope::~S_Const_EffectScope(){
}
/*-------------------------------------------------
		单例
*/
S_Const_EffectScope* S_Const_EffectScope::cur_instance = NULL;
S_Const_EffectScope* S_Const_EffectScope::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new S_Const_EffectScope();
	}
	return cur_instance;
}

/*-------------------------------------------------
		获取 - 地图界面
*/
QString S_Const_EffectScope::getSceneName_Map(){
	return "地图界面";
}
/*-------------------------------------------------
		获取 - 战斗界面
*/
QString S_Const_EffectScope::getSceneName_Battle(){
	return "战斗界面";
}
/*-------------------------------------------------
		获取 - 菜单界面
*/
QString S_Const_EffectScope::getSceneName_Menu(){
	return "菜单界面";
}
/*-------------------------------------------------
		获取 - 其它界面
*/
QStringList S_Const_EffectScope::getSceneName_Other(){
	return QStringList() << "STG界面";
}

/*-------------------------------------------------
		获取 - 界面名称（全部）
*/
QStringList S_Const_EffectScope::getSceneName_All(){
	return this->m_sceneNameList;
}
/*-------------------------------------------------
		获取 - 界面名称（根据界面关键字）
*/
QString S_Const_EffectScope::getSceneName_BySceneKey(QString sceneKey){
	if (sceneKey == ""){ return ""; }
	for (int i = 0; i < this->m_sceneKeyMatrix.count(); i++){
		QStringList text_list = this->m_sceneKeyMatrix.at(i);
		if (text_list.contains(sceneKey)){
			return text_list.first();
		}
	}
	return "";
}


/*-------------------------------------------------
		获取 - 界面关键字（全部）
*/
QStringList S_Const_EffectScope::getSceneKey_All(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->m_sceneKeyMatrix.count(); i++){
		QStringList data = this->m_sceneKeyMatrix.at(i);
		data.removeFirst();
		result_list.append(data);
	}
	return result_list;
}
/*-------------------------------------------------
		获取 - 界面关键字（根据界面名称）
*/
QStringList S_Const_EffectScope::getSceneKey_ByName(QString scene_name){
	if (scene_name == ""){ return QStringList(); }
	for (int i = 0; i < this->m_sceneKeyMatrix.count(); i++){
		QStringList text_list = this->m_sceneKeyMatrix.at(i);
		if (text_list.first() == scene_name){
			text_list.removeFirst();
			return text_list;
		}
	}
	return QStringList();
}
