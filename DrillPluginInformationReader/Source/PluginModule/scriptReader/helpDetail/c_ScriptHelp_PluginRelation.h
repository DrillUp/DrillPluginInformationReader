#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-扩展组 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_PluginRelationGroup{

	public:
		C_ScriptHelp_PluginRelationGroup();
		~C_ScriptHelp_PluginRelationGroup();

	//-----------------------------------
	//----数据
	public:
		QString title;					//组标题（类型）
		QStringList plugin_context;		//插件说明
	public:
								//数据 - 空判断
		bool isNull();
								//数据 - 类型 基于
		bool isBaseOn();
								//数据 - 类型 可被扩展/可扩展
		bool isBeingExtend();
								//数据 - 类型 可作用于/作用于
		bool isEffectTo();
								//数据 - 类型其它
		bool isOther();
};

/*
-----==========================================================-----
		类：		帮助数据-插件扩展 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_PluginRelation{

	public:
		C_ScriptHelp_PluginRelation();
		~C_ScriptHelp_PluginRelation();

	//-----------------------------------
	//----数据
	protected:
		QStringList context;								//插件扩展 - 主内容说明
		QList<C_ScriptHelp_PluginRelationGroup> group_list;	//插件扩展 - 扩展组
	public:
								//数据 - 获取主内容
		QStringList getMainContext();
								//数据 - 获取 基于 的插件信息
		QStringList getContextByBaseOn();
								//数据 - 获取 可被扩展 的插件信息
		QStringList getContextByBeingExtend();
								//数据 - 获取 可作用于 的插件信息
		QStringList getContextByEffectTo();
								//数据 - 获取 其它 插件信息
		QStringList getContextByOther();
								//数据 - 空判断
		bool isNull();

	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 插件扩展 字符串
		void readPluginRelation(QString relation_context);

};
