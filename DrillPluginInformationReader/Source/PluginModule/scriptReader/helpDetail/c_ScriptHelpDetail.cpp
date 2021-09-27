#include "stdafx.h"
#include "c_ScriptHelpDetail.h"


/*
-----==========================================================-----
		类：		插件注解 实体类.cpp
		所属模块：	插件模块
		功能：		插件注解的数据。

		必要事项：	> 框架数据为从js脚本中读取到的数据。
					  由于js脚本随时可变，所以不建议存储。
-----==========================================================-----
*/
C_ScriptHelpDetail::C_ScriptHelpDetail(){
	this->name = "";			 	//插件名（文件名）
	this->help = "";				//帮助信息（@help）
}
C_ScriptHelpDetail::~C_ScriptHelpDetail(){
}

/*-------------------------------------------------
		运算符重载
*/
const bool C_ScriptHelpDetail::operator== (const C_ScriptHelpDetail& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		实体类 -> QJsonObject
*/
QJsonObject C_ScriptHelpDetail::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("help", this->help);
	return obj;
}
/*-------------------------------------------------
		QJsonObject -> 实体类
*/
void C_ScriptHelpDetail::setJsonObject(QJsonObject obj){

	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("help").isUndefined() == false){ this->help = obj.value("help").toString(); }

}

