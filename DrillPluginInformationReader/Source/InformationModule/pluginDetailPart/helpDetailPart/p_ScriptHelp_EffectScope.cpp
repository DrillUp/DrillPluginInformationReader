#include "stdafx.h"
#include "p_ScriptHelp_EffectScope.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		作用域 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_EffectScope::P_ScriptHelp_EffectScope(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----控件初始化
	this->setData(nullptr);		//（初始没有任何数据）

	//-----------------------------------
	//----事件绑定
	//（无）

}

P_ScriptHelp_EffectScope::~P_ScriptHelp_EffectScope(){
}


/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_EffectScope::setData(C_ScriptHelp_EffectScope* data){
	if (data == nullptr){
		ui.stackedWidget->setCurrentIndex(0);
		return;
	}

	// > 三种界面
	if (data->isEnableSenceBattle()){
		ui.toolButton_battle->setEnabled(true);
		ui.toolButton_battle->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Selected.png"));
	}else{
		ui.toolButton_battle->setEnabled(false);
		ui.toolButton_battle->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Error.png"));
	}
	if (data->isEnableSenceMap()){
		ui.toolButton_map->setEnabled(true);
		ui.toolButton_map->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Selected.png"));
	}else{
		ui.toolButton_map->setEnabled(false);
		ui.toolButton_map->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Error.png"));
	}
	if (data->isEnableSenceMenu()){
		ui.toolButton_menu->setEnabled(true);
		ui.toolButton_menu->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Selected.png"));
	}else{
		ui.toolButton_menu->setEnabled(false);
		ui.toolButton_menu->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Error.png"));
	}

	// > 其他界面
	//QStringList other_list = data->getOtherSence();
	//for (int i = 0; i < other_list.count(); i++){
	//	other_list.at(i);
	//}

	// > 作用域描述
	if (data->comments == ""){
		ui.label_context->setText("没有作用域描述。");
	}else{
		ui.label_context->setText(data->comments);
	}

	ui.stackedWidget->setCurrentIndex(1);
}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_EffectScope::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_EffectScope::putUiToData(){
	//（暂无）
}