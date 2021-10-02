#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-章节 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的章节。
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
		QStringList comment_list;	//内容列表

};
/*
-----==========================================================-----
		类：		帮助数据-分段说明 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Subsection{

	public:
		C_ScriptHelp_Subsection();
		~C_ScriptHelp_Subsection();

	//-----------------------------------
	//----数据
	public:
		QStringList main_list;							//主内容说明
	protected:
		QList<C_ScriptHelp_SubsectionPage> page_list;	//章节列表
	public:
								//数据 - 添加章节
		void addPage(QString page_context); 
};
