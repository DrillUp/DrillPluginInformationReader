#pragma once
#include <QList>
#include <QJsonObject>


/*
-----==========================================================-----
		类：		插件注解 实体类.h
		所属模块：	插件模块
		功能：		插件注解的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelpDetail{

	public:
		C_ScriptHelpDetail();
		~C_ScriptHelpDetail();
		
	public:
		QString name;				//插件名（文件名）
		QString help;				//帮助信息（@help）

	//-----------------------------------
	//----类属性
	public:
										//运算符重载
		const bool operator== (const C_ScriptHelpDetail& a)const;
										//实体类 -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> 实体类
		void setJsonObject(QJsonObject obj);
};
