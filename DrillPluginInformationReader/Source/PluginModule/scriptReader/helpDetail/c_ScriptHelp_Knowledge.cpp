#include "stdafx.h"
#include "c_ScriptHelp_Knowledge.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		帮助数据-知识点 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_KnowledgeGroup::C_ScriptHelp_KnowledgeGroup(){
	this->group_name = "";						//组名称
	this->context_data = QStringList();			//内容列表
	this->context_note = QStringList();			//内容列表
}
C_ScriptHelp_KnowledgeGroup::~C_ScriptHelp_KnowledgeGroup(){
}


/*
-----==========================================================-----
		类：		帮助数据-指令 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Knowledge::C_ScriptHelp_Knowledge(){
	this->group_list = QList<C_ScriptHelp_KnowledgeGroup>();
}
C_ScriptHelp_Knowledge::~C_ScriptHelp_Knowledge(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_Knowledge::isNull(){
	return this->group_list.count() == 0;
}
/*-------------------------------------------------
		数据 - 指令集列表
*/
QList<C_ScriptHelp_KnowledgeGroup> C_ScriptHelp_Knowledge::getGroupList(){
	return this->group_list;
}

/*-------------------------------------------------
		读取器 - 读取新的指令集字符串
*/
void C_ScriptHelp_Knowledge::readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs){
	if (group_context == ""){ return; }
	C_ScriptHelp_KnowledgeGroup group;
	P_TxtFastReader group_reader = P_TxtFastReader(group_context);

	// > 标题捕获
	QString title = group_reader.d_getRows(0, 1).at(0);
	QStringList data_list = title.split(QRegExp("[ -]+"));
	if (data_list.count() > 2){
		group.group_name = data_list.last();
	}

	// > 内容捕获
	int i_context_note = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.。]"), 1);
	if (i_context_note > 0){

		// > 有说明内容时
		int row_count = i_context_note - 1;
		QStringList commandComment = group_reader.d_getRows(1, row_count);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.context_data = commandComment;
	}else{

		// > 无说明内容时（则全部为内容）
		QStringList commandComment = group_reader.d_getRows(1);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.context_data = commandComment;
	}

	// > 说明列表
	if (i_context_note > 0){
		QStringList contextComment = group_reader.d_getRows(i_context_note);
		if (contextComment.count() > 0){

			P_TxtFastReader commentReader = P_TxtFastReader(contextComment.join("\n"));
			int i_page = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."));	//（找到数字的行）
			for (int k = 0; k < 15; k++){
				if (i_page != -1){

					// > 向下搜索
					QStringList data_list = QStringList();
					int i_nextPage = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."), i_page + 1);	//（找到多个章节后，addPage，再在子函数中继续细分）
					if (i_nextPage != -1){
						int page_count = i_nextPage - i_page;
						data_list = commentReader.d_getRows(i_page, page_count);
					}
					else{
						data_list = commentReader.d_getRows(i_page);
					}

					// > 添加到列表
					if (data_list.count() > 0){
						QString data = data_list.join("\n");
						c_docs->addRelativeDocx(c_docs->findDocsNameList(data));	//【插件文档 - 相关文档】
						contextComment.append(data);
					}

					i_page = i_nextPage;
				}
				else{
					break;
				}
			}
		}
		group.context_note = contextComment;
	}

	this->group_list.append(group);
}