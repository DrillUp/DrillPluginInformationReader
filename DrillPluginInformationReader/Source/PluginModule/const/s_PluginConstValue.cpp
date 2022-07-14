#include "stdafx.h"
#include "s_PluginConstValue.h"

#include "Source/utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件 常量值.cpp
		版本：		v1.00
		作者：		drill_up
		所属模块：	工具模块
		功能：		所有常量值在这里直接获取。
-----==========================================================-----
*/
S_PluginConstValue::S_PluginConstValue(){

	// > 界面名称
	this->m_sceneNameList = QStringList() << "地图界面" << "战斗界面" << "菜单界面" << "STG界面";

	// > 界面关键字
	this->m_sceneKeyMatrix = QList<QList<QString>>();
	this->m_sceneKeyMatrix << (QStringList() << "地图界面" << "物体" << "事件" << "玩家" );
	this->m_sceneKeyMatrix << (QStringList() << "战斗界面" << "单位" << "敌人" << "角色");
	this->m_sceneKeyMatrix << (QStringList() << "菜单界面" << "控件" );
	this->m_sceneKeyMatrix << (QStringList() << "STG界面" << "机组" << "敌机" << "自机");

	// > 性能关键字
	this->m_performanceKeyMatrix = QList<QList<QString>>();
	this->m_performanceKeyMatrix << (QStringList() << "地图界面" << "20个事件" << "50个事件" << "100个事件" << "200个事件");
	this->m_performanceKeyMatrix << (QStringList() << "战斗界面" << "没有敌人" << "1个敌人" << "4个敌人" << "8个敌人");
	this->m_performanceKeyMatrix << (QStringList() << "战斗界面" << "没有角色" << "1个角色" << "4个角色" << "8个角色");		//（只 根据界面名称获取 的函数获取不到这部分数据）
	this->m_performanceKeyMatrix << (QStringList() << "菜单界面" << "程度1" << "程度2" << "程度3" << "程度4");
	this->m_performanceKeyMatrix << (QStringList() << "STG界面" << "20个敌机" << "50个敌机" << "100个敌机" << "200个敌机");
}
S_PluginConstValue::~S_PluginConstValue(){
}
/*-------------------------------------------------
		单例
*/
S_PluginConstValue* S_PluginConstValue::cur_instance = NULL;
S_PluginConstValue* S_PluginConstValue::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new S_PluginConstValue();
	}
	return cur_instance;
}

/*-------------------------------------------------
		获取 - 地图界面
*/
QString S_PluginConstValue::getSceneName_Map(){
	return "地图界面";
}
/*-------------------------------------------------
		获取 - 战斗界面
*/
QString S_PluginConstValue::getSceneName_Battle(){
	return "战斗界面";
}
/*-------------------------------------------------
		获取 - 菜单界面
*/
QString S_PluginConstValue::getSceneName_Menu(){
	return "菜单界面";
}
/*-------------------------------------------------
		获取 - 其它界面
*/
QStringList S_PluginConstValue::getSceneName_Other(){
	return QStringList() << "STG界面";
}

/*-------------------------------------------------
		获取 - 界面名称（全部）
*/
QStringList S_PluginConstValue::getSceneName_All(){
	return this->m_sceneNameList;
}
/*-------------------------------------------------
		获取 - 界面名称（根据界面关键字）
*/
QString S_PluginConstValue::getSceneName_BySceneKey(QString sceneKey){
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
		获取 - 界面名称（根据性能关键字）
*/
QString S_PluginConstValue::getSceneName_ByPerformanceWord(QString performanceWord){
	if (performanceWord == ""){ return ""; }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		if (text_list.contains( performanceWord ) ){
			return text_list.first();
		}
	}
	return "";
}


/*-------------------------------------------------
		获取 - 界面关键字（全部）
*/
QStringList S_PluginConstValue::getSceneKey_All(){
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
QStringList S_PluginConstValue::getSceneKey_ByName(QString scene_name){
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

/*-------------------------------------------------
		获取 - 性能关键字（全部）
*/
QStringList S_PluginConstValue::getPerformanceWord_All(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList data = this->m_performanceKeyMatrix.at(i);
		data.removeFirst();
		result_list.append(data);
	}
	return result_list;
}
/*-------------------------------------------------
		获取 - 性能关键字（根据界面名称）
*/
QStringList S_PluginConstValue::getPerformanceWord_ByName(QString scene_name){
	if (scene_name == ""){ return QStringList(); }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		if (text_list.first() == scene_name){
			text_list.removeFirst();
			return text_list;
		}
	}
	return QStringList();
}
/*-------------------------------------------------
		获取 - 程度（根据性能关键字）
*/
int S_PluginConstValue::getLevel_ByPerformanceWord(QString performanceWord){
	if (performanceWord == ""){ return -1; }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		int index = text_list.indexOf(performanceWord);
		if (index != -1){
			return index;
		}
	}
	return -1;
}