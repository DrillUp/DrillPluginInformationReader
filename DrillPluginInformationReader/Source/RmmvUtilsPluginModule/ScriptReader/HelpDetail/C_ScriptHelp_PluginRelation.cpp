#include "stdafx.h"
#include "C_ScriptHelp_PluginRelation.h"

#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		类：		帮助数据-扩展组 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					数据结构为：插件扩展 > 扩展组。
-----==========================================================-----
*/
C_ScriptHelp_PluginRelationGroup::C_ScriptHelp_PluginRelationGroup(){
	this->title = "";
	this->plugin_context = QStringList();
}
C_ScriptHelp_PluginRelationGroup::~C_ScriptHelp_PluginRelationGroup(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_PluginRelationGroup::isNull(){
	return this->title == "" || this->plugin_context.count() == 0;
}
/*-------------------------------------------------
		数据 - 基于
*/
bool C_ScriptHelp_PluginRelationGroup::isBaseOn(){
	return this->title == "基于";
}
/*-------------------------------------------------
		数据 - 可被扩展/可扩展
*/
bool C_ScriptHelp_PluginRelationGroup::isBeingExtend(){
	return this->title == "可被扩展" || this->title == "可扩展";
}
/*-------------------------------------------------
		数据 - 可作用于/作用于
*/
bool C_ScriptHelp_PluginRelationGroup::isEffectTo(){
	return this->title == "可作用于" || this->title == "作用于";
}
/*-------------------------------------------------
		数据 - 类型其它
*/
bool C_ScriptHelp_PluginRelationGroup::isOther(){
	if (this->isBaseOn()){ return false; }
	if (this->isBeingExtend()){ return false; }
	if (this->isEffectTo()){ return false; }
	return true;
}

/*
-----==========================================================-----
		类：		帮助数据-插件扩展 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					数据结构为：插件扩展 > 扩展组。
-----==========================================================-----
*/
C_ScriptHelp_PluginRelation::C_ScriptHelp_PluginRelation(){
	this->context = QStringList();
	this->group_list = QList<C_ScriptHelp_PluginRelationGroup>();
}
C_ScriptHelp_PluginRelation::~C_ScriptHelp_PluginRelation(){
}

/*-------------------------------------------------
		数据 - 获取主内容
*/
QStringList C_ScriptHelp_PluginRelation::getMainContext(){
	return this->context;
}
/*-------------------------------------------------
		数据 - 获取 基于 的插件信息
*/
QStringList C_ScriptHelp_PluginRelation::getContextByBaseOn(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isBaseOn()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取 可被扩展 的插件信息
*/
QStringList C_ScriptHelp_PluginRelation::getContextByBeingExtend(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isBeingExtend()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取 可作用于 的插件信息
*/
QStringList C_ScriptHelp_PluginRelation::getContextByEffectTo(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isEffectTo()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取 其它 插件信息
*/
QStringList C_ScriptHelp_PluginRelation::getContextByOther(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isOther()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_PluginRelation::isNull(){
	return this->context.count() == 0 && this->group_list.count() == 0;
}


/*-------------------------------------------------
		读取器 - 读取 插件扩展 字符串
*/
void C_ScriptHelp_PluginRelation::readPluginRelation(QString relation_context){
	QStringList context_list = relation_context.split(QRegExp("[\n\r]+"));
	TTool::_QStringList_clearEmptyRows_(&context_list);

	// > 主内容
	int i_context = 0;
	for (int i = 0; i < context_list.count(); i++){
		QString data = context_list.at(i);
		if (data.at(0) != ' ' && data.count() <= 5){	//（简单粗暴：少于5个字的算标题）
			i_context = i;		//（遇到标题时终止）
			break;
		}else{
			this->context.append(data);
		}
	}

	// > 扩展组
	C_ScriptHelp_PluginRelationGroup cur_group = C_ScriptHelp_PluginRelationGroup();
	for (int i = i_context; i < context_list.count(); i++){
		QString data = context_list.at(i);

		// > 扩展组标题
		if ( data.at(0) != ' ' && data.count() <= 5 ){

			if (cur_group.isNull() == false){
				this->group_list.append(cur_group);
			}

			cur_group = C_ScriptHelp_PluginRelationGroup();
			cur_group.title = data.replace(QRegExp("[:：]"), "");
		
		// > 扩展组内容
		}else{
			data = data.trimmed().replace(QRegExp("^\\-[ ]+"), "◆");
			cur_group.plugin_context.append(data);
		}
	}
	if (cur_group.isNull() == false){
		this->group_list.append(cur_group);
	}
}
