#include "stdafx.h"
#include "c_DesignTip_Cell.h"

/*
-----==========================================================-----
		类：		灵感生成器-单条 数据类.cpp
		所属模块：	信息模块
		功能：		灵感生成器的单条插件数据。与单条控件对应。
					【注意，插件中如果有多条设计说明，那么会有多个单条】

		说明：		此数据类单独存储，从 已读取的所有插件帮助信息 中进行取材。
-----==========================================================-----
*/
C_DesignTip_Cell::C_DesignTip_Cell(){
	this->plugin_name = "";
	this->plugin_desc = "";
	this->context = "";
}
C_DesignTip_Cell::~C_DesignTip_Cell(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_DesignTip_Cell::isNull(){
	return this->plugin_name == "" || this->context == "";
}

