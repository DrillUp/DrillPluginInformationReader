﻿#include "stdafx.h"
#include "C_ScriptHelpDetail.h"

#include "Source/Utils/Manager/TxtRead/P_TxtFastReader.h"

/*
-----==========================================================-----
		类：		帮助信息 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		插件注解中 @help 的全部数据+解析数据。
-----==========================================================-----
*/
C_ScriptHelpDetail::C_ScriptHelpDetail(){
	this->name = "";			 	//插件名（文件名）
	this->help = "";				//帮助信息（@help）

	this->m_effectScope = nullptr;			//作用域
	this->m_pluginRelation = nullptr;		//插件扩展
	this->m_src = nullptr;					//资源路径
	this->m_docs = nullptr;					//插件文档
	this->m_subsection = nullptr;			//分段说明
	this->m_command = nullptr;				//指令
	this->m_knowledge = nullptr;			//知识点
	this->m_performance = nullptr;			//插件性能
}
C_ScriptHelpDetail::~C_ScriptHelpDetail(){
}


/*-------------------------------------------------
		基本 - 设置插件名
*/
void C_ScriptHelpDetail::setName(QString name){
	this->name = name;
}
/*-------------------------------------------------
		基本 - 设置帮助信息
*/
void C_ScriptHelpDetail::setHelpContext(QString help){
	this->help = help;
	this->initHelpContext();
}
/*-------------------------------------------------
		基本 - 获取插件名
*/
QString C_ScriptHelpDetail::getName(){
	return this->name;
}
/*-------------------------------------------------
		基本 - 获取帮助信息
*/
QString C_ScriptHelpDetail::getHelpContext(){
	return this->help;
}


/*-------------------------------------------------
		私有 - 帮助信息初始化
*/
void C_ScriptHelpDetail::initHelpContext(){
	P_TxtFastReader reader = P_TxtFastReader(this->help);
	this->m_docs = new C_ScriptHelp_Docs();					//数据 - 插件文档（初始就要创建）
	this->m_command = new C_ScriptHelp_Command();			//数据 - 指令（初始就要创建）
	this->m_knowledge = new C_ScriptHelp_Knowledge();		//数据 - 知识点（初始就要创建）
	this->m_subsection = new C_ScriptHelp_Subsection();		//数据 - 分段说明（初始就要创建）

	// > 插件扩展
	int i_relation = reader.d_indexOf("----插件扩展");
	int i_relation_end = reader.d_indexOf("----------------------", i_relation + 1);
	if (i_relation != -1){
		int row_count = i_relation_end - i_relation - 1;
		QStringList relationComment = reader.d_getRows(i_relation + 1, row_count);
		this->m_pluginRelation = new C_ScriptHelp_PluginRelation();		//数据 - 插件扩展
		this->m_pluginRelation->readPluginRelation(relationComment.join("\n"));
	}

	// > 作用域
	int i_effectScope = reader.d_indexOf("插件的作用域：");
	if (i_effectScope != -1){
		this->m_effectScope = new C_ScriptHelp_EffectScope();	//数据 - 作用域
		QStringList row_list = reader.d_getRows(i_effectScope, 4);
		for (int k = 0; k < row_list.count(); k++){
			QString row = row_list.at(k);
			if (k == 0){
				QString data = row.split("插件的作用域：").last();
				data = data.replace(QRegExp("[\\.。]"), "").trimmed();
				this->m_effectScope->scope_list = data.split(QRegExp("[，,、]"));
				continue;
			}
			if (row.count() > 0 && row.at(0) == ' '){	//（有空格表示章节没说完）
				this->m_effectScope->comments.append(row);
				this->m_effectScope->comments.append("\n");
			}else{
				break;
			}
		}
	}

	// > 分段说明 - 介绍
	int i_introductionComment = reader.d_indexOf("===========");
	int i_introductionComment2 = reader.d_indexOf("===========", i_introductionComment+1);	//（第二条等号线）
	int i_introductionComment2_end = reader.d_indexOf("----------------------", i_introductionComment2+1);
	if (i_introductionComment2 != -1){
		int row_count = i_introductionComment2_end - i_introductionComment2 - 1;
		QStringList introductionComment = reader.d_getRows(i_introductionComment2 + 1, row_count);
		this->m_subsection->readHeader(introductionComment.join("\n"));
	}

	// > 分段说明 - 章节
	int i_mainComment = reader.d_indexOf("----设定注意事项");
	int i_mainComment_end = reader.d_indexOf("----------------------", i_mainComment + 1);
	if (i_mainComment != -1){
		int row_count = i_mainComment_end - i_mainComment - 1;
		QStringList mainComment = reader.d_getRows(i_mainComment + 1, row_count);
		this->m_subsection->readSubsection(mainComment.join("\n"),this->m_docs);
	}

	// > 资源路径
	int i_src = reader.d_indexOf("----关联文件");
	int i_src_end = reader.d_indexOf("----------------------", i_src + 1);
	if (i_src != -1){
		int row_count = i_src_end - i_src - 1;
		QStringList srcComment = reader.d_getRows(i_src + 1, row_count);
		this->m_src = new C_ScriptHelp_Src();	//数据 - 资源路径
		this->m_src->readSrc(srcComment);
	}

	// > 指令
	int i_command = reader.d_indexOf(QRegExp("----(激活条件|可选设定)"));
	int i_command_end = reader.d_indexOf("----------------------", i_command + 1);
	for (int k = 0; k < 20; k++){		//（多组指令集）
		if (i_command == -1){ break; }

		int row_count = i_command_end - i_command - 1;
		if (row_count < 0){ row_count = -1; }
		QStringList commandComment = reader.d_getRows(i_command, row_count);
		this->m_command->readNextGroup(commandComment.join("\n"), this->m_docs);

		i_command = reader.d_indexOf(QRegExp("----(激活条件|可选设定)"), i_command + 1);
		i_command_end = reader.d_indexOf("----------------------", i_command + 1);
	}

	// > 知识点
	int i_knowledge = reader.d_indexOf(QRegExp("----(知识点|其他|其它|其他说明|其它说明)"));
	int i_knowledge_end = reader.d_indexOf("----------------------", i_knowledge + 1);
	for (int k = 0; k < 20; k++){		//（多组知识点集）
		if (i_knowledge == -1){ break; }

		int row_count = i_knowledge_end - i_knowledge - 1;
		if (row_count < 0){ row_count = -1; }
		QStringList knowledgeComment = reader.d_getRows(i_knowledge, row_count);
		this->m_knowledge->readNextGroup(knowledgeComment.join("\n"), this->m_docs);

		i_knowledge = reader.d_indexOf(QRegExp("----(知识点|其他|其它|其他说明|其它说明)"), i_knowledge + 1);
		i_knowledge_end = reader.d_indexOf("----------------------", i_knowledge + 1);
	}

	// > 插件性能
	int i_performance = reader.d_indexOf(QRegExp("----插件性能"));
	int i_performance_end = reader.d_indexOf("----------------------", i_performance + 1);
	if (i_performance != -1){
		int row_count = i_performance_end - i_performance - 1;
		if (row_count < 0){ row_count = -1; }
		QStringList performanceComment = reader.d_getRows(i_performance + 1, row_count);
		this->m_performance = new C_ScriptHelp_Performance();		//数据 - 插件性能
		this->m_performance->readPerformance(performanceComment.join("\n"));
	}

}
/*-------------------------------------------------
		数据 - 获取作用域
*/
C_ScriptHelp_EffectScope* C_ScriptHelpDetail::getEffectScope(){
	return this->m_effectScope;
}
/*-------------------------------------------------
		数据 - 获取插件扩展
*/
C_ScriptHelp_PluginRelation* C_ScriptHelpDetail::getPluginRelation(){
	return this->m_pluginRelation;
}
/*-------------------------------------------------
		数据 - 获取资源路径
*/
C_ScriptHelp_Src* C_ScriptHelpDetail::getSrc(){
	return this->m_src;
}
/*-------------------------------------------------
		数据 - 获取插件文档
*/
C_ScriptHelp_Docs* C_ScriptHelpDetail::getDocs(){
	return this->m_docs;
}
/*-------------------------------------------------
		数据 - 获取分段说明
*/
C_ScriptHelp_Subsection* C_ScriptHelpDetail::getSubsection(){
	return this->m_subsection;
}
/*-------------------------------------------------
		数据 - 获取指令
*/
C_ScriptHelp_Command* C_ScriptHelpDetail::getCommand(){
	return this->m_command;
}
/*-------------------------------------------------
		数据 - 获取知识点
*/
C_ScriptHelp_Knowledge* C_ScriptHelpDetail::getKnowledge(){
	return this->m_knowledge;
}
/*-------------------------------------------------
		数据 - 获取插件性能
*/
C_ScriptHelp_Performance* C_ScriptHelpDetail::getPerformance(){
	return this->m_performance;
}

/*-------------------------------------------------
		操作 - 判断包含指定指令关键字
*/
bool C_ScriptHelpDetail::hasCommandKeyWord(QString keyWord){
	if (this->m_command == nullptr){ return false; }
	return this->m_command->hasCommandKeyWord_All(keyWord);
}

/*-------------------------------------------------
		空判断
*/
bool C_ScriptHelpDetail::isNull(){
	return this->name == "";
}
/*-------------------------------------------------
		运算符重载
*/
const bool C_ScriptHelpDetail::operator== (const C_ScriptHelpDetail& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		实体类 -> QJsonObject
*/
QJsonObject C_ScriptHelpDetail::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("help", this->help);
	return obj;
}
/*-------------------------------------------------
		QJsonObject -> 实体类
*/
void C_ScriptHelpDetail::setJsonObject(QJsonObject obj){

	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("help").isUndefined() == false){ this->help = obj.value("help").toString(); }

}

