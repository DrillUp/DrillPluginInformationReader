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
		
		说明：		> 【注意，属性按钮组，需要多套一层Widget，再addCellWidget。】
					  反复试验，cellWidget会被表格父类删掉，必须用嵌套隔离出来。
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
	this->initTable(ui.tableWidget_plugin);
	ui.widget_search->setVisible(false);

	// > 树按钮控件
	this->m_btnPartList = QList<P_PluginAttr_ButtonPart*>();
	for (int i = 0; i < 100; i++){
		P_PluginAttr_ButtonPart* btn_part = new P_PluginAttr_ButtonPart(this);
		btn_part->setVisible(false);
		this->m_btnPartList.append(btn_part);
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
	connect(ui.comboBox_pluginMode, &QComboBox::currentTextChanged, this, &P_PluginListPart::modeChanged);

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
	this->m_table->horizontalHeader()->resizeSection(0, 280);
	this->m_table->horizontalHeader()->resizeSection(1, 140);
	this->m_table->horizontalHeader()->resizeSection(2, 110);
	this->m_table->horizontalHeader()->resizeSection(3, 80);
	this->m_table->horizontalHeader()->resizeSection(4, 220);
	this->m_table->horizontalHeader()->resizeSection(5, 80);

	// > 事件绑定
	//connect(this->m_table, &QTreeWidget::itemDoubleClicked, this, &P_PluginListPart::treeDoubled);
	//connect(this->m_table, &QTreeWidget::customContextMenuRequested, this, &P_PluginListPart::treeRightClicked);


}

/*-------------------------------------------------
		树结构 - 下拉框变化
*/
void P_PluginListPart::modeChanged(QString text){

	// > 搜索显示
	if (ui.comboBox_pluginMode->currentIndex() == 0){
		ui.widget_search->setVisible(false);
	}
	if (ui.comboBox_pluginMode->currentIndex() == 1){
		ui.widget_search->setVisible(true);
	}
	
	// > 刷新树
	this->refreshTable();
}
/*-------------------------------------------------
		树结构 - 清理项
*/
void P_PluginListPart::clearTableItem(){

	// > 退按钮组（转移到别处）
	for (int i = 0; i < this->m_table->rowCount(); i++){
		QWidget* w = this->m_table->cellWidget(i,1);
		if (w == nullptr){ continue; }
		if (w->layout() == nullptr){ continue; }

		for (int j = 0; j < this->m_btnPartList.count(); j++){
			P_PluginAttr_ButtonPart* btn_part = this->m_btnPartList.at(j);
			w->layout()->removeWidget(btn_part);
		}
		this->m_table->removeCellWidget(i, 1);		//【必须夹个中间widget层，然后移除Widget】
	}
	for (int j = 0; j < this->m_btnPartList.count(); j++){
		P_PluginAttr_ButtonPart* btn_part = this->m_btnPartList.at(j);
		btn_part->setParent(this);
	}

	// > 清除树控件
	this->m_table->clearContents();
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
	if (this->m_table == nullptr){ return; }
	this->clearTableItem();

	// > 配置的插件
	QList<C_PluginData*> data_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	if (end_index >= data_list.count()){ end_index = data_list.count()-1; }
	this->m_table->setRowCount(end_index - start_index + 1);
	for (int i = start_index; i <= end_index; i++){
		C_PluginData* c_p = data_list.at(i);

		int index = i - start_index;
		this->setOneRow(index, c_p->name, this->getButtonPartByIndex(index));
	}

	// > 刷新分页器
	this->m_p_PageNavigator->setAllCount(data_list.count());
}

/*-------------------------------------------------
		树结构 - 刷新树（全部插件）
*/
void P_PluginListPart::refreshTable_allPlugin(int start_index, int end_index){
	if (this->m_table == nullptr){ return; }
	this->clearTableItem();

	// > 全部插件
	QList<C_ScriptAnnotation> data_list = S_InformationDataContainer::getInstance()->getAnnotationTank();
	if (end_index >= data_list.count()){ end_index = data_list.count() - 1; }
	this->m_table->setRowCount(end_index - start_index + 1);
	for (int i = start_index; i <= end_index; i++){
		C_ScriptAnnotation data = data_list.at(i);
		
		int index = i - start_index;
		this->setOneRow(index, data.getName(), this->getButtonPartByIndex(index));
	}

	// > 刷新分页器
	this->m_p_PageNavigator->setAllCount(data_list.count());
}
/*-------------------------------------------------
		私有 - 添加一行
*/
void P_PluginListPart::setOneRow(int row, QString pluginName, QWidget* widget){

	C_PluginData* c_p = S_PluginDataContainer::getInstance()->getPluginData(pluginName);
	C_ScriptAnnotation data = S_InformationDataContainer::getInstance()->getAnnotation(pluginName);
	QString search_text = ui.lineEdit_searchPlugin->text();

	// > 不标蓝情况
	if(  ui.comboBox_pluginMode->currentIndex() == 0 || 
		(ui.comboBox_pluginMode->currentIndex() == 1 && search_text.isEmpty())){

		this->m_table->setItem(row, 0, new QTableWidgetItem(pluginName));

		// > 分割线
		if (pluginName.contains("---")){
			this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc()));

		// > 插件行
		}else{
		
			// > 按钮组
			if (widget != nullptr){
				widget->setParent(this->m_table);
				widget->setVisible(true);
				this->m_table->setCellWidget(row, 1, TTool::_CreateQWidget_containsTarget_(widget, 0));		//【必须夹个中间widget层】
			}else{
				qDebug() << row;
				Q_ASSERT(false);
			}

			// > 文本
			QString version = data.getPlugindesc_version();
			if (version.isEmpty() == false){
				this->m_table->setItem(row, 2, new QTableWidgetItem(version));
				this->m_table->setItem(row, 3, new QTableWidgetItem(data.getPlugindesc_type()));
				this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc_name()));
			}else{
				this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc()));		//（读不到版本时，显示全名）
			}
			if (c_p == nullptr){
				this->m_table->setItem(row, 5, new QTableWidgetItem("未装载"));			//（配置中未找到的，标记 未装载）
			}else{
				this->m_table->setItem(row, 5, new QTableWidgetItem(c_p->status ? "ON" : "OFF"));
			}
		}
	
	// > 标蓝情况
	}else{

		this->m_table->setCellWidget(row, 0, this->getLabelWithSign(pluginName, search_text));

		// > 分割线
		if (pluginName.contains("---")){
			this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc()));

			// > 插件行
		}
		else{

			// > 按钮组
			if (widget != nullptr){
				widget->setParent(this->m_table);
				widget->setVisible(true);
				this->m_table->setCellWidget(row, 1, TTool::_CreateQWidget_containsTarget_(widget, 0));		//【必须夹个中间widget层】
			}
			else{
				qDebug() << row;
				Q_ASSERT(false);
			}

			// > 文本
			QString version = data.getPlugindesc_version();
			if (version.isEmpty() == false){
				this->m_table->setCellWidget(row, 2, this->getLabelWithSign(version, search_text));
				this->m_table->setCellWidget(row, 3, this->getLabelWithSign(data.getPlugindesc_type(), search_text));
				this->m_table->setCellWidget(row, 4, this->getLabelWithSign(data.getPlugindesc_name(), search_text));
			}else{
				this->m_table->setCellWidget(row, 4, this->getLabelWithSign(data.getPlugindesc(), search_text));
			}
			if (c_p == nullptr){
				this->m_table->setItem(row, 5, new QTableWidgetItem("未装载"));			//（配置中未找到的，标记 未装载）
			}else{
				this->m_table->setItem(row, 5, new QTableWidgetItem(c_p->status ? "ON" : "OFF"));
			}
		}
	}

}
/*-------------------------------------------------
		私有 - 将指定字符串标蓝
*/
QLabel* P_PluginListPart::getLabelWithSign(QString text, QString searching_text){
	if (text.contains(searching_text) == false){
		return new QLabel(text);
	}
	QStringList data_list = text.split(searching_text);
	QString result_text = "<p>";
	for (int i = 0; i < data_list.count(); i++){
		result_text.append(data_list.at(i));
		if (i < data_list.count()-1){
			result_text.append("<span style=\"background-color:#5fc2ff;\">");
			result_text.append(searching_text);
			result_text.append("</span>");
		}
	}
	result_text.append("<\p>");
	return new QLabel(result_text);
}

/*-------------------------------------------------
		按钮组 - 获取按钮组
*/
P_PluginAttr_ButtonPart* P_PluginListPart::getButtonPartByIndex(int index){
	if (index < 0){ return nullptr; }
	if (index >= this->m_btnPartList.count()){ return nullptr; }
	return this->m_btnPartList.at(index);
}


/*-------------------------------------------------
		树事件 - 双击树节点

void P_PluginListPart::treeDoubled(QTreeWidgetItem *item, int col){
	if (this->slot_block){ return; };
	this->slot_block = true;

	QList<C_PluginData*> datas = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < datas.count(); i++) {
		C_PluginData* c_p = datas.at(i);
		if (c_p->name == item->text(0) ) {
			//...
		}
	}

	this->slot_block = false;
}
*/
/*-------------------------------------------------
		树事件 - 右键树节点

void P_PluginListPart::treeRightClicked(QPoint p){
	if (this->slot_block){ return; };
	this->slot_block = true;

	if (this->m_tree->itemAt(p) == nullptr){ return; }
	QTreeWidgetItem* item = this->m_tree->itemAt(p);	//QPoint返回的是鼠标坐标值，treeWidget可以通过itemAt()获取到item。

	qDebug() << this->m_tree->indexAt(p);
	//...

	this->slot_block = false;
}
*/


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