#include "stdafx.h"
#include "p_ScriptHelp_CommandSearchCell.h"

#include "drillplugininformationreader.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		指令 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块
		说明：		显示控件 指令 信息的结构。
					【注意，由于需要反复查询，那么就一定不要用临时new的控件，必须用现成的控件填内容】
-----==========================================================-----
*/
P_ScriptHelp_CommandSearchCell::P_ScriptHelp_CommandSearchCell(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----控件初始化
	this->clearAllChild();
}

P_ScriptHelp_CommandSearchCell::~P_ScriptHelp_CommandSearchCell(){
}

/*-------------------------------------------------
		控件 - 清空全部内容（不删除控件）
*/
void P_ScriptHelp_CommandSearchCell::clearAllChild(){

	// > 断开连接
	

}
/*-------------------------------------------------
		控件 - 链接被点击
*/
void P_ScriptHelp_CommandSearchCell::linkClicked_plugin(QString data){
	DrillPluginInformationReader::getInstance()->showPluginDetail(data);
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_CommandSearchCell::setData(C_ScriptHelp_Command* data, QString plugin_name){
	this->clearAllChild();
	if (data == nullptr){ return; }
	if (data->isNull()){ return; }
	if (plugin_name.isEmpty()){ return; }


}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_CommandSearchCell::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_CommandSearchCell::putUiToData(){
	//（暂无）
}