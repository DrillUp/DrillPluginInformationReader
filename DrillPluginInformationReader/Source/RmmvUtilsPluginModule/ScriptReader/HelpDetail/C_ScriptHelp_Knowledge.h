#pragma once
#include <QList>

#include "C_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		类：		帮助数据-知识点 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					数据结构为：知识点列表 > 知识点。
-----==========================================================-----
*/
class C_ScriptHelp_KnowledgeGroup{

	public:
		C_ScriptHelp_KnowledgeGroup();
		~C_ScriptHelp_KnowledgeGroup();

	//-----------------------------------
	//----数据
	public:
		QString group_name;					//组名称（可为空）
		QStringList context_data;			//内容列表
		QStringList context_note;			//说明列表

};
/*
-----==========================================================-----
		类：		帮助数据-知识点列表 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					数据结构为：知识点列表 > 知识点。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Knowledge{

	public:
		C_ScriptHelp_Knowledge();
		~C_ScriptHelp_Knowledge();

	//-----------------------------------
	//----数据
	protected:
		QList<C_ScriptHelp_KnowledgeGroup> group_list;	//知识点列表
	public:
								//数据 - 空判断
		bool isNull();
								//数据 - 知识点列表
		QList<C_ScriptHelp_KnowledgeGroup> getGroupList();

	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 知识点 数据
		void readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs);

};
