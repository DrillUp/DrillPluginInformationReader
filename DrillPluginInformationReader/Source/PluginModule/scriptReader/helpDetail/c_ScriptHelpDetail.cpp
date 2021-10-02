#include "stdafx.h"
#include "c_ScriptHelpDetail.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"

/*
-----==========================================================-----
		类：		插件注解 实体类.cpp
		所属模块：	插件模块
		功能：		插件注解的数据。

		必要事项：	> 框架数据为从js脚本中读取到的数据。
					  由于js脚本随时可变，所以不建议存储。
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

	// > 插件扩展
	int i_relation = reader.d_indexOf("----插件扩展");
	if (i_relation != -1){

	}

	// > 作用域
	int i_effectScope = reader.d_indexOf("插件的作用域：");
	if (i_effectScope != -1){
		this->m_effectScope = new C_ScriptHelp_EffectScope();
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


	// > 分段说明
	int i_mainComment = reader.d_indexOf("----设定注意事项");
	int i_mainComment_end = reader.d_indexOf("----------------------", i_mainComment + 1);
	if (i_mainComment != -1){
		int row_count = i_mainComment_end - i_mainComment - 1;
		QStringList mainComment = reader.d_getRows(i_mainComment + 1, row_count);
		P_TxtFastReader main_reader = P_TxtFastReader(mainComment.join("\n"));

		C_ScriptHelp_Subsection* subsection = new C_ScriptHelp_Subsection();

		// > 分段说明 - 主内容
		int i_main = main_reader.d_indexOf(QRegExp("^[\\d]+[\\.。]"));
		int i_page = i_main;
		for (int k = 0; k < 15; k++){
			if (i_main != -1){
				int i_nextMain = main_reader.d_indexOf(QRegExp("^[^ ]+"), i_main + 1);	//（后续行有空格表示内容没完）
				if (i_nextMain != -1){
					int main_count = i_nextMain - i_main;
					QStringList data = main_reader.d_getRows(i_main, main_count);
					subsection->main_list.append(data.join("\n"));
				}else{
					QStringList data = main_reader.d_getRows(i_main);
					subsection->main_list.append(data.join("\n"));
				}
				i_main = main_reader.d_indexOf(QRegExp("^[\\d]+[\\.。]"), i_main + 1);
			}else{
				break;
			}
		}

		// > 分段说明 - 章节
		i_page = main_reader.d_indexOf(QRegExp("^[^ \\d]+"), i_page + 1);	//（找到非空格、非数字的行）
		for (int k = 0; k < 15; k++){
			if (i_page != -1){
				QStringList title_list = main_reader.d_getRows(i_page - 1, 1);
				int i_nextPage = main_reader.d_indexOf(QRegExp("^[^ \\d]+"), i_page + 1);	//（找到多个章节后，addPage，再在子函数中继续细分）
				if (i_nextPage != -1){
					int page_count = i_nextPage - i_page;
					QStringList data = main_reader.d_getRows(i_page, page_count);
					subsection->addPage(data.join("\n"));
					i_page = i_nextPage;
				}else{
					QStringList data = main_reader.d_getRows(i_page);
					subsection->addPage(data.join("\n"));
					break;
				}
			}else{
				break;
			}
		}
	}

	// > 资源路径

	// > 插件文档

	// > 指令

	// > 插件性能

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
		数据 - 获取插件性能
*/
C_ScriptHelp_Performance* C_ScriptHelpDetail::getPerformance(){
	return this->m_performance;
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

