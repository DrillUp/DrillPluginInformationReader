#include "stdafx.h"
#include "p_PluginAttr_ButtonPart.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件属性 按钮块.cpp
		作者：		drill_up
		所属模块：	信息模块

		说明：		插件属性显示用的按钮块。
-----==========================================================-----
*/
P_PluginAttr_ButtonPart::P_PluginAttr_ButtonPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	this->m_w_PluginAttr_Docs = nullptr;
	this->m_w_PluginAttr_Src = nullptr;
	this->m_w_PluginAttr_HighConsumption = nullptr;
	this->m_w_PluginAttr_HasTool = nullptr;
	this->m_w_PluginAttr_ForeignKey = nullptr;

	//-----------------------------------
	//----初始化ui
	ui.toolButton_src->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_src.png"));
	ui.toolButton_word->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_word.png"));
	ui.toolButton_highConsumption->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_highConsumption.png"));
	ui.toolButton_hasTool->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_hasTool.png"));
	ui.toolButton_foreignKey->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_foreignKey.png"));

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_word, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_docs);
	connect(ui.toolButton_src, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_src);
	connect(ui.toolButton_highConsumption, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_highConsumption);
	connect(ui.toolButton_hasTool, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_hasTool);
	connect(ui.toolButton_foreignKey, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_foreignKey);

}

P_PluginAttr_ButtonPart::~P_PluginAttr_ButtonPart(){
}


/*-------------------------------------------------
		控件 - 隐藏全部
*/
void P_PluginAttr_ButtonPart::hideAll(){
	ui.toolButton_src->hide();
	ui.toolButton_word->hide();
	ui.toolButton_highConsumption->hide();
	ui.toolButton_hasTool->hide();
	ui.toolButton_foreignKey->hide();
}

/*-------------------------------------------------
		控件 - 设置当前插件名
*/
void P_PluginAttr_ButtonPart::setPluginName(QString pluginName){
	this->m_pluginName = pluginName;
	this->refreshBtnVisible();
}
/*-------------------------------------------------
		控件 - 获取当前插件名
*/
QString P_PluginAttr_ButtonPart::getPluginName(){
	return this->m_pluginName;
}
/*-------------------------------------------------
		控件 - 根据属性显示按钮
*/
void P_PluginAttr_ButtonPart::refreshBtnVisible(){
	this->hideAll();
	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(this->m_pluginName);
	if (detail == nullptr){ return; }

	// > 资源路径
	ui.toolButton_src->setVisible(detail->getSrc() != nullptr);

	// > 插件文档（此数据类一开始就创建了）
	ui.toolButton_word->setVisible(detail->getDocs()->hasAnyDocx());

	// > 高消耗
	C_ScriptHelp_Performance* performance = detail->getPerformance();
	if (performance != nullptr &&
		performance->isHighCost()){
		ui.toolButton_highConsumption->setVisible(true);
	}
	
	// > 小工具支持
	//...

	// > 外键
	//...

}
/*-------------------------------------------------
		控件 - 资源按钮
*/
void P_PluginAttr_ButtonPart::setWindowDocs(W_PluginAttr_Docs* w){
	this->m_w_PluginAttr_Docs = w;
}
void P_PluginAttr_ButtonPart::setWindowSrc(W_PluginAttr_Src* w){
	this->m_w_PluginAttr_Src = w;
}
void P_PluginAttr_ButtonPart::setWindowHighConsumption(W_PluginAttr_HighConsumption* w){
	this->m_w_PluginAttr_HighConsumption = w;
}
void P_PluginAttr_ButtonPart::setWindowHasTool(W_PluginAttr_HasTool* w){
	this->m_w_PluginAttr_HasTool = w;
}
void P_PluginAttr_ButtonPart::setWindowForeignKey(W_PluginAttr_ForeignKey* w){
	this->m_w_PluginAttr_ForeignKey = w;
}

/*-------------------------------------------------
		控件 - 资源按钮
*/
void P_PluginAttr_ButtonPart::btn_docs(){
	if (this->m_w_PluginAttr_Docs == nullptr){ return; }
	this->m_w_PluginAttr_Docs->showInformation_word(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_Docs);
}
void P_PluginAttr_ButtonPart::btn_src(){
	if (this->m_w_PluginAttr_Src == nullptr){ return; }
	this->m_w_PluginAttr_Src->showInformation_src(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_Src);
}
void P_PluginAttr_ButtonPart::btn_highConsumption(){
	if (this->m_w_PluginAttr_HighConsumption == nullptr){ return; }
	//this->m_w_PluginAttr_HighConsumption->showInformation_highConsumption(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_HighConsumption);
}
void P_PluginAttr_ButtonPart::btn_hasTool(){
	if (this->m_w_PluginAttr_HasTool == nullptr){ return; }
	//this->m_w_PluginAttr_HasTool->showInformation_hasTool(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_HasTool);
}
void P_PluginAttr_ButtonPart::btn_foreignKey(){
	if (this->m_w_PluginAttr_ForeignKey == nullptr){ return; }
	//this->m_w_PluginAttr_ForeignKey->showInformation_foreignKey(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_ForeignKey);
}
/*-------------------------------------------------
		控件 - 显示单一窗口
*/
void P_PluginAttr_ButtonPart::showWindowAlone(QDialog* w){
	if (this->m_w_PluginAttr_Docs == nullptr){ return; }
	if (this->m_w_PluginAttr_Src == nullptr){ return; }
	if (this->m_w_PluginAttr_HighConsumption == nullptr){ return; }
	if (this->m_w_PluginAttr_HasTool == nullptr){ return; }
	if (this->m_w_PluginAttr_ForeignKey == nullptr){ return; }
	
	if (this->m_w_PluginAttr_Docs == w){
		this->m_w_PluginAttr_Docs->show();
	}else{
		this->m_w_PluginAttr_Docs->close();
	}
	if (this->m_w_PluginAttr_Src == w){
		this->m_w_PluginAttr_Src->show();
	}else{
		this->m_w_PluginAttr_Src->close();
	}
	if (this->m_w_PluginAttr_HighConsumption == w){
		this->m_w_PluginAttr_HighConsumption->show();
	}else{
		this->m_w_PluginAttr_HighConsumption->close();
	}
	if (this->m_w_PluginAttr_HasTool == w){
		this->m_w_PluginAttr_HasTool->show();
	}else{
		this->m_w_PluginAttr_HasTool->close();
	}
	if (this->m_w_PluginAttr_ForeignKey == w ){
		this->m_w_PluginAttr_ForeignKey->show();
	}else{
		this->m_w_PluginAttr_ForeignKey->close();
	}
}


/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_PluginAttr_ButtonPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_PluginAttr_ButtonPart::putUiToData(){
	//（暂无）
}