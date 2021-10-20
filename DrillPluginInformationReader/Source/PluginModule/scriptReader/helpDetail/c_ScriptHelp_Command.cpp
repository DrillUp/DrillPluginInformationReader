#include "stdafx.h"
#include "c_ScriptHelp_Command.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		帮助数据-指令 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_CommandGroup::C_ScriptHelp_CommandGroup(){
	this->group_name = "";						//组名称
	this->is_important = false;					//是否为激活条件
	this->note_context = QStringList();			//内容列表

	this->command_context = QString();					//指令全文
	this->command_PluginCommand = QStringList();		//指令 - 插件指令
	this->command_PluginCommand_old = QStringList();	//指令 - 插件指令(旧)
	this->command_EventComment = QStringList();			//指令 - 事件注释
	this->command_EventComment_old = QStringList();		//指令 - 事件注释(旧)
	this->command_EventNote = QStringList();			//指令 - 事件备注
	this->command_MapNote = QStringList();				//指令 - 地图备注
	this->command_ActorNote = QStringList();			//指令 - 角色注释
	this->command_EnemyNote = QStringList();			//指令 - 敌人注释
	this->command_Other = QStringList();				//指令 - 其它
}
C_ScriptHelp_CommandGroup::~C_ScriptHelp_CommandGroup(){
}

/*-------------------------------------------------
		数据 - 添加指令
*/
void C_ScriptHelp_CommandGroup::addOneRowCommand(QString command_row){
	if (command_row.isEmpty()){ return; }
	if (command_row.contains(this->commandRe()) == false){ return; }

	int index = command_row.indexOf(QRegExp("[:：]"));
	QString type_str = command_row.mid(0, index);
	QString commend_str = command_row.mid(index + 1);
	if (type_str == "插件指令"){
		this->command_PluginCommand.append(commend_str);
	}else if (type_str == "事件注释"){
		this->command_EventComment.append(commend_str);
	}else if (type_str == "事件备注"){
		this->command_EventNote.append(commend_str);
	}else if (type_str == "地图备注"){
		this->command_MapNote.append(commend_str);
	}else if (type_str == "角色注释" || type_str == "角色备注"){
		this->command_ActorNote.append(commend_str);
	}else if (type_str == "敌人注释" || type_str == "敌人备注"){
		this->command_EnemyNote.append(commend_str);
	}else if (type_str == "插件指令(旧)" || type_str == "插件指令（旧）"){
		this->command_PluginCommand_old.append(commend_str);
	}else if (type_str == "事件注释(旧)" || type_str == "事件注释（旧）"){
		this->command_EventComment_old.append(commend_str);
	}else{
		this->command_Other.append(commend_str);
	}
}
/*-------------------------------------------------
		数据 - 获取全部指令
*/
QStringList C_ScriptHelp_CommandGroup::getAllCommand(){
	return QStringList()
		<< this->command_PluginCommand
		<< this->command_PluginCommand_old
		<< this->command_EventComment
		<< this->command_EventComment_old
		<< this->command_EventNote
		<< this->command_MapNote
		<< this->command_ActorNote
		<< this->command_EnemyNote
		<< this->command_Other;
}
/*-------------------------------------------------
		数据 - 包含指定指令关键字
*/
bool C_ScriptHelp_CommandGroup::hasCommandKeyWord(QString keyWord){
	QStringList data_list = this->getAllCommand();
	for (int j = 0; j < data_list.count(); j++){
		QString data = data_list.at(j);
		if (data.contains(keyWord)){
			return true;
		}
	}
	return false;
}
/*-------------------------------------------------
		数据 - 指令的正则规则
*/
QRegExp C_ScriptHelp_CommandGroup::commandRe(){
	return QRegExp("^[^ ]{4,7}[:：]");		//（正则：4到7个字以内且含冒号的，算作一条指令行，比如 "插件指令(旧)：" ）
}


/*
-----==========================================================-----
		类：		帮助数据-指令 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Command::C_ScriptHelp_Command(){
	this->group_list = QList<C_ScriptHelp_CommandGroup>();
}
C_ScriptHelp_Command::~C_ScriptHelp_Command(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_Command::isNull(){
	return this->group_list.count() == 0;
}
/*-------------------------------------------------
		数据 - 指令集列表
*/
QList<C_ScriptHelp_CommandGroup> C_ScriptHelp_Command::getGroupList(){
	return this->group_list;
}
/*-------------------------------------------------
		数据 - 包含指定指令关键字
*/
bool C_ScriptHelp_Command::hasCommandKeyWord(QString keyWord){
	if (keyWord.isEmpty()){ return false; }

	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_CommandGroup group = this->group_list.at(i);
		if (group.hasCommandKeyWord(keyWord) == true){
			return true;
		}
	}
	return false;
}


/*-------------------------------------------------
		读取器 - 读取新的指令集字符串
*/
void C_ScriptHelp_Command::readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs){
	if (group_context == ""){ return; }
	C_ScriptHelp_CommandGroup group;
	P_TxtFastReader group_reader = P_TxtFastReader(group_context);

	// > 标题捕获
	QString title = group_reader.d_getRows(0, 1).at(0);
	QStringList data_list = title.split(QRegExp("[ -]+"));
	if (data_list.contains("激活条件")){
		group.is_important = true;
	}else{
		group.is_important = false;
	}
	if (data_list.count() > 1){
		group.group_name = data_list.last();
	}

	//（指令特殊规则： 3x4 或 2x2x2 这种单个组中出现了间隔性的 插件指令，【要显示指令之间间隔的行，将其换成横线】。 ）

	// > 指令捕获
	int i_command = group_reader.d_indexOf(group.commandRe());
	int i_command_end = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.。]"), i_command + 1);
	if (i_command != -1){
		int row_count = i_command_end - i_command;
		if (row_count < 0){ row_count = -1; }
		QStringList commandComment = group_reader.d_getRows(i_command, row_count);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.command_context = commandComment.join("\n");

		for (int i = 0; i < commandComment.count(); i++){
			group.addOneRowCommand(commandComment.at(i));
		}
	}

	// > 说明列表
	if (i_command_end != -1){
		QStringList commandComment = group_reader.d_getRows(i_command_end);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.note_context = commandComment;
	}
}