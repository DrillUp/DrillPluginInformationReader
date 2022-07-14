#pragma once

#include "c_ScriptAnnotation.h"

/*
-----==========================================================-----
		类：		插件注解读取器.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		读取js文件内的所有数据 @的注解 内容。
					（详细见.cpp）
-----==========================================================-----
*/

class S_ScriptAnnotationReader : public QObject
{
	Q_OBJECT

	public:
		S_ScriptAnnotationReader();
		~S_ScriptAnnotationReader();
		static S_ScriptAnnotationReader* cur_manager;			//单例
		static S_ScriptAnnotationReader* getInstance();			//单例，获取自己（必须要拿到全局配置才能进行计算）

	//-----------------------------------
	//----读取
	public:
										//读取 - 插件参数（简要）
										//		【参数】：文件完整路径，"C:/aaa/ccc/DrillTip1.js"。
										//		【说明】：只含 插件名、插件详细、作者、帮助信息。
		C_ScriptAnnotation readPlugin_simple(QString file_fullPath);
										//读取 - 插件参数（完整）
										//		【参数】：文件完整路径，"C:/aaa/ccc/DrillTip1.js"。
										//		【说明】：包含插件全部完整的信息。
		C_ScriptAnnotation readPlugin_complete(QString file_fullPath);
	
	private:
										//私有 - 解析帮助信息 获取到 数据
		C_ScriptHelpDetail* readScriptHelpDetail(QString help_context);
										//私有 - 解析插件信息 获取到 参数
		C_ScriptDictionary* readScriptDictionary(QString plugin_context);
		
	//-----------------------------------
	//----解析
	public:
										//解析 - 作用域
		//QString getContentField(QString plugin_helpContext);
										//解析 - 关联文件
		//QString getContentFiles(QString plugin_helpContext);
};
