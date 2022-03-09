#pragma once
#include <QList>
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Subsection.h"

/*
-----==========================================================-----
		类：		灵感生成器-插件 数据类.h
		所属模块：	插件模块
		功能：		灵感生成器的插件数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_DesignTip{

	public:
		C_DesignTip();
		~C_DesignTip();

	//-----------------------------------
	//----数据
	public:
		QString plugin_name;					//所属插件（英文名）
		QString plugin_desc;					//所属插件（中文名）
		C_ScriptHelp_SubsectionPage page;		//内容列表
	public:
									//数据 - 空判断
		bool isNull();
};

/*
-----==========================================================-----
		类：		灵感生成器-插件集合 数据类.h
		所属模块：	插件模块
		功能：		灵感生成器中用到的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_DesignTipGenerator{

	public:
		C_DesignTipGenerator();
		~C_DesignTipGenerator();

	//-----------------------------------
	//----数据
	protected:
		QList<C_DesignTip> tip_list;	//灵感集合
	public:
								//数据 - 空判断
		bool isNull();
	public:
								//数据 - 获取章节标题
		void initData();

};
