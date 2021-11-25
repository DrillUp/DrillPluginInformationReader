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
	this->context_note = QStringList();			//内容列表

	this->context_command = QString();					//指令全文
	this->command_PluginCommand = QStringList();		//指令 - 插件指令
	this->command_PluginCommand_old = QStringList();	//指令 - 插件指令(旧)
	this->command_EventComment = QStringList();			//指令 - 事件注释
	this->command_EventComment_old = QStringList();		//指令 - 事件注释(旧)
	this->command_MapNote = QStringList();				//指令 - 地图备注
	this->command_ActorNote = QStringList();			//指令 - 角色注释
	this->command_EnemyNote = QStringList();			//指令 - 敌人注释
	this->command_StateNote = QStringList();			//指令 - 状态注释
	this->command_ItemNote = QStringList();				//指令 - 物品/武器/护甲注释
	this->command_SkillNote = QStringList();			//指令 - 技能注释
	this->command_MoveRoute = QStringList();			//指令 - 移动路线指令
	this->command_WindowChar = QStringList();			//指令 - 窗口字符
	this->command_Other = QStringList();				//指令 - 其它
}
C_ScriptHelp_CommandGroup::~C_ScriptHelp_CommandGroup(){
}

/*-------------------------------------------------
		读取器 - 添加指令
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
	}else if (type_str == "地图备注"){
		this->command_MapNote.append(commend_str);
	}else if (type_str == "角色注释" || type_str == "角色备注"){
		this->command_ActorNote.append(commend_str);
	}else if (type_str == "敌人注释" || type_str == "敌人备注"){
		this->command_EnemyNote.append(commend_str);
	}else if (type_str == "状态注释"){
		this->command_StateNote.append(commend_str);
	}else if (type_str == "物品注释" || type_str == "物品备注" || 
			  type_str == "道具注释" || type_str == "道具备注" || 
			  type_str == "武器注释" || type_str == "武器备注" || 
			  type_str == "护甲注释" || type_str == "护甲备注" || 
			  type_str == "防具注释" || type_str == "防具备注" ){
		this->command_ItemNote.append(commend_str);
	}else if (type_str == "技能注释" || type_str == "技能备注"){
		this->command_SkillNote.append(commend_str);
	}else if (type_str == "移动路线指令" || type_str == "移动路线脚本"){
		this->command_MoveRoute.append(commend_str);
	}else if (type_str == "窗口字符"){
		this->command_WindowChar.append(commend_str);
	}else if (type_str == "插件指令(旧)" || type_str == "插件指令（旧）"){
		this->command_PluginCommand_old.append(commend_str);
	}else if (type_str == "事件注释(旧)" || type_str == "事件注释（旧）"){
		this->command_EventComment_old.append(commend_str);
	}else{
		this->command_Other.append(commend_str);
	}
}

/*-------------------------------------------------
		搜索 - 获取全部指令
*/
QStringList C_ScriptHelp_CommandGroup::getAllAvailableCommand(){
	return QStringList()
		<< this->command_PluginCommand
		<< this->command_PluginCommand_old
		<< this->command_EventComment
		<< this->command_EventComment_old
		<< this->command_MapNote
		<< this->command_ActorNote
		<< this->command_EnemyNote
		<< this->command_StateNote
		<< this->command_ItemNote
		<< this->command_SkillNote
		<< this->command_MoveRoute
		<< this->command_WindowChar;
}
/*-------------------------------------------------
		搜索 - 获取全部指令
*/
QStringList C_ScriptHelp_CommandGroup::getAllCommand(){
	return this->getAllAvailableCommand() << this->command_Other;
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字
*/
bool C_ScriptHelp_CommandGroup::hasCommandKeyWord(QString keyWord){
	QStringList data_list = this->getAllAvailableCommand();
	if (keyWord == ""){
		return data_list.count() > 0;
	}
	for (int j = 0; j < data_list.count(); j++){
		QString data = data_list.at(j);
		if (data.contains(keyWord)){
			return true;
		}
	}
	return false;
}
/*-------------------------------------------------
		搜索 - 指令的正则规则
*/
QRegExp C_ScriptHelp_CommandGroup::commandRe(){
	return QRegExp("^[^ ]{4,7}[:：]");		//（正则：4到7个字以内且含冒号的，算作一条指令行，比如 "插件指令(旧)：" ）
}
/*-------------------------------------------------
		数据 - 获取名称
*/
QString C_ScriptHelp_CommandGroup::getGroupFullName(){
	QString rusult = "";
	if (this->is_important){
		rusult = "激活条件";
	}else{
		rusult = "可选设定";
	}
	if (this->group_name != ""){
		rusult.append(" - ");
		rusult.append(this->group_name);
	}
	return rusult;
}

/*-------------------------------------------------
		数据 - 网格竖切 - 获取全部标签
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_TagList(){
	QStringList data_list = this->context_command.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 0; i < data_list.count(); i++){
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << re.cap(0);
		}else{
			result_list << "";	//（保留空行）
		}
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 网格竖切 - 获取全部指令
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_CommandList(){
	QStringList data_list = this->context_command.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 0; i < data_list.count(); i++){
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << data.mid(pos + re.cap(0).length());
		}else{
			result_list << data;	//（若未成功读取，直接显示全部内容）
		}
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 网格竖切 - 获取全部标签
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_OldTagList(){
	QStringList data_list = this->context_command_old.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 1; i < data_list.count(); i++){	//（从第二行开始获取）
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << re.cap(0);
		}else{
			result_list << "";	//（保留空行）
		}
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 网格竖切 - 获取全部指令
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_OldCommandList(){
	QStringList data_list = this->context_command_old.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 1; i < data_list.count(); i++){	//（从第二行开始获取）
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << data.mid(pos + re.cap(0).length());
		}else{
			result_list << data;	//（若未成功读取，直接显示全部内容）
		}
	}
	return result_list;
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
		数据 - 获取全部指令 - 插件指令
*/
QStringList C_ScriptHelp_Command::getAllCommand_PluginCommand(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_PluginCommand);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 插件指令(旧)
*/
QStringList C_ScriptHelp_Command::getAllCommand_PluginCommandOld(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_PluginCommand_old);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 事件注释
*/
QStringList C_ScriptHelp_Command::getAllCommand_EventComment(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_EventComment);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 事件注释(旧)
*/
QStringList C_ScriptHelp_Command::getAllCommand_EventCommentOld(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_EventComment_old);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 地图备注
*/
QStringList C_ScriptHelp_Command::getAllCommand_MapNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_MapNote);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 角色注释
*/
QStringList C_ScriptHelp_Command::getAllCommand_ActorNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_ActorNote);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 敌人注释
*/
QStringList C_ScriptHelp_Command::getAllCommand_EnemyNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_EnemyNote);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 状态注释
*/
QStringList C_ScriptHelp_Command::getAllCommand_StateNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_StateNote);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 物品/武器/护甲注释
*/
QStringList C_ScriptHelp_Command::getAllCommand_ItemNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_ItemNote);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 技能注释
*/
QStringList C_ScriptHelp_Command::getAllCommand_SkillNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_SkillNote);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 移动路线指令
*/
QStringList C_ScriptHelp_Command::getAllCommand_MoveRoute(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_MoveRoute);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 窗口字符
*/
QStringList C_ScriptHelp_Command::getAllCommand_WindowChar(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_WindowChar);
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取全部指令 - 其它
*/
QStringList C_ScriptHelp_Command::getAllCommand_Other(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_Other);
	}
	return result_list;
}

/*-------------------------------------------------
		搜索 - 包含指定指令关键字
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_All(QString keyWord){
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_CommandGroup group = this->group_list.at(i);
		if (group.hasCommandKeyWord(keyWord) == true){
			return true;
		}
	}
	return false;
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 插件指令
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_PluginCommand(QString keyWord){
	QStringList data_list = this->getAllCommand_PluginCommand();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 插件指令(旧)
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_PluginCommandOld(QString keyWord){
	QStringList data_list = this->getAllCommand_PluginCommandOld();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 事件注释
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_EventComment(QString keyWord){
	QStringList data_list = this->getAllCommand_EventComment();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 事件注释(旧)
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_EventCommentOld(QString keyWord){
	QStringList data_list = this->getAllCommand_EventCommentOld();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 地图备注
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_MapNote(QString keyWord){
	QStringList data_list = this->getAllCommand_MapNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 角色注释
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_ActorNote(QString keyWord){
	QStringList data_list = this->getAllCommand_ActorNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 敌人注释
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_EnemyNote(QString keyWord){
	QStringList data_list = this->getAllCommand_EnemyNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 状态注释
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_StateNote(QString keyWord){
	QStringList data_list = this->getAllCommand_StateNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 物品/武器/护甲注释
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_ItemNote(QString keyWord){
	QStringList data_list = this->getAllCommand_ItemNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 技能注释
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_SkillNote(QString keyWord){
	QStringList data_list = this->getAllCommand_SkillNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 移动路线指令
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_MoveRoute(QString keyWord){
	QStringList data_list = this->getAllCommand_MoveRoute();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 窗口字符
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_WindowChar(QString keyWord){
	QStringList data_list = this->getAllCommand_WindowChar();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		搜索 - 包含指定指令关键字 - 其它
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_Other(QString keyWord){
	QStringList data_list = this->getAllCommand_Other();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		私有 - 判断关键字
*/
bool C_ScriptHelp_Command::searchCommandKeyWord(QStringList* command_list, QString keyWord){

	// > 空搜索情况
	if (keyWord == ""){
		if (command_list->count() == 0){
			return false;
		}else{
			return true;
		}
	}

	// > 搜索情况
	for (int i = 0; i < command_list->count(); i++){
		QString data = command_list->at(i);
		if (data.contains(keyWord)){
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
	if (data_list.contains("激活条件") || data_list.contains("激活方式") || data_list.contains("激活方法")){
		group.is_important = true;
	}else{
		group.is_important = false;
	}
	if (data_list.count() > 2){
		group.group_name = data_list.last();
	}

	//（指令特殊规则： 3x4 或 2x2x2 这种单个组中出现了间隔性的 插件指令，【要显示指令之间间隔的行，将其换成横线】。 ）

	// > 指令捕获
	int i_command = group_reader.d_indexOf(group.commandRe());
	int i_command_end = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.。]"), i_command + 1);
	int i_command_oldCommandEnd = group_reader.d_indexOf(this->getOldKeyword(), i_command_end);
	if (i_command != -1){
		int row_count = i_command_end - i_command;
		if (row_count < 0){ row_count = -1; }

		// > 指令全文（显示详细信息用）
		QStringList commandComment = group_reader.d_getRows(i_command, row_count);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.context_command = commandComment.join("\n");

		// > 依次捕获单行指令（搜索用）
		for (int i = 0; i < commandComment.count(); i++){
			group.addOneRowCommand(commandComment.at(i));
		}
	}

	// > 说明列表
	if (   i_command_end != -1
		&& i_command_end != i_command_oldCommandEnd){

		QStringList command_list = QStringList();
		QStringList commandComment = group_reader.d_getRows(i_command_end);
		if (i_command_oldCommandEnd != -1){
			commandComment = group_reader.d_getRows(i_command_end, i_command_oldCommandEnd-i_command_end);
		}
		if (commandComment.count() > 0 ){

			P_TxtFastReader commentReader = P_TxtFastReader(commandComment.join("\n"));
			int i_page = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."));	//（找到数字的行）
			for (int k = 0; k < 15; k++){
				if (i_page != -1){
			
					// > 向下搜索
					QStringList data_list = QStringList();
					int i_nextPage = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."), i_page + 1);	//（找到多个章节后，addPage，再在子函数中继续细分）
					if (i_nextPage != -1){
						int page_count = i_nextPage - i_page;
						data_list = commentReader.d_getRows(i_page, page_count);
					}else{
						data_list = commentReader.d_getRows(i_page);
					}
			
					// > 添加到列表
					if (data_list.count() > 0){
						QString data = data_list.join("\n");
						c_docs->addRelativeDocx(c_docs->findDocsNameList(data));	//【插件文档 - 相关文档】
						command_list.append(data);
					}
			
					i_page = i_nextPage;
				}else{
					break;
				}
			}
		}
		group.context_note = command_list;
	}

	// > 旧指令
	if (i_command_oldCommandEnd != -1){

		// > 指令全文（详细信息用）
		QStringList commandComment_old = group_reader.d_getRows(i_command_oldCommandEnd);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment_old);
		group.context_command_old = commandComment_old.join("\n");

		// > 依次捕获单行指令（搜索用）
		for (int i = 0; i < commandComment_old.count(); i++){
			group.addOneRowCommand(commandComment_old.at(i));
		}
	}
	this->group_list.append(group);
}
/*-------------------------------------------------
		读取器 - 获取默认关键字
*/
QString C_ScriptHelp_Command::getOldKeyword(){
	return "以下是旧版本的指令";
}