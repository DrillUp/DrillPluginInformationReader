#include "stdafx.h"
#include "c_ScriptDictionary.h"


/*
-----==========================================================-----
		类：		插件注解 实体类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		插件注解的数据。

		必要事项：	> 框架数据为从js脚本中读取到的数据。
					  由于js脚本随时可变，所以不建议存储。
-----==========================================================-----
*/
C_ScriptDictionary::C_ScriptDictionary(){
	this->name = "";									  	//插件名
	this->param_list = QList<C_ScriptDictionary_Param>(); 	//参数列表
}
C_ScriptDictionary::~C_ScriptDictionary(){
}

/*-------------------------------------------------
		运算符重载
*/
const bool C_ScriptDictionary::operator== (const C_ScriptDictionary& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		实体类 -> QJsonObject
*/
QJsonObject C_ScriptDictionary::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	QJsonArray arr_param_list = QJsonArray();
	for (int i = 0; i < this->param_list.count(); i++){ 
		C_ScriptDictionary_Param c_p = this->param_list.at(i);
		arr_param_list.append(c_p.getJsonObject());
	}
	obj.insert("param_list", arr_param_list);

	return obj;
}
/*-------------------------------------------------
		QJsonObject -> 实体类
*/
void C_ScriptDictionary::setJsonObject(QJsonObject obj){

	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("param_list").isUndefined() == false){
		QJsonArray arr_option = QJsonArray();
		this->param_list = QList<C_ScriptDictionary_Param>();
		for (int i = 0; i < arr_option.count(); i++){ 
			C_ScriptDictionary_Param c_p = C_ScriptDictionary_Param();
			c_p.setJsonObject(arr_option.at(i).toObject());
			this->param_list.append(c_p);
		}
	}
}

