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
	this->group_name = "";					//组名称
	this->is_important = false;				//是否为激活条件
	this->context = QStringList();			//内容列表
}
C_ScriptHelp_CommandGroup::~C_ScriptHelp_CommandGroup(){
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
		读取器 - 读取新的指令集字符串
*/
void C_ScriptHelp_Command::readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs){
	if (group_context == ""){ return; }
	C_ScriptHelp_CommandGroup group;
	P_TxtFastReader group_reader = P_TxtFastReader(group_context);

	// > 标题捕获
	QString title = group_reader.d_getRows(0, 1).at(0);
	QStringList data_list = title.split(QRegExp("[ -]+"));
	TTool::_QStringList_clearEmptyRows_(&data_list);
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
	//...

}