#pragma once
#include <QList>

#include "c_ScriptHelp_Docs.h"

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
		QString group_name;						//组名称（可为空）
		bool is_important;						//是否为激活条件
		QStringList note_context;				//说明列表

		QString command_context;				//指令全文
												//		【注意，不含 事件备注、脚本 】
		QStringList command_PluginCommand;		//指令 - 插件指令
		QStringList command_PluginCommand_old;	//指令 - 插件指令(旧)
		QStringList command_EventComment;		//指令 - 事件注释
		QStringList command_EventComment_old;	//指令 - 事件注释(旧)
		QStringList command_MapNote;			//指令 - 地图备注
		QStringList command_ActorNote;			//指令 - 角色注释
		QStringList command_EnemyNote;			//指令 - 敌人注释
		QStringList command_StateNote;			//指令 - 状态注释
		QStringList command_ItemNote;			//指令 - 物品/武器/护甲注释
		QStringList command_SkillNote;			//指令 - 技能注释
		QStringList command_MoveRoute;			//指令 - 移动路线指令
		QStringList command_Other;				//指令 - 其它
	public:
									//数据 - 添加指令
		void addOneRowCommand(QString command_row);
									//数据 - 获取全部指令（不含其它指令）
		QStringList getAllAvailableCommand();
									//数据 - 获取全部指令
		QStringList getAllCommand();
									//数据 - 获取名称
		QString getGroupFullName();
									//数据 - 网格竖切 - 获取全部标签
									//		【说明】：将 指令全文 "插件指令：>xxxx" 竖切，切成两列文本。保留 \n 换行符。
		QStringList getGrid_TagList();
									//数据 - 网格竖切 - 获取全部指令
		QStringList getGrid_CommandList();

	//-----------------------------------
	//----搜索
	public:
									//搜索 - 包含指定指令关键字
		bool hasCommandKeyWord(QString keyWord);
									//搜索 - 指令的正则规则
		QRegExp commandRe();
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
								//数据 - 指令集列表
		QList<C_ScriptHelp_CommandGroup> getGroupList();
								//数据 - 获取全部指令 - 插件指令
		QStringList getAllCommand_PluginCommand();
								//数据 - 获取全部指令 - 插件指令(旧)
		QStringList getAllCommand_PluginCommandOld();
								//数据 - 获取全部指令 - 事件注释
		QStringList getAllCommand_EventComment();
								//数据 - 获取全部指令 - 事件注释(旧)
		QStringList getAllCommand_EventCommentOld();
								//数据 - 获取全部指令 - 地图备注
		QStringList getAllCommand_MapNote();
								//数据 - 获取全部指令 - 角色注释
		QStringList getAllCommand_ActorNote();
								//数据 - 获取全部指令 - 敌人注释
		QStringList getAllCommand_EnemyNote();
								//数据 - 获取全部指令 - 状态注释
		QStringList getAllCommand_StateNote();
								//数据 - 获取全部指令 - 物品/武器/护甲注释
		QStringList getAllCommand_ItemNote();
								//数据 - 获取全部指令 - 技能注释
		QStringList getAllCommand_SkillNote();
								//数据 - 获取全部指令 - 移动路线指令
		QStringList getAllCommand_MoveRoute();
								//数据 - 获取全部指令 - 其它
		QStringList getAllCommand_Other();
		
	//-----------------------------------
	//----搜索
	public:
								//搜索 - 包含指定指令关键字
		bool hasCommandKeyWord_All(QString keyWord);
								//搜索 - 包含指定指令关键字 - 插件指令
		bool hasCommandKeyWord_PluginCommand(QString keyWord);
								//搜索 - 包含指定指令关键字 - 插件指令(旧)
		bool hasCommandKeyWord_PluginCommandOld(QString keyWord);
								//搜索 - 包含指定指令关键字 - 事件注释
		bool hasCommandKeyWord_EventComment(QString keyWord);
								//搜索 - 包含指定指令关键字 - 事件注释(旧)
		bool hasCommandKeyWord_EventCommentOld(QString keyWord);
								//搜索 - 包含指定指令关键字 - 地图备注
		bool hasCommandKeyWord_MapNote(QString keyWord);
								//搜索 - 包含指定指令关键字 - 角色注释
		bool hasCommandKeyWord_ActorNote(QString keyWord);
								//搜索 - 包含指定指令关键字 - 敌人注释
		bool hasCommandKeyWord_EnemyNote(QString keyWord);
								//搜索 - 包含指定指令关键字 - 状态注释
		bool hasCommandKeyWord_StateNote(QString keyWord);
								//搜索 - 包含指定指令关键字 - 物品/武器/护甲注释
		bool hasCommandKeyWord_ItemNote(QString keyWord);
								//搜索 - 包含指定指令关键字 - 技能注释
		bool hasCommandKeyWord_SkillNote(QString keyWord);
								//搜索 - 包含指定指令关键字 - 移动路线指令
		bool hasCommandKeyWord_MoveRoute(QString keyWord);
								//搜索 - 包含指定指令关键字 - 其它
		bool hasCommandKeyWord_Other(QString keyWord);
	protected:
								//私有 - 判断关键字
		bool searchCommandKeyWord(QStringList* command_list, QString keyWord);

	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取新的指令集字符串
		void readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs);
};
