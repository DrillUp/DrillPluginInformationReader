#include "stdafx.h"
#include "p_PluginListPart.h"

#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		插件列表 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					
-----==========================================================-----
*/
P_PluginListPart::P_PluginListPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----控件初始化
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_pluginMode, 30);
	this->initTable(ui.treeWidget_plugin);
	ui.widget->setVisible(false);

	// > 树按钮控件
	this->m_treeBtnList = QList<P_PluginAttr_ButtonPart*>();
	for (int i = 0; i < 100; i++){
		P_PluginAttr_ButtonPart* btn_part = new P_PluginAttr_ButtonPart(this);
		btn_part->setVisible(false);
		this->m_treeBtnList.append(btn_part);
	}

	// > 分页控件
	this->m_p_PageNavigator = new P_PageNavigator();
	this->m_p_PageNavigator->initNavigator(100, 100, 5);
	ui.verticalLayout->addWidget(this->m_p_PageNavigator);

	//-----------------------------------
	//----事件绑定

	// > 数据全变时，重刷树
	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, this, &P_PluginListPart::refreshTable);

	// > 数据全变时，重刷交互中的注释数据
	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, S_InformationDataContainer::getInstance(), &S_InformationDataContainer::loadAllAnnotationData);

	// > 下拉框变化时，刷新
	connect(ui.comboBox_pluginMode, &QComboBox::currentTextChanged, this, &P_PluginListPart::treeModeChanged);

	// > 分页变化时
	connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &P_PluginListPart::refreshTableAuto);

}
P_PluginListPart::~P_PluginListPart(){
}


/*-------------------------------------------------
		树结构 - 初始化
*/
void P_PluginListPart::initTable(QTableWidget* table){
	this->m_table = table;

	// > ui初始化
	this->m_table->horizontalHeader()->resizeSection(0, 260);
	this->m_table->horizontalHeader()->resizeSection(1, 120);
	this->m_table->horizontalHeader()->resizeSection(2, 100);
	this->m_table->horizontalHeader()->resizeSection(3, 70);
	this->m_table->horizontalHeader()->resizeSection(4, 200);
	this->m_table->horizontalHeader()->resizeSection(5, 70);

	// > 事件绑定
	connect(this->m_table, &QTreeWidget::itemDoubleClicked, this, &P_PluginListPart::treeDoubled);
	connect(this->m_table, &QTreeWidget::customContextMenuRequested, this, &P_PluginListPart::treeRightClicked);


}

/*-------------------------------------------------
		树结构 - 下拉框变化
*/
void P_PluginListPart::treeModeChanged(QString text){

	// > 搜索显示
	if (ui.comboBox_pluginMode->currentIndex() == 0){
		ui.widget->setVisible(false);
	}
	if (ui.comboBox_pluginMode->currentIndex() == 1){
		ui.widget->setVisible(true);
	}
	
	// > 刷新树
	this->refreshTable();
}
/*-------------------------------------------------
		树结构 - 清理项
*/
void P_PluginListPart::clearTreeItem(){

	// > 退按钮组
	if (this->m_tree->columnCount() >= 2){
		for (int i = this->m_treeItemList.count() - 1; i >= 0; i--){
			QTreeWidgetItem* item = this->m_treeItemList.at(i);
			QWidget* widget = this->m_tree->itemWidget(item, 1);
			if (widget != nullptr){
				widget->setVisible(false);
				this->m_tree->setItemWidget(item, 1, nullptr);
			}
		}
	}

	// > 清除树控件
	this->m_treeItemList.clear();
	this->m_tree->clear();
}

/*-------------------------------------------------
		树结构 - 刷新树（自动）
*/
void P_PluginListPart::refreshTable(){
	this->refreshTableAuto(0, 99);
}
void P_PluginListPart::refreshTableAuto(int start_index, int end_index){
	if (ui.comboBox_pluginMode->currentIndex() == 0){
		this->refreshTable_configedPlugin(start_index, end_index);
	}
	if (ui.comboBox_pluginMode->currentIndex() == 1){
		this->refreshTable_allPlugin(start_index, end_index);
	}
}
/*-------------------------------------------------
		树结构 - 刷新树（配置的插件）
*/
void P_PluginListPart::refreshTable_configedPlugin(int start_index, int end_index){
	if (this->m_tree == nullptr){ return; }
	this->clearTreeItem();

	// > 配置的插件
	QList<C_PluginData*> data_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = start_index; i < end_index; i++){
		if (i >= data_list.count()){ return; }
		C_PluginData* c_p = data_list.at(i);

		int index = i - start_index;
		this->addOneRow(c_p->name, this->getButtonPartByIndex(index));
	}

	// > 刷新分页器
	this->m_p_PageNavigator->setAllCount(data_list.count());
}

/*-------------------------------------------------
		树结构 - 刷新树（全部插件）
*/
void P_PluginListPart::refreshTable_allPlugin(int start_index, int end_index){
	if (this->m_tree == nullptr){ return; }
	this->clearTreeItem();

	// > 全部插件
	QList<C_ScriptAnnotation> data_list = S_InformationDataContainer::getInstance()->getAnnotationTank();
	for (int i = start_index; i < end_index; i++){
		if (i >= data_list.count()){ return; }
		C_ScriptAnnotation data = data_list.at(i);
		
		int index = i - start_index;
		this->addOneRow(data.getName(), this->getButtonPartByIndex(index));
	}

	// > 刷新分页器
	this->m_p_PageNavigator->setAllCount(data_list.count());
}
/*-------------------------------------------------
		私有 - 添加一行
*/
void P_PluginListPart::addOneRow(QString pluginName, QWidget* widget){
	QTreeWidgetItem* new_item = new QTreeWidgetItem(this->m_tree);
	this->m_tree->addTopLevelItem(new_item);
	this->m_treeItemList.append(new_item);
	new_item->setText(0, pluginName);

	C_PluginData* c_p = S_PluginDataContainer::getInstance()->getPluginData(pluginName);
	C_ScriptAnnotation data = S_InformationDataContainer::getInstance()->getAnnotation(pluginName);

	// > 分割线
	if (pluginName.contains("---")){
		new_item->setText(4, data.getPlugindesc());

	// > 插件行
	}else{
		
		// > 按钮组
		if (widget != nullptr){
			this->m_tree->setItemWidget(new_item, 1, widget);
			widget->setVisible(true);
		}

		// > 文本
		QString version = data.getPlugindesc_version();
		if (version.isEmpty() == false){
			new_item->setText(2, version);
			new_item->setText(3, data.getPlugindesc_type());
			new_item->setText(4, data.getPlugindesc_name());
		}else{
			new_item->setText(4, data.getPlugindesc());		//（读不到版本时，显示全名）
		}
		if (c_p == nullptr){
			new_item->setText(5, "未装载");		//（配置中未找到的，标记 未装载）
		}else{
			new_item->setText(5, c_p->status ? "ON" : "OFF");
		}
	}
}

/*-------------------------------------------------
		按钮组 - 获取按钮组
*/
P_PluginAttr_ButtonPart* P_PluginListPart::getButtonPartByIndex(int index){
	if (index < 0){ return nullptr; }
	if (index >= this->m_treeBtnList.count()){ return nullptr; }
	return this->m_treeBtnList.at(index);
}


/*-------------------------------------------------
		树事件 - 双击树节点
*/
void P_PluginListPart::treeDoubled(QTreeWidgetItem *item, int col){
	if (this->slot_block){ return; };
	this->slot_block = true;

	/* --------------编辑插件--------------*/
	QList<C_PluginData*> datas = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < datas.count(); i++) {
		C_PluginData* c_p = datas.at(i);
		if (c_p->name == item->text(0) ) {
			//...
		}
	}

	this->slot_block = false;
}
/*-------------------------------------------------
		树事件 - 右键树节点
*/
void P_PluginListPart::treeRightClicked(QPoint p){
	if (this->slot_block){ return; };
	this->slot_block = true;

	if (this->m_tree->itemAt(p) == nullptr){ return; }
	QTreeWidgetItem* item = this->m_tree->itemAt(p);	//QPoint返回的是鼠标坐标值，treeWidget可以通过itemAt()获取到item。

	qDebug() << this->m_tree->indexAt(p);
	//...

	this->slot_block = false;
}


/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_PluginListPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_PluginListPart::putUiToData(){
	//（暂无）
}