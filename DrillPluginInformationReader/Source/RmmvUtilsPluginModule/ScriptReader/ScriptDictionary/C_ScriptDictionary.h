#pragma once
#include <QList>
#include <QJsonObject>

#include "C_ScriptDictionary_Param.h"

/*
-----==========================================================-----
		类：		插件注解 实体类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		插件注解的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptDictionary{

	public:
		C_ScriptDictionary();
		~C_ScriptDictionary();
		
	//-----------------------------------
	//----数据
	public:
		QString name;										//插件名（文件名）
		QList<C_ScriptDictionary_Param> param_list;			//参数列表（@param）

	//-----------------------------------
	//----类属性
	public:
										//运算符重载
		const bool operator== (const C_ScriptDictionary& a)const;
										//实体类 -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> 实体类
		void setJsonObject(QJsonObject obj);
};