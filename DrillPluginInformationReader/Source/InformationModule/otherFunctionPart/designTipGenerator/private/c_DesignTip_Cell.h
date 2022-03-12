#pragma once
#include <QString>

/*
-----==========================================================-----
		类：		灵感生成器-单条 数据类.h
		所属模块：	信息模块
		功能：		灵感生成器的单条插件数据。与单条控件对应。
					【注意，插件中如果有多条设计说明，那么会有多个单条】
					（详细见.cpp）
-----==========================================================-----
*/
class C_DesignTip_Cell{

	public:
		C_DesignTip_Cell();
		~C_DesignTip_Cell();

	//-----------------------------------
	//----数据
	public:
		QString plugin_name;		//所属插件（英文名）
		QString plugin_desc;		//所属插件（中文名）
		QString context;			//单条内容
	public:
									//数据 - 空判断
		bool isNull();
};
