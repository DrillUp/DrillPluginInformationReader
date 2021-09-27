#pragma once
#include <QList>
#include <QJsonObject>


/*
-----==========================================================-----
		类：		插件框架参数 实体类.h
		所属模块：	插件模块
		功能：		单独的参数识别。
-----==========================================================-----
*/
class C_ScriptDictionary_Param {

	public:
		C_ScriptDictionary_Param();
		~C_ScriptDictionary_Param();
		
	//-----------------------------------
	//----数据
	public:
		QString name;			//参数名（@param）
		QString parent;			//参数父类名（@parent）
		QString type;			//参数类型（@type）
		QString desc;			//参数描述（@desc）
		QString default_;		//参数默认值（@default）

		int min;				//参数类型-数字最小值（@min）
		int max;				//参数类型-数字最大值（@max）
		QString on;				//参数类型-布尔文本（@on）
		QString off;			//参数类型-布尔文本（@off）
		QStringList option;		//参数类型-下拉框的内容（@option）
		int require;			//参数类型-文件（@require）
		QString dir;			//参数类型-文件（@dir）
		
	//-----------------------------------
	//----类属性
	public:
										//运算符重载
		const bool operator== (const C_ScriptDictionary_Param& a)const;
										//实体类 -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> 实体类
		void setJsonObject(QJsonObject obj);
};