#include "stdafx.h"
#include "C_ScriptHelp_Src.h"


/*
-----==========================================================-----
		类：		帮助数据-资源路径 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Src::C_ScriptHelp_Src(){
	this->src_list = QStringList();				//资源路径
	this->context = QString();					//路径说明
	this->example = QString();					//举例说明
}
C_ScriptHelp_Src::~C_ScriptHelp_Src(){
}

/*-------------------------------------------------
		数据 - 读取 资源路径 字符串
*/
void C_ScriptHelp_Src::readSrc(QStringList src_contextRows){

	// > 资源路径 捕获
	int i_context = 0;
	for (int i = 0; i < 4; i++){
		QString row = src_contextRows.at(i);
		if (row.contains("资源路径：")){
			QString data = row.replace("资源路径：", "");
			data = data.mid(0, data.indexOf(QRegExp("[ \\(（\n]"))).trimmed();
			if (data.isEmpty() == false){
				this->src_list.append(data);
			}
			i_context += 1;
		}
		else{
			break;
		}
	}

	// > 其它说明文本 捕获
	QString context = "";
	QString example = "";
	bool is_context = true;
	for (int i = i_context; i < src_contextRows.count(); i++){
		QString row = src_contextRows.at(i);
		if (is_context == true && row.contains(QRegExp("[:：]"))){		//（根据下一行的冒号来分割 路径说明 和 举例说明 ）
			is_context = false;
			context.append(row);
			continue;
		}

		// > 路径说明
		if (is_context){
			context.append(row);
			context.append("\n");
			continue;
		}

		// > 举例说明
		example.append(row);
		if (i < src_contextRows.count() - 1){
			example.append("\n");
		}
	}
	this->context = context;
	this->example = example;
}
