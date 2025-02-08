﻿#pragma once
#include <QList>
#include <QJsonObject>

#include "C_ScriptHelp_EffectScope.h"
#include "C_ScriptHelp_PluginRelation.h"
#include "C_ScriptHelp_Src.h"
#include "C_ScriptHelp_Docs.h"
#include "C_ScriptHelp_Subsection.h"
#include "C_ScriptHelp_Command.h"
#include "C_ScriptHelp_Knowledge.h"
#include "C_ScriptHelp_Performance.h"

/*
-----==========================================================-----
		类：		帮助信息 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		插件注解中 @help 的全部数据+解析数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelpDetail{

	public:
		C_ScriptHelpDetail();
		~C_ScriptHelpDetail();
		
	//-----------------------------------
	//----基本属性
	protected:
		QString name;				//插件名（文件名）
		QString help;				//帮助信息（@help）
	public:
									//基本 - 设置插件名
		void setName(QString name);
									//基本 - 设置帮助信息
		void setHelpContext(QString help);
									//基本 - 获取插件名
		QString getName();
									//基本 - 获取帮助信息
		QString getHelpContext();
	private:
									//私有 - 帮助信息初始化
		void initHelpContext();

	//-----------------------------------
	//----解析数据
	protected:
		C_ScriptHelp_EffectScope* m_effectScope;		//作用域
		C_ScriptHelp_PluginRelation* m_pluginRelation;	//插件扩展
		C_ScriptHelp_Src* m_src;						//资源路径
		C_ScriptHelp_Docs* m_docs;						//插件文档
		C_ScriptHelp_Subsection* m_subsection;			//分段说明
		C_ScriptHelp_Command* m_command;				//指令
		C_ScriptHelp_Knowledge* m_knowledge;			//知识点
		C_ScriptHelp_Performance* m_performance;		//插件性能
	public:
									//数据 - 获取作用域
		C_ScriptHelp_EffectScope* getEffectScope();
									//数据 - 获取插件扩展
		C_ScriptHelp_PluginRelation* getPluginRelation();
									//数据 - 获取资源路径
		C_ScriptHelp_Src* getSrc();
									//数据 - 获取插件文档
		C_ScriptHelp_Docs* getDocs();
									//数据 - 获取分段说明
		C_ScriptHelp_Subsection* getSubsection();
									//数据 - 获取指令
		C_ScriptHelp_Command* getCommand();
									//数据 - 获取知识点
		C_ScriptHelp_Knowledge* getKnowledge();
									//数据 - 获取插件性能
		C_ScriptHelp_Performance* getPerformance();

	//-----------------------------------
	//----操作
	public:
									//操作 - 判断包含指定指令关键字
		bool hasCommandKeyWord(QString keyWord);


	//-----------------------------------
	//----类属性
	public:
										//空判断
		bool isNull();
										//运算符重载
		const bool operator== (const C_ScriptHelpDetail& a)const;
										//实体类 -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> 实体类
		void setJsonObject(QJsonObject obj);
};
