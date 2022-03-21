#pragma once
#include <QList>
#include <QMap>


/*
-----==========================================================-----
		类：		插件注解 实体类.h
		所属模块：	插件模块
		功能：		插件注解的数据。
					【该数据类的初始化通过读取器赋值来完成。】
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelpDetail;
class C_ScriptDictionary;
class C_ScriptAnnotation{

	public:
		C_ScriptAnnotation();
		~C_ScriptAnnotation();
		
	//-----------------------------------
	//----数据
	protected:
		QString name;								//插件名（文件名）
		QString plugindesc;							//插件描述（@plugindesc）
		QString author;								//作者（@author）
		C_ScriptHelpDetail* helpDetail;				//帮助信息（@help + 解析内容）
		C_ScriptDictionary* dictionary;				//参数字典（@param全部内容）

	public:
										//数据 - 获取插件名（文件名）
		QString getName();
										//数据 - 获取插件描述（@plugindesc）
		QString getPlugindesc();
										//数据 - 获取作者（@author）
		QString getAuthor();
										//数据 - 获取帮助信息全文（@help）
		QString getHelp();
										//数据 - 是否为完整解析的内容
		bool isCompleted();
										//数据 - 帮助信息数据
		C_ScriptHelpDetail* getScriptHelpDetail();
										//数据 - 参数字典数据
		C_ScriptDictionary* getScriptDictionary();
		
										//数据 - 设置插件名（文件名）
		void setName(QString name);
										//数据 - 设置插件描述（@plugindesc）
		void setPlugindesc(QString plugindesc);
										//数据 - 设置作者（@author）
		void setAuthor(QString author);
										//数据 - 设置帮助信息数据
		void setScriptHelpDetail(C_ScriptHelpDetail* helpDetail);
										//数据 - 设置参数字典数据
		void setScriptDictionary(C_ScriptDictionary* dictionary);

	//-----------------------------------
	//----临时截断数据
	protected:
		bool temp_inited;				//标记
		QString temp_version;			//版本(调取时才初始化）
		QString temp_type;				//类型（调取时才初始化）
		QString temp_name;				//中文名（调取时才初始化）
	public:
										//数据 - 初始化截取段
		void initPlugindesc_data();
										//数据 - 获取版本（插件描述 截取段）
		QString getPlugindesc_version();
		double getPlugindesc_versionNum();
										//数据 - 获取类型（插件描述 截取段）
		QString getPlugindesc_type();
										//数据 - 获取中文名（插件描述 截取段）
		QString getPlugindesc_name();

	//-----------------------------------
	//----类属性
	public:
										//空判断
		bool isNull();	
										//运算符重载
		const bool operator== (const C_ScriptAnnotation& a)const;
										//实体类 -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> 实体类
		void setJsonObject(QJsonObject obj);
};
