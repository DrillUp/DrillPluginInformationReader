#pragma once
#include <QList>
#include "private/c_DesignTip_Cell.h"

/*
-----==========================================================-----
		类：		灵感生成器-插件灵感集合 数据类.h
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
		QList<C_DesignTip_Cell> tip_list;	//插件灵感集合
	public:
								//数据 - 集合初始化
		void initData();
	public:
								//数据 - 获取单条
		C_DesignTip_Cell getCellByIndex(int index);
								//数据 - 获取数量
		int count();
								//数据 - 判断是否已含某内容（防止多个插件的设计内容重复）
		bool hasContext(QString context);
								//数据 - 空判断
		bool isNull();

};
