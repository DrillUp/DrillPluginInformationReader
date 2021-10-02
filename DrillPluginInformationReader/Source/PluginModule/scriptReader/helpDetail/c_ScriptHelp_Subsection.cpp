#include "stdafx.h"
#include "c_ScriptHelp_Subsection.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"

/*
-----==========================================================-----
		类：		帮助数据-章节 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的章节。
-----==========================================================-----
*/
C_ScriptHelp_SubsectionPage::C_ScriptHelp_SubsectionPage(){
	this->title = "";
	this->comment_list = QStringList();
}
C_ScriptHelp_SubsectionPage::~C_ScriptHelp_SubsectionPage(){
}

/*
-----==========================================================-----
		类：		帮助数据-分段说明 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Subsection::C_ScriptHelp_Subsection(){
	this->main_list = QStringList();
	this->page_list = QList<C_ScriptHelp_SubsectionPage>();
}
C_ScriptHelp_Subsection::~C_ScriptHelp_Subsection(){
}

/*-------------------------------------------------
		数据 - 添加章节
*/
void C_ScriptHelp_Subsection::addPage(QString page_context){
	if (page_context == ""){ return; }
	C_ScriptHelp_SubsectionPage page;
	P_TxtFastReader page_reader = P_TxtFastReader(page_context);

	// > 标题
	QString title = page_reader.d_getRows(0, 1).at(0);
	title = title.replace(QRegExp("[:：]"), "").trimmed();
	page.title = title;
	
	// > 小结
	int i_label = page_reader.d_indexOf(QRegExp("^[ ]+[\\(（][\\d]+"),1);	//（找到括号章节）
	for (int i = 0; i < 15; i++){
		if (i_label != -1){
			int i_nextLabel = page_reader.d_indexOf(QRegExp("^[ ]+[\\(（][\\d]+"), i_label + 1);
			if (i_nextLabel != -1){
				int page_count = i_nextLabel - i_label;
				QStringList data = page_reader.d_getRows(i_label, page_count);
				page.comment_list.append(data.join("\n"));
				i_label = i_nextLabel;
			}else{
				QStringList data = page_reader.d_getRows(i_label);
				page.comment_list.append(data.join("\n"));
				break;
			}
		}
		else{
			break;
		}
	}

	this->page_list.append(page);
}

