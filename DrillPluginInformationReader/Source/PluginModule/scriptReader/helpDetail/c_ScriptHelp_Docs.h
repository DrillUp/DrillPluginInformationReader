#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-插件文档 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Docs{

	public:
		C_ScriptHelp_Docs();
		~C_ScriptHelp_Docs();

	//-----------------------------------
	//----数据
	public:
		QStringList main_docx;		//主要帮助文档
		QStringList relative_docx;	//相关帮助文档
	public:
									//数据 - 空判断
		bool isNull();
									//数据 - 添加主要文档
		void addMainDocx(QString docx);
		void addMainDocx(QStringList docx_list);
									//数据 - 添加相关文档
		void addRelativeDocx(QString docx);
		void addRelativeDocx(QStringList docx_list);
									//数据 - 是否含有文档
		bool hasAnyDocx();
		
	//-----------------------------------
	//----读取器
	public:
									//读取器 - 寻找文档名称
									//		【说明1】：文档包括 docx 和 xlsx。名称前面需要空格或引号，如格式"xxx.docx"或 xxxx xxx.docx。
									//		【说明2】：该函数只是个工具函数，返回的结果可以选择手动添加到该数据类中。
		QStringList findDocsNameList(QString context);
};
