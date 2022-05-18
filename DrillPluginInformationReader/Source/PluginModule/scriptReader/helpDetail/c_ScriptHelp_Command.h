#pragma once
#include <QList>

#include "c_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		类：		帮助数据-指令集 原子类.h
		所属模块：	插件模块
		功能：		帮助信息中单条指令的数据类。
-----==========================================================-----
*/
class C_ScriptHelp_CommandCell{

	public:
		C_ScriptHelp_CommandCell();
		~C_ScriptHelp_CommandCell();
		
	public:
		QString type;		//指令类型
		QString command;	//指令内容
		QString note;		//指令后附加注释
};
/*
-----==========================================================-----
		类：		帮助数据-指令集 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的章节。
					
		说明：		注意，指令集分为两个部分：【数据（显示详细信息用）】，【搜索（显示搜索信息用）】
					两种数据可以分别获取，互不相关。
					- 数据：单独分为 指令全文 和 旧指令全文，文本包含空行，显示时需要 竖切 。
					- 搜索：所有指令按照 类型 分在各个字符串数组中。	
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

		QStringList context_note;				//说明列表
		QString context_command;				//指令全文
		QString context_command_old;			//旧指令全文
	public:
									//数据 - 获取名称
		QString getGroupFullName();
									//数据 - 从对象列表中，获取指令字符串列表
		QStringList getCommandListByObjList(QList<C_ScriptHelp_CommandCell> cell_list);

									//数据 - 网格竖切 - 获取全部标签
									//		【说明】：将 指令全文 "插件指令：>xxxx" 竖切，切成两列文本。保留 \n 换行符。
		QStringList getGrid_TagList();
									//数据 - 网格竖切 - 获取全部指令
		QStringList getGrid_CommandList();
									//数据 - 网格竖切 - 获取全部附加注释
		QStringList getGrid_NoteList();
									//数据 - 网格竖切 - 获取全部标签（旧全文用）
		QStringList getGrid_OldTagList();
									//数据 - 网格竖切 - 获取全部指令（旧全文用）
		QStringList getGrid_OldCommandList();

	//-----------------------------------
	//----搜索	【注意，不含 事件备注、脚本 】
	public:
		QList<C_ScriptHelp_CommandCell> command_Available;			//指令 - 有效指令
		QList<C_ScriptHelp_CommandCell> command_Other;				//指令 - 其它

		QList<C_ScriptHelp_CommandCell> command_PluginCommand;		//指令 - 插件指令
		QList<C_ScriptHelp_CommandCell> command_EventComment;		//指令 - 事件注释
		QList<C_ScriptHelp_CommandCell> command_MapNote;			//指令 - 地图备注
		QList<C_ScriptHelp_CommandCell> command_ActorNote;			//指令 - 角色注释
		QList<C_ScriptHelp_CommandCell> command_EnemyNote;			//指令 - 敌人注释
		QList<C_ScriptHelp_CommandCell> command_StateNote;			//指令 - 状态注释
		QList<C_ScriptHelp_CommandCell> command_ItemNote;			//指令 - 物品/武器/护甲注释
		QList<C_ScriptHelp_CommandCell> command_SkillNote;			//指令 - 技能注释
		QList<C_ScriptHelp_CommandCell> command_MoveRoute;			//指令 - 移动路线指令
		QList<C_ScriptHelp_CommandCell> command_WindowChar;			//指令 - 窗口字符
		QList<C_ScriptHelp_CommandCell> command_PluginCommand_old;	//指令 - 插件指令(旧)
		QList<C_ScriptHelp_CommandCell> command_EventComment_old;	//指令 - 事件注释(旧)
	public:
									//搜索 - 获取有效指令（不含其它指令）
		QList<C_ScriptHelp_CommandCell> getAllAvailableCommand();
									//搜索 - 获取全部指令
		QList<C_ScriptHelp_CommandCell> getAllCommand();
									//搜索 - 包含指定指令关键字
		bool hasCommandKeyWord(QString keyWord);
									//搜索 - 指令的正则规则（类型标签）
		QRegExp commandRe_tag();
									//搜索 - 指令的正则规则（附加注释）
		QRegExp commandRe_note();
		
	//-----------------------------------
	//----读取器
	public:
									//读取器 - 添加指令
									//		【说明】：添加一行字符串，格式需要是指令结构。
									//		【示例1】："插件指令：>某插件 : 变量[21]   （这个指令的内容介绍）"
									//		【示例2】："窗口字符：<br>   用于表示换行"
		void addOneRowCommand(QString command_row);

};
/*
-----==========================================================-----
		类：		帮助数据-指令 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
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
								//数据 - 获取全部指令 - 窗口字符
		QStringList getAllCommand_WindowChar();
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
								//搜索 - 包含指定指令关键字 - 窗口字符
		bool hasCommandKeyWord_WindowChar(QString keyWord);
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
	protected:
								//读取器 - 获取默认关键字
		QString getOldKeyword();

};
