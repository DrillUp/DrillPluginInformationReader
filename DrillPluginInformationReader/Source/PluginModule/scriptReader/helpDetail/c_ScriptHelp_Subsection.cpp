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
	this->context = QStringList();
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
		数据 - 设置主内容
*/
void C_ScriptHelp_Subsection::setMainContext(QStringList mainContext_list){
	this->main_list = mainContext_list;
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
	
	// > 小章节
	QRegExp page_re("^[ ]+[\\(（][\\d]+\\.");
	int i_label = page_reader.d_indexOf(page_re, 1);	//（找到括号章节）
	for (int i = 0; i < 15; i++){
		if (i_label != -1){
			int i_nextLabel = page_reader.d_indexOf(page_re, i_label + 1);
			if (i_nextLabel != -1){
				int page_count = i_nextLabel - i_label;
				QStringList data_list = page_reader.d_getRows(i_label, page_count);

				// > 去掉 序号前缀和空格
				QStringList result_list = QStringList();
				for (int j = 0; j < data_list.count(); j++){
					QString text = data_list.at(j);
					text = text.replace(page_re, "");
					result_list.append(text.trimmed());
				}

				page.context.append(result_list.join("\n"));
				i_label = i_nextLabel;
			}else{
				QStringList data_list = page_reader.d_getRows(i_label);

				// > 去掉 序号前缀和空格
				QStringList result_list = QStringList();
				for (int j = 0; j < data_list.count(); j++){
					QString text = data_list.at(j);
					text = text.replace(page_re, "");
					result_list.append(text.trimmed());
				}

				page.context.append(result_list.join("\n"));
				break;
			}
		}
		else{
			break;
		}
	}

	this->page_list.append(page);
}


/*-------------------------------------------------
		数据 - 获取主内容
*/
QStringList C_ScriptHelp_Subsection::getMainContext(){
	return this->main_list;
}
/*-------------------------------------------------
		数据 - 获取章节标题
*/
QStringList C_ScriptHelp_Subsection::getAllTitle(){
	QStringList result;
	for (int i = 0; i < this->page_list.count(); i++){
		result.append(page_list.at(i).title);
	}
	return result;
}
/*-------------------------------------------------
		数据 - 获取章节（根据标题）
*/
C_ScriptHelp_SubsectionPage C_ScriptHelp_Subsection::getPageByTitle(QString title){
	for (int i = 0; i < this->page_list.count(); i++){
		C_ScriptHelp_SubsectionPage page = this->page_list.at(i);
		if (page.title == title){
			return page;
		}
	}
	return C_ScriptHelp_SubsectionPage();
}
/*-------------------------------------------------
		数据 - 获取章节内容（根据标题）
*/
QStringList C_ScriptHelp_Subsection::getPageContextByTitle(QString title){
	return this->getPageByTitle(title).context;
}
