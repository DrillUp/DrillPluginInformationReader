#include "stdafx.h"
#include "p_OtherFunctionPart.h"

#include "Source/InformationModule/otherFunctionPart/pluginBatchDelete/w_PluginBatchDeletePart.h"
#include "Source/InformationModule/otherFunctionPart/pluginBatchUpdate/w_PluginBatchUpdatePart.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		其它功能 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	其它功能的编辑块结构。
					
-----==========================================================-----
*/
P_OtherFunctionPart::P_OtherFunctionPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----控件初始化
	ui.groupBox_2->setVisible(false);	//（隐藏待填坑）

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_showDesignTip, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_DesignTipGenerator);
	connect(ui.toolButton_showDeletePart, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_PluginBatchDelete);
	connect(ui.toolButton_showUpdatePart, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_PluginBatchUpdate);

}

P_OtherFunctionPart::~P_OtherFunctionPart(){
}


/*-------------------------------------------------
		控件 - 选择 灵感生成器
*/
void P_OtherFunctionPart::btn_DesignTipGenerator(){
	emit selected_DesignTipGenerator();
}
/*-------------------------------------------------
		控件 - 选择 清理未使用的插件
*/
void P_OtherFunctionPart::btn_PluginBatchDelete(){
	W_PluginBatchDeletePart d(this);
	d.exec();
}
/*-------------------------------------------------
		控件 - 选择 插件更新器
*/
void P_OtherFunctionPart::btn_PluginBatchUpdate(){
	W_PluginBatchUpdatePart d(this);
	d.exec();
}

/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_OtherFunctionPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_OtherFunctionPart::putUiToData(){
	//（暂无）
}