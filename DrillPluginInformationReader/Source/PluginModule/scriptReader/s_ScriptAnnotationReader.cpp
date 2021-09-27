#include "stdafx.h"
#include "s_ScriptAnnotationReader.h"

#include "helpDetail/c_ScriptHelpDetail.h"
#include "scriptDictionary/c_ScriptDictionary.h"
#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"

/*
-----==========================================================-----
		类：		插件注解读取器.cpp
		所属模块：	插件模块
		功能：		读取js文件内的所有数据 @的注解 内容。

		使用方法：
				>初始化：
				
-----==========================================================-----
*/

S_ScriptAnnotationReader::S_ScriptAnnotationReader(){
}
S_ScriptAnnotationReader::~S_ScriptAnnotationReader() {
}

/* --------------------------------------------------------------
----------PluginFrameManager 单例
*/
S_ScriptAnnotationReader* S_ScriptAnnotationReader::cur_manager = NULL;
S_ScriptAnnotationReader* S_ScriptAnnotationReader::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_ScriptAnnotationReader();
	}
	return cur_manager;
}


/*-------------------------------------------------
		读取 - 插件参数（简要）
*/
C_ScriptAnnotation S_ScriptAnnotationReader::readPlugin_simple(QString file_fullPath) {
	C_ScriptAnnotation c_ScriptFrame = C_ScriptAnnotation();

	// > 读取工程文件
	QFile plugin_file(file_fullPath);
	if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "错误", "无法打开文件：" + file_fullPath, QMessageBox::Yes);
		return c_ScriptFrame;
	}
	QString plugin_context = plugin_file.readAll();
	plugin_file.close();

	// > 读取基本信息
	P_TxtFastReader reader = P_TxtFastReader(plugin_context);
	reader.prepare_trimAllRows();									// 去除空格
	reader.prepare_replaceInStrings(QRegExp("^\\*[ ]?"), "");		// 去除注释的前缀内容


	// > 获取 插件名
	QString name = QFileInfo(file_fullPath).completeBaseName();
	c_ScriptFrame.setName(name);

	// > 第一篇注释
	int i_comment_start = reader.d_indexOf("/*:");
	int i_comment_end = reader.d_indexOf("*/", i_comment_start);
	if (i_comment_start != -1) {

		// > 获取 描述
		int i_plugindesc = reader.d_indexOf("@plugindesc", i_comment_start);
		if (i_plugindesc != -1 && i_plugindesc <= i_comment_end) {
			QString s_rows = reader.d_getRows(i_plugindesc,2).join(" ");
			QStringList list_plugindesc = s_rows.split("@");
			if (list_plugindesc.size() >= 2) {
				QString s = list_plugindesc.at(1);
				QString plugindesc = s.replace("plugindesc", "").trimmed();
				c_ScriptFrame.setPlugindesc(plugindesc);
			}
		}

		// > 获取 作者
		int i_author = reader.d_indexOf("@author", i_comment_start);
		if (i_author != -1 && i_author <= i_comment_end) {
			QStringList list_author = reader.d_rowAt(i_author).split("@author");
			if (list_author.size() >= 2) {
				QString author = list_author.at(1).trimmed();
				c_ScriptFrame.setAuthor(author);
			}
		}

		// > 获取 帮助信息
		int i_help = reader.d_indexOf("@help", i_comment_start, i_comment_end);
		if (i_help != -1 && i_help <= i_comment_end) {
			QStringList list_help = reader.d_getRows(i_help, i_comment_end - i_help).join("\n").split("@help");	// 从@help开始到注释结束查找"@"
			if (list_help.size() >= 2) {
				QString help_text = list_help.at(1);
				help_text = help_text.replace("@help", "");
				int index = help_text.indexOf("@");
				help_text = help_text.mid(0, index);
				help_text = help_text.trimmed();	// 去除开头的结尾的"\n"和空格
				C_ScriptHelpDetail* helpDetail = this->readScriptHelpDetail(help_text);
				c_ScriptFrame.setScriptHelpDetail(helpDetail);
			}
		}
	}
	return c_ScriptFrame;
}
/*-------------------------------------------------
		读取 - 插件参数（完整）
*/
C_ScriptAnnotation S_ScriptAnnotationReader::readPlugin_complete(QString file_fullPath) {
	C_ScriptAnnotation c_ScriptFrame = this->readPlugin_simple(file_fullPath);

	// > 读取工程文件
	QFile plugin_file(file_fullPath);
	if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "错误", "无法打开文件：" + file_fullPath, QMessageBox::Yes);
		return c_ScriptFrame;
	}
	QString plugin_context = plugin_file.readAll();
	plugin_file.close();

	C_ScriptDictionary* dictionary = this->readScriptDictionary(plugin_context);
	c_ScriptFrame.setScriptDictionary(dictionary);

	return c_ScriptFrame;
}


/*-------------------------------------------------
		私有 - 解析帮助信息 获取到 数据
*/
C_ScriptHelpDetail* S_ScriptAnnotationReader::readScriptHelpDetail(QString help_context){
	C_ScriptHelpDetail* helpDetail = new C_ScriptHelpDetail();

	helpDetail->help = help_context;

	return helpDetail;
}

/*-------------------------------------------------
		私有 - 解析插件信息 获取到 参数
*/
C_ScriptDictionary* S_ScriptAnnotationReader::readScriptDictionary(QString plugin_context){
	C_ScriptDictionary* dictionary = new C_ScriptDictionary();

	// > 读取基本信息
	P_TxtFastReader reader = P_TxtFastReader(plugin_context);
	reader.prepare_trimAllRows();									// 去除空格
	reader.prepare_replaceInStrings(QRegExp("^\\*[ ]?"), "");		// 去除注释的前缀内容

	// > 第一篇注释
	int i_comment_start = reader.d_indexOf("/*:");
	int i_comment_end = reader.d_indexOf("*/", i_comment_start);
	if (i_comment_start != -1) {

		// > 获取 参数
		int i_param = reader.d_indexOf("@param", i_comment_start, i_comment_end);
		//..

	}

	// > 结构体
	int i_comment_struct = reader.d_indexOf(QRegExp("/\\*~struct~[\\S]+:"));
	//...

	return dictionary;
}