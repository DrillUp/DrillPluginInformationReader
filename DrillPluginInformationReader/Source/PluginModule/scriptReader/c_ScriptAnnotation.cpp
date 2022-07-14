#include "stdafx.h"
#include "c_ScriptAnnotation.h"

#include "helpDetail/c_ScriptHelpDetail.h"
#include "scriptDictionary/c_ScriptDictionary.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件注解 实体类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		插件注解的数据。
					【该数据类的初始化通过读取器赋值来完成。】
					
		注意：		> 框架数据为从js脚本中读取到的数据。
					  由于js脚本随时可变，所以不建议存储。
-----==========================================================-----
*/
C_ScriptAnnotation::C_ScriptAnnotation(){
	this->name = "";					//插件名（文件名）
	this->plugindesc = "";				//插件描述（@plugindesc）
	this->author = "";					//作者（@author）
	this->helpDetail = nullptr;		 	//帮助信息（@help + 解析内容）
	this->dictionary = nullptr; 		//参数字典（@param全部内容）

	this->temp_inited = false;
	this->temp_version = "";			//版本(调取时才初始化）
	this->temp_type = "";				//类型（调取时才初始化）
	this->temp_name = "";				//中文名（调取时才初始化）
}
C_ScriptAnnotation::~C_ScriptAnnotation(){
}


//数据 - 获取插件名（文件名）
QString C_ScriptAnnotation::getName(){ return this->name; }
//数据 - 获取插件描述（@plugindesc）
QString C_ScriptAnnotation::getPlugindesc(){ return this->plugindesc; }
//数据 - 获取作者（@author）
QString C_ScriptAnnotation::getAuthor(){ return this->author; }
//数据 - 获取帮助信息全文（@help）
QString C_ScriptAnnotation::getHelp(){
	if (this->helpDetail == nullptr){ return ""; }
	return this->helpDetail->getHelpContext();
}
//数据 - 是否为完整解析的内容
bool C_ScriptAnnotation::isCompleted(){
	if (this->helpDetail == nullptr){ return false; }
	if (this->dictionary == nullptr){ return false; }
	return true;
}
//数据 - 帮助信息数据
C_ScriptHelpDetail* C_ScriptAnnotation::getScriptHelpDetail(){ return this->helpDetail; }
//数据 - 参数字典数据
C_ScriptDictionary* C_ScriptAnnotation::getScriptDictionary(){ return this->dictionary; }


//数据 - 初始化截取段
void C_ScriptAnnotation::initPlugindesc_data(){
	this->temp_inited = true;

	// > 版本
	if (this->plugindesc.isEmpty() == false){			//（根据方括号截取内容）
		QString data = this->plugindesc.trimmed();
		QChar ch = data.at(0);
		if (ch == '[' || ch == '(' || ch == '（' || data.at(0) == 'v' || data.at(0) == 'V'){
			QStringList data_list = this->plugindesc.split("]");
			if (data_list.count() >= 2){
				this->temp_version = data_list.at(0) + "]";
			}else{
				data_list = this->plugindesc.split(" ");
				if (data_list.count() >= 2){
					this->temp_version = data_list.at(0);
				}
			}
		}
	}

	// > 类型
	QStringList data_list = this->plugindesc.split(" - ");	//（取横杠的左侧内容）
	if (data_list.count() >= 2){
		QStringList data_list2 = data_list.at(0).trimmed().split(QRegExp("[ \\]\\)]+"));
		this->temp_type = data_list2.last();
		if (this->temp_type.contains(".")){ this->temp_type = ""; }		//（含特殊字符的类型去掉）
		if (this->temp_type.contains("[")){ this->temp_type = ""; }
		if (this->temp_type.contains("]")){ this->temp_type = ""; }
		if (this->temp_type.contains("-")){ this->temp_type = ""; }

		// > 中文名
		data_list.removeFirst();
		this->temp_name = data_list.join(" - ");
	}else{

		// > 中文名
		QStringList data_list2 = this->plugindesc.split(" ");
		this->temp_name = data_list2.last();
	}
}
//数据 - 获取版本（插件描述 截取段）
QString C_ScriptAnnotation::getPlugindesc_version(){
	if (this->temp_inited == false){ this->initPlugindesc_data(); }
	return this->temp_version;
}
double C_ScriptAnnotation::getPlugindesc_versionNum(){
	if (this->temp_inited == false){ this->initPlugindesc_data(); }
	if (this->temp_version.isEmpty()){ return -1; }
	return TTool::_to_double_(this->temp_version);
}
//数据 - 获取类型（插件描述 截取段）
QString C_ScriptAnnotation::getPlugindesc_type(){
	if (this->temp_inited == false){ this->initPlugindesc_data(); }
	return this->temp_type;
}
//数据 - 获取中文名（插件描述 截取段）
QString C_ScriptAnnotation::getPlugindesc_name(){
	if (this->temp_inited == false){ this->initPlugindesc_data(); }
	return this->temp_name;
}


//数据 - 设置插件名（文件名）
void C_ScriptAnnotation::setName(QString name){ this->name = name; }
//数据 - 设置插件描述（@plugindesc）
void C_ScriptAnnotation::setPlugindesc(QString plugindesc){ this->plugindesc = plugindesc; }
//数据 - 设置作者（@author）
void C_ScriptAnnotation::setAuthor(QString author){ this->author = author; }
//数据 - 设置帮助信息数据
void C_ScriptAnnotation::setScriptHelpDetail(C_ScriptHelpDetail* helpDetail){ this->helpDetail = helpDetail; }
//数据 - 设置参数字典数据
void C_ScriptAnnotation::setScriptDictionary(C_ScriptDictionary* dictionary){ this->dictionary = dictionary; }


/*-------------------------------------------------
		空判断
*/
bool C_ScriptAnnotation::isNull(){
	return this->name == "";
}
/*-------------------------------------------------
		运算符重载
*/
const bool C_ScriptAnnotation::operator== (const C_ScriptAnnotation& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		实体类 -> QJsonObject
*/
QJsonObject C_ScriptAnnotation::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("plugindesc", this->plugindesc);
	obj.insert("author", this->author);
	if (this->helpDetail != nullptr){ obj.insert("helpDetail", this->helpDetail->getJsonObject()); }
	if (this->dictionary != nullptr){ obj.insert("dictionary", this->dictionary->getJsonObject()); }	
	return obj;
}
/*-------------------------------------------------
		QJsonObject -> 实体类
*/
void C_ScriptAnnotation::setJsonObject(QJsonObject obj){
	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("plugindesc").isUndefined() == false){ this->plugindesc = obj.value("plugindesc").toString(); }
	if (obj.value("author").isUndefined() == false){ this->author = obj.value("author").toString(); }

	if (obj.value("helpDetail").isUndefined() == false){ 
		this->helpDetail = new C_ScriptHelpDetail();
		this->helpDetail->setJsonObject(obj.value("helpDetail").toObject());
	}
	if (obj.value("dictionary").isUndefined() == false){
		this->dictionary = new C_ScriptDictionary();
		this->dictionary->setJsonObject(obj.value("dictionary").toObject());
	}
}
