#include "stdafx.h"
#include "p_CommandSearcherPart.h"

#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/ProjectModule/StorageGlobal/S_IniManager.h"
#include "Source/Utils/Common/TTool.h"

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

	// > 指令控件块
	for (int i = 0; i < 30; i++){
		P_ScriptHelp_CommandSearchCell* cell = new P_ScriptHelp_CommandSearchCell();
		if (i% 2 == 0){
			ui.verticalLayout_left->addWidget(cell);
		}else{
			ui.verticalLayout_right->addWidget(cell);
		}
		this->m_cellPartList.append(cell);
	}
	ui.verticalLayout_left->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
	ui.verticalLayout_right->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

	// > 历史查询控件
	this->m_p_historicalSearchRecord = new P_HistoricalSearchRecord(this);
	ui.horizontalLayout_searchType->removeItem(ui.horizontalSpacer);
	ui.horizontalLayout_searchType->addWidget(this->m_p_historicalSearchRecord);
	ui.horizontalLayout_searchType->addItem(ui.horizontalSpacer);
	ui.horizontalLayout_searchType->setStretch(ui.horizontalLayout_searchType->count()-1, 1);

	// > 分页控件
	this->m_p_PageNavigator = new P_PageNavigator();
	this->m_p_PageNavigator->initNavigator(30, 30, 5);
	ui.verticalLayout_PageNavigator->addWidget(this->m_p_PageNavigator);


	//-----------------------------------
	//----事件绑定

	// > 执行搜索时
	connect(ui.pushButton_search, &QPushButton::clicked, this, &P_CommandSearcherPart::btn_search);
	connect(this->m_p_historicalSearchRecord, &P_HistoricalSearchRecord::textClicked, this, &P_CommandSearcherPart::searchTextClicked);

	// > 分页变化时
	connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &P_CommandSearcherPart::refreshCellAuto);

}

P_CommandSearcherPart::~P_CommandSearcherPart(){
}


/*-------------------------------------------------
		搜索指令 - 搜索
*/
void P_CommandSearcherPart::btn_search(){

	this->m_searchText = ui.lineEdit_search->text();
	this->m_allSearchedData = S_InformationDataContainer::getInstance()->getAnnotationTank();
	this->m_p_historicalSearchRecord->addText(m_searchText);

	// > 搜索类型
	QString commandType = ui.comboBox_commandType->currentText();

	// > 全部插件
	QList<C_ScriptAnnotation> data_list = QList<C_ScriptAnnotation>();
	for (int i = 0; i < this->m_allSearchedData.count(); i++){
		C_ScriptAnnotation data = this->m_allSearchedData.at(i);
		C_ScriptHelpDetail* detail = data.getScriptHelpDetail();
		if (detail == nullptr){ continue; }
		C_ScriptHelp_Command* command = detail->getCommand();
		if (command == nullptr){ continue; }

		// > 筛选条件
		if (commandType == "全部类型" && command->hasCommandKeyWord_All(m_searchText)){ data_list.append(data); }
		if (commandType == "插件指令" && command->hasCommandKeyWord_PluginCommand(m_searchText)){ data_list.append(data); }
		if (commandType == "事件注释" && command->hasCommandKeyWord_EventComment(m_searchText)){ data_list.append(data); }
		if (commandType == "地图备注" && command->hasCommandKeyWord_MapNote(m_searchText)){ data_list.append(data); }
		if (commandType == "角色注释" && command->hasCommandKeyWord_ActorNote(m_searchText)){ data_list.append(data); }
		if (commandType == "敌人注释" && command->hasCommandKeyWord_EnemyNote(m_searchText)){ data_list.append(data); }
		if (commandType == "状态注释" && command->hasCommandKeyWord_StateNote(m_searchText)){ data_list.append(data); }
		if (commandType == "物品/武器/护甲注释" && command->hasCommandKeyWord_ItemNote(m_searchText)){ data_list.append(data); }
		if (commandType == "技能注释" && command->hasCommandKeyWord_SkillNote(m_searchText)){ data_list.append(data); }
		if (commandType == "移动路线指令" && command->hasCommandKeyWord_MoveRoute(m_searchText)){ data_list.append(data); }
		if (commandType == "窗口字符" && command->hasCommandKeyWord_WindowChar(m_searchText)){ data_list.append(data); }
	}
	this->m_allSearchedData = data_list;	//（修改数据范围）

	// > 刷新分页器
	this->m_p_PageNavigator->setAllCount(this->m_allSearchedData.count());	
	
	this->refreshCellAuto(0, 29);
}

/*-------------------------------------------------
		搜索指令 - 刷新控件
*/
void P_CommandSearcherPart::refreshCellAuto(int start_index, int end_index){
	if (start_index < 0){ start_index = 0; }
	if (end_index <= 0){ return; }

	// > 搜索类型
	QString commandType = ui.comboBox_commandType->currentText();

	// > 显示的插件
	if (end_index >= this->m_allSearchedData.count()){ end_index = this->m_allSearchedData.count() - 1; }
	for (int i = start_index; i <= end_index; i++){
		C_ScriptAnnotation data = this->m_allSearchedData.at(i);
		C_ScriptHelpDetail* c_detail = data.getScriptHelpDetail();
		if (c_detail == nullptr){ continue; }

		int index = i - start_index;
		P_ScriptHelp_CommandSearchCell* cell_part = this->getButtonPartByIndex(index);
		if (cell_part == nullptr){ continue; }
		cell_part->setData(c_detail->getCommand(), data.getName(), data.getPlugindesc(), this->m_searchText, commandType);
	}

	// > 剩余的清空
	for (int i = end_index + 1; i < this->m_cellPartList.count(); i++){
		P_ScriptHelp_CommandSearchCell* cell_part = this->getButtonPartByIndex(i);
		if (cell_part != nullptr){
			cell_part->clearAllChild();
		};
	}
}

/*-------------------------------------------------
		属性 - 获取按钮组
*/
P_ScriptHelp_CommandSearchCell* P_CommandSearcherPart::getButtonPartByIndex(int index){
	if (index < 0){ return nullptr; }
	if (index >= this->m_cellPartList.count()){ return nullptr; }
	return this->m_cellPartList.at(index);
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