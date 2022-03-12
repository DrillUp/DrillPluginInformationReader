#include "stdafx.h"
#include "p_DesignTip_Cell.h"

#include "drillplugininformationreader.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		灵感生成器-单条 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块
		说明：		显示控件 灵感生成器-单条 信息的结构。
-----==========================================================-----
*/
P_DesignTip_Cell::P_DesignTip_Cell(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定
	connect(ui.label_pluginName_A, &QLabel::linkActivated, this, &P_DesignTip_Cell::linkClicked_plugin);

	//-----------------------------------
	//----控件初始化
}

P_DesignTip_Cell::~P_DesignTip_Cell(){
}

/*-------------------------------------------------
		控件 - 链接被点击
*/
void P_DesignTip_Cell::linkClicked_plugin(QString data){
	DrillPluginInformationReader::getInstance()->showPluginDetail(data);
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_DesignTip_Cell::setData(C_DesignTip_Cell data){

	// > 所属插件 标签文本
	QString plugin_text = "<p>所属插件：<a href=\"";
	plugin_text.append(data.plugin_name);
	plugin_text.append("\"><span style=\"text-decoration: underline; color:#0000ff; \">");
	plugin_text.append(data.plugin_name);
	plugin_text.append("</span></a>");
	plugin_text.append(" ");
	plugin_text.append(data.plugin_desc);
	plugin_text.append("。< / p>");
	ui.label_pluginName_A->setText(plugin_text);

	// > 内容
	ui.label_context_A->setText(data.context);
}

/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_DesignTip_Cell::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_DesignTip_Cell::putUiToData(){
	//（暂无）
}