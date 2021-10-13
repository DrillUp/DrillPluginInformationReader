#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-指令集 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的章节。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_CommandGroup{

	public:
		C_ScriptHelp_CommandGroup();
		~C_ScriptHelp_CommandGroup();

	//-----------------------------------
	//----数据
	public:
		QString group_name;			//组名称（可为空）
		bool is_important;			//是否为激活条件
		QStringList context;		//内容列表

		QStringList command_PluginCommand;		//指令 - 插件指令
		QStringList command_PluginCommand_old;	//旧指令 - 插件指令
		QStringList command_EventComment;		//指令 - 事件注释
		QStringList command_EventComment_old;	//旧指令 - 事件注释
		QStringList command_EventNote;			//指令 - 事件备注
		QStringList command_MapNote;			//指令 - 地图备注
		QStringList command_ActorNote;			//指令 - 角色备注
		QStringList command_EnemyNote;			//指令 - 敌人备注
		
};
/*
-----==========================================================-----
		类：		帮助数据-指令 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Command{

	public:
		C_ScriptHelp_Command();
		~C_ScriptHelp_Command();

	//-----------------------------------
	//----数据
	protected:
		QList<C_ScriptHelp_CommandGroup> group_list;	//指令集列表
	public:
								//数据 - 空判断
		bool isNull();
	public:
								//数据 - 读取新的指令集字符串
		void readNextGroup(QString group_context); 
};
