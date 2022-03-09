#include "stdafx.h"
#include "c_DesignTipGenerator.h"

/*
-----==========================================================-----
		类：		灵感生成器-插件 数据类.cpp
		所属模块：	插件模块
		功能：		灵感生成器的插件数据。
-----==========================================================-----
*/
C_DesignTip::C_DesignTip(){
	this->plugin_name = "";
	this->plugin_desc = "";
	this->page = C_ScriptHelp_SubsectionPage();
}
C_DesignTip::~C_DesignTip(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_DesignTip::isNull(){
	return this->plugin_name == "" || this->page.isNull() == 0;
}


/*
-----==========================================================-----
		类：		灵感生成器-插件集合 数据类.cpp
		所属模块：	插件模块
		功能：		灵感生成器中用到的数据。
-----==========================================================-----
*/
C_DesignTipGenerator::C_DesignTipGenerator(){
	this->tip_list = QList<C_DesignTip>();
}
C_DesignTipGenerator::~C_DesignTipGenerator(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_DesignTipGenerator::isNull(){
	return this->tip_list.count() == 0;
}