#include "stdafx.h"
#include "s_Const_Performance.h"

#include "Source/utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件性能 常量值.cpp
		作者：		drill_up
		所属模块：	工具模块
		功能：		所有常量值在这里直接获取。
-----==========================================================-----
*/
S_Const_Performance::S_Const_Performance() : S_Const_PluginValue(){

	// > 性能关键字
	this->m_performanceKeyMatrix = QList<QList<QString>>();
	this->m_performanceKeyMatrix << (QStringList() << "地图界面" << "20个事件" << "50个事件" << "100个事件" << "200个事件");
	this->m_performanceKeyMatrix << (QStringList() << "战斗界面" << "没有敌人" << "1个敌人" << "4个敌人" << "8个敌人");
	this->m_performanceKeyMatrix << (QStringList() << "战斗界面" << "没有角色" << "1个角色" << "4个角色" << "8个角色");		//（只 根据界面名称获取 的函数获取不到这部分数据）
	this->m_performanceKeyMatrix << (QStringList() << "菜单界面" << "程度1" << "程度2" << "程度3" << "程度4");
	this->m_performanceKeyMatrix << (QStringList() << "STG界面" << "20个敌机" << "50个敌机" << "100个敌机" << "200个敌机");
}
S_Const_Performance::~S_Const_Performance(){
}
/*-------------------------------------------------
		单例
*/
S_Const_Performance* S_Const_Performance::cur_instance = NULL;
S_Const_Performance* S_Const_Performance::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new S_Const_Performance();
	}
	return cur_instance;
}

/*-------------------------------------------------
		获取 - 界面名称（根据性能关键字）
*/
QString S_Const_Performance::getSceneName_ByPerformanceWord(QString performanceWord){
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
		获取 - 性能关键字（全部）
*/
QStringList S_Const_Performance::getPerformanceWord_All(){
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
QStringList S_Const_Performance::getPerformanceWord_ByName(QString scene_name){
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
int S_Const_Performance::getLevel_ByPerformanceWord(QString performanceWord){
	if (performanceWord == ""){ return -1; }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		int index = text_list.indexOf(performanceWord);	//（返回 1至4 ，0肯定搜索不到 ）
		if (index != -1){
			return index;
		}
	}
	return -1;
}