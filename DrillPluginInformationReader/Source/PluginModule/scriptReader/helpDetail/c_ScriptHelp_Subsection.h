#pragma once
#include <QList>

#include "c_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		类：		帮助数据-介绍 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的介绍内容。
					【开头"========"后面的几行内容】
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_SubsectionHeader{

	public:
		C_ScriptHelp_SubsectionHeader();
		~C_ScriptHelp_SubsectionHeader();

	//-----------------------------------
	//----数据
	public:
		QString introduction;		//简介
		QString package;			//打包支持提示
		QStringList condition;		//必要条件列表
	public:
									//数据 - 空判断
		bool isNull();
};

/*
-----==========================================================-----
		类：		帮助数据-章节 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的章节。
					【"----设定注意事项"后面的小分段内容】
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_SubsectionPage{

	public:
		C_ScriptHelp_SubsectionPage();
		~C_ScriptHelp_SubsectionPage();

	//-----------------------------------
	//----数据
	public:
		QString title;				//章节标题
		QStringList context;		//内容列表
	public:
									//数据 - 空判断
		bool isNull();
									//数据 - 判断是否为"设计"章节
		bool isDesignTip();
};

/*
-----==========================================================-----
		类：		帮助数据-分段说明 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					【综合 上面的数据 和 "作用域"后面的内容点】
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Subsection{

	public:
		C_ScriptHelp_Subsection();
		~C_ScriptHelp_Subsection();

	//-----------------------------------
	//----数据
	protected:
		C_ScriptHelp_SubsectionHeader header;			//介绍数据
		QStringList main_list;							//主内容说明
		QList<C_ScriptHelp_SubsectionPage> page_list;	//章节列表
	public:
								//数据 - 获取主内容
		QStringList getMainContext();
								//数据 - 获取介绍数据
		C_ScriptHelp_SubsectionHeader getHeader();
								//数据 - 空判断（介绍数据）
		bool isHeaderNull();
								//数据 - 空判断（介绍的条件、章节列表、主内容说明）
		bool isSubsectionNull();
								//数据 - 获取章节标题
		QStringList getAllTitle();
								//数据 - 获取章节（根据标题）
		C_ScriptHelp_SubsectionPage getPageByTitle(QString title);
								//数据 - 获取章节内容（根据标题）
		QStringList getPageContextByTitle(QString title);

								//数据 - 是否含有"设计"章节
		bool hasDesignTip();
								//数据 - 获取"设计"章节
		C_ScriptHelp_SubsectionPage getPage_DesignTip();

	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 介绍 数据
		void readHeader(QString header_context);
								//读取器 - 读取 分段说明 数据
		void readSubsection(QString subsection_context, C_ScriptHelp_Docs* c_docs);
	protected:
								//读取器 - 添加一个章节
		void readNextPage(QString page_context); 
};
