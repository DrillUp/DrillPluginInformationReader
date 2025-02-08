#include "stdafx.h"
#include "C_ScriptDictionary_Param.h"


/*
-----==========================================================-----
		类：		插件框架参数 实体类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		单独的参数识别。
-----==========================================================-----
*/
C_ScriptDictionary_Param::C_ScriptDictionary_Param(){

	// > 数据
	this->name = "";				//参数名（@param）
	this->parent = "";				//参数父类名（@parent）
	this->type = "";				//参数类型（@type）
	this->desc = "";				//参数描述（@desc）
	this->default_ = "";			//参数默认值（@default）

	this->min = -1;					//参数类型-数字最小值（@min）
	this->max = -1;					//参数类型-数字最大值（@max）
	this->on = "";					//参数类型-布尔文本（@on）
	this->off = "";					//参数类型-布尔文本（@off）
	this->option = QStringList(); 	//参数类型-下拉框的内容（@option）
	this->require = -1;				//参数类型-文件（@require）
	this->dir = "";					//参数类型-文件（@dir）
}
C_ScriptDictionary_Param::~C_ScriptDictionary_Param(){
}


/*-------------------------------------------------
		运算符重载
*/
const bool C_ScriptDictionary_Param::operator== (const C_ScriptDictionary_Param& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		实体类 -> QJsonObject
*/
QJsonObject C_ScriptDictionary_Param::getJsonObject(){
	QJsonObject obj = QJsonObject();

	// > 数据
	obj.insert("name", this->name);
	obj.insert("parent", this->parent);
	obj.insert("type", this->type);
	obj.insert("desc", this->desc);
	obj.insert("default_", this->default_);

	obj.insert("min", this->min);
	obj.insert("max", this->max);
	obj.insert("on", this->on);
	obj.insert("off", this->off);
	QJsonArray arr_option = QJsonArray();
	for (int i = 0; i < this->option.count(); i++){ 
		arr_option.append(this->option.at(i)); 
	}
	obj.insert("option", arr_option);
	obj.insert("require", this->require);
	obj.insert("dir", this->dir);

	return obj;
}
/*-------------------------------------------------
		QJsonObject -> 实体类
*/
void C_ScriptDictionary_Param::setJsonObject(QJsonObject obj){

	// > 数据
	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("parent").isUndefined() == false){ this->parent = obj.value("parent").toString(); }
	if (obj.value("type").isUndefined() == false){ this->type = obj.value("type").toString(); }
	if (obj.value("desc").isUndefined() == false){ this->desc = obj.value("desc").toString(); }
	if (obj.value("default_").isUndefined() == false){ this->default_ = obj.value("default_").toString(); }

	if (obj.value("min").isUndefined() == false){ this->min = obj.value("min").toInt(); }
	if (obj.value("max").isUndefined() == false){ this->max = obj.value("max").toInt(); }
	if (obj.value("on").isUndefined() == false){ this->on = obj.value("on").toString(); }
	if (obj.value("off").isUndefined() == false){ this->off = obj.value("off").toString(); }
	if (obj.value("option").isUndefined() == false){
		QJsonArray arr_option = QJsonArray();
		this->option = QStringList();
		for (int i = 0; i < arr_option.count(); i++){ this->option.append(arr_option.at(i).toString()); }
	}
	if (obj.value("require").isUndefined() == false){ this->require = obj.value("require").toInt(); }
	if (obj.value("dir").isUndefined() == false){ this->dir = obj.value("dir").toString(); }
}
