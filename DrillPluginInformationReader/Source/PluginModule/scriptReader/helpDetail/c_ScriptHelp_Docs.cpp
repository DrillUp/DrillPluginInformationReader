#include "stdafx.h"
#include "c_ScriptHelp_Docs.h"


/*
-----==========================================================-----
		类：		帮助数据-插件文档 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。只存了文档名称，没存文件夹。
					【文档名称必须独一无二，链接都必须根据文档名称来找路径。】
-----==========================================================-----
*/
C_ScriptHelp_Docs::C_ScriptHelp_Docs(){
	this->main_docx = QStringList();
	this->relative_docx = QStringList();
}
C_ScriptHelp_Docs::~C_ScriptHelp_Docs(){
}

/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_Docs::isNull(){
	return this->main_docx.count() == 0 && this->relative_docx.count() == 0;
}
/*-------------------------------------------------
		数据 - 添加主要文档
*/
void C_ScriptHelp_Docs::addMainDocx(QString docx){
	if (this->main_docx.contains(docx)){ return; }	//（去重）
	if (this->relative_docx.contains(docx)){ return; }
	this->main_docx.append(docx);
}
void C_ScriptHelp_Docs::addMainDocx(QStringList docx_list){
	for (int i = 0; i < docx_list.count(); i++){
		this->addMainDocx(docx_list.at(i));
	}
}
/*-------------------------------------------------
		数据 - 添加相关文档
*/
void C_ScriptHelp_Docs::addRelativeDocx(QString docx){
	if (this->main_docx.contains(docx)){ return; }	//（去重）
	if (this->relative_docx.contains(docx)){ return; }
	this->relative_docx.append(docx);
}
void C_ScriptHelp_Docs::addRelativeDocx(QStringList docx_list){
	for (int i = 0; i < docx_list.count(); i++){
		this->addRelativeDocx(docx_list.at(i));
	}
}
/*-------------------------------------------------
		数据 - 是否含有文档
*/
bool C_ScriptHelp_Docs::hasAnyDocx(){
	if (this->main_docx.count() > 0){ return true; }
	if (this->relative_docx.count() > 0){ return true; }
	return false;
}


/*-------------------------------------------------
		读取器 - 寻找文档名称
*/
QStringList C_ScriptHelp_Docs::findDocsNameList(QString context){

	// > 获取到匹配（名称前面有 空格、引号 都可以）
	QRegExp rx("[ \"“]([^ \"“]+\\.(docx|xlsx))");
	QStringList match_list = QStringList();
	int pos = 0;
	while ((pos = rx.indexIn(context, pos)) != -1) {
		match_list << rx.cap(1);
		pos += rx.matchedLength();
	}
	return match_list;
}

