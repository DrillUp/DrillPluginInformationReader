#include "stdafx.h"
#include "c_ScriptHelp_Subsection.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"


/*
-----==========================================================-----
		类：		帮助数据-介绍 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的介绍内容。
					【开头"========"后面的几行内容】
-----==========================================================-----
*/
C_ScriptHelp_SubsectionHeader::C_ScriptHelp_SubsectionHeader(){
	this->introduction = "";
	this->package = "";
	this->condition = QStringList();
}
C_ScriptHelp_SubsectionHeader::~C_ScriptHelp_SubsectionHeader(){
}

/*
-----==========================================================-----
		类：		帮助数据-章节 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的章节。
					【"----设定注意事项"后面的小分段内容】
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
					【综合 上面的数据 和 "作用域"后面的内容点】
-----==========================================================-----
*/
C_ScriptHelp_Subsection::C_ScriptHelp_Subsection(){
	this->header = C_ScriptHelp_SubsectionHeader();
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
		数据 - 设置介绍数据
*/
void C_ScriptHelp_Subsection::setHeader(QString context){
	if (context == ""){ return; }
	P_TxtFastReader header_reader = P_TxtFastReader(context);
	C_ScriptHelp_SubsectionHeader header;

	int i_introductionEnd = header_reader.d_indexOf(QRegExp("[【★]"));
	if (i_introductionEnd == -1){

		// > 整个都是 简介
		header.introduction = context.replace(QRegExp("[\n\r]+")," ");
	}else{
		
		// > 简介
		QStringList introduction_list = header_reader.d_getRows(0,i_introductionEnd);
		header.introduction = introduction_list.join(" ");

		// > 打包支持提示
		QStringList data_list = header_reader.d_getRows(i_introductionEnd);
		QString data = data_list.first();
		if (data.contains("【")){
			header.package = data.replace(QRegExp("[【】]"), "");
		}else{

			// > 必要条件列表
			header.condition.append(data);	//★不替换
		}

		// > 必要条件列表
		if (data_list.count() > 1){
			for (int i = 1; i < data_list.count(); i++){
				QString data = data_list.at(i);
				header.condition.append(data);	//★不替换
			}
		}
	}
	this->header = header;
}
/*-------------------------------------------------
		数据 - 添加章节
*/
void C_ScriptHelp_Subsection::readNextPage(QString page_context){
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
		数据 - 空判断
*/
bool C_ScriptHelp_Subsection::isNull(){
	return this->main_list.count() == 0 && this->page_list.count() == 0 && this->header.introduction == "";
}
/*-------------------------------------------------
		数据 - 获取主内容
*/
QStringList C_ScriptHelp_Subsection::getMainContext(){
	return this->main_list;
}
/*-------------------------------------------------
		数据 - 获取介绍数据
*/
C_ScriptHelp_SubsectionHeader C_ScriptHelp_Subsection::getHeader(){
	return this->header;
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
