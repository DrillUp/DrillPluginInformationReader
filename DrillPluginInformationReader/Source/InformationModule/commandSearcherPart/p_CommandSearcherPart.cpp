#include "stdafx.h"
#include "p_CommandSearcherPart.h"

#include "Source/ProjectModule/storageGlobal/s_IniManager.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		指令搜索器 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					
-----==========================================================-----
*/
P_CommandSearcherPart::P_CommandSearcherPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----控件初始化
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_commandType, 30);

	// > 历史查询控件
	this->m_p_historicalSearchRecord = new P_HistoricalSearchRecord(this);
	ui.horizontalLayout_searchType->removeItem(ui.horizontalSpacer);
	ui.horizontalLayout_searchType->addWidget(this->m_p_historicalSearchRecord);
	ui.horizontalLayout_searchType->addItem(ui.horizontalSpacer);

	// > 分页控件
	this->m_p_PageNavigator = new P_PageNavigator();
	this->m_p_PageNavigator->initNavigator(100, 100, 5);
	ui.verticalLayout_PageNavigator->addWidget(this->m_p_PageNavigator);


	//-----------------------------------
	//----事件绑定

	// > 执行搜索时
	connect(this->m_p_historicalSearchRecord, &P_HistoricalSearchRecord::textClicked, this, &P_CommandSearcherPart::searchTextClicked);

	// > 分页变化时
	//connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &P_CommandSearcherPart::refreshTableAuto);


}

P_CommandSearcherPart::~P_CommandSearcherPart(){
}


/*-------------------------------------------------
		控件 - 搜索的字符串被点击
*/
void P_CommandSearcherPart::searchTextClicked(QString text){
	ui.lineEdit_search->setText(text);
}

/*-------------------------------------------------
		块 - 用户自定义UI读取
*/
void P_CommandSearcherPart::ui_loadConfig(){

	QString search_str = S_IniManager::getInstance()->getConfig("PIR_CommandSearcher_search");
	this->m_p_historicalSearchRecord->setData(search_str.split("|||"));
}
/*-------------------------------------------------
		块 - 用户自定义UI存储
*/
void P_CommandSearcherPart::ui_saveConfig(){

	QStringList search_list = this->m_p_historicalSearchRecord->getData();
	S_IniManager::getInstance()->setConfig("PIR_CommandSearcher_search", search_list.join("|||"));
}