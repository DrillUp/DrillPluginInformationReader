#include "stdafx.h"
#include "p_PluginListPart.h"

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
	ui.widget_search->setVisible(false);
	this->slot_block = false;
	this->initTable(ui.tableWidget_plugin);

	// > 表格按钮控件
	this->m_w_PluginAttrComment = new W_PluginAttrComment(this);
	this->m_btnPartList = QList<P_PluginAttr_ButtonPart*>();
	for (int i = 0; i < 100; i++){
		P_PluginAttr_ButtonPart* btn_part = new P_PluginAttr_ButtonPart(this->m_w_PluginAttrComment, this);
		btn_part->setVisible(false);
		this->m_btnPartList.append(btn_part);
	}

	// > 分页控件
	this->m_p_PageNavigator = new P_PageNavigator();
	this->m_p_PageNavigator->initNavigator(100, 100, 5);
	ui.verticalLayout->addWidget(this->m_p_PageNavigator);

	//-----------------------------------
	//----事件绑定

	// > 下拉框变化时，刷新
	connect(ui.comboBox_pluginMode, &QComboBox::currentTextChanged, this, &P_PluginListPart::modeChanged);
	connect(ui.pushButton_searchPlugin, &QPushButton::clicked, this, &P_PluginListPart::btn_search);

	// > 分页变化时
	connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &P_PluginListPart::refreshTableAuto);

}
P_PluginListPart::~P_PluginListPart(){
}


/*-------------------------------------------------
		数据 - 下拉框变化
*/
void P_PluginListPart::modeChanged(QString text){

	// > 搜索显示
	if (ui.comboBox_pluginMode->currentIndex() == 0){
		ui.widget_search->setVisible(false);
	}
	if (ui.comboBox_pluginMode->currentIndex() == 1){
		ui.widget_search->setVisible(true);
	}
	
	// > 刷新表格
	this->rebuildTable();
}
/*-------------------------------------------------
		数据 - 搜索插件
*/
void P_PluginListPart::btn_search(){

	this->m_searchText = ui.lineEdit_searchPlugin->text();
	this->m_allAnnotationData = S_InformationDataContainer::getInstance()->getAnnotationTank();

	// > 全部插件
	QList<C_ScriptAnnotation> data_list = QList<C_ScriptAnnotation>();
	if (this->m_searchText == ""){
		data_list = this->m_allAnnotationData;
	}else{
		for (int i = 0; i < this->m_allAnnotationData.count(); i++){
			C_ScriptAnnotation data = this->m_allAnnotationData.at(i);

			// > 筛选条件
			if (data.getName().contains(this->m_searchText)){ data_list.append(data); continue; }
			if (data.getPlugindesc_version().contains(this->m_searchText)){ data_list.append(data); continue; }
			if (data.getPlugindesc_name().contains(this->m_searchText)){ data_list.append(data); continue; }
			if (data.getPlugindesc_type().contains(this->m_searchText)){ data_list.append(data); continue; }
			if (data.getPlugindesc().contains(this->m_searchText)){ data_list.append(data); continue; }
		}
	}
	this->m_allAnnotationData = data_list;	//（修改数据范围）
	this->refreshTableAuto(0, 99);
}

/*-------------------------------------------------
		表格 - 初始化
*/
void P_PluginListPart::initTable(QTableWidget* table){
	this->m_table = table;

	// > ui初始化
	this->refreshHorizontalSize(0);
	//this->m_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);		//行自适应
	//（不要自适应，影响性能，且QLabel无法自动换行）

	// > 事件绑定
	connect(this->m_table, &QTableWidget::itemDoubleClicked, this, &P_PluginListPart::tableDoubled);
	connect(this->m_table, &QTableWidget::customContextMenuRequested, this, &P_PluginListPart::tableRightClicked);
	
}
/*-------------------------------------------------
		表格 - 刷新横向宽度
*/
void P_PluginListPart::refreshHorizontalSize(int table_width){
	int ww = table_width;
	if (ww < 950){
		this->m_table->horizontalHeader()->resizeSection(0, 280);
		this->m_table->horizontalHeader()->resizeSection(1, 140);
		this->m_table->horizontalHeader()->resizeSection(2, 110);
		this->m_table->horizontalHeader()->resizeSection(3, 80);
		this->m_table->horizontalHeader()->resizeSection(4, 220);
		this->m_table->horizontalHeader()->resizeSection(5, 80);
	}else{
		ww = ww - 40 - 270;
		this->m_table->horizontalHeader()->resizeSection(0, ww * 280 / 640);
		this->m_table->horizontalHeader()->resizeSection(1, ww * 140 / 640);
		this->m_table->horizontalHeader()->resizeSection(2, 110);
		this->m_table->horizontalHeader()->resizeSection(3, 80);
		this->m_table->horizontalHeader()->resizeSection(4, ww * 220 / 640);
		this->m_table->horizontalHeader()->resizeSection(5, 80);
	}
}
/*-------------------------------------------------
		表格结构 - 清理项
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

	// > 清除表格控件
	this->m_table->clearContents();
}

/*-------------------------------------------------
		表格结构 - 重刷表格（读取时）
*/
void P_PluginListPart::rebuildTable(){
	
	// > 数据重刷
	ui.lineEdit_searchPlugin->setText("");
	this->m_searchText = "";
	this->m_allPluginData = S_PluginDataContainer::getInstance()->getPluginDataTank();
	this->m_allAnnotationData = S_InformationDataContainer::getInstance()->getAnnotationTank();

	// > 刷新
	this->refreshTableAuto(0, 99);
}
/*-------------------------------------------------
		表格结构 - 刷新表格（自动）
*/
void P_PluginListPart::refreshTableAuto(int start_index, int end_index){
	if (ui.comboBox_pluginMode->currentIndex() == 0){
		this->m_p_PageNavigator->setAllCount(this->m_allPluginData.count());	//（刷新分页器）
		this->refreshTable_configedPlugin(start_index, end_index);				//（刷新表格内容）
	}
	if (ui.comboBox_pluginMode->currentIndex() == 1){
		this->m_p_PageNavigator->setAllCount(this->m_allAnnotationData.count());	//（刷新分页器）
		this->refreshTable_allPlugin(start_index, end_index);						//（刷新表格内容）
	}
}
/*-------------------------------------------------
		表格结构 - 刷新表格（配置的插件）
*/
void P_PluginListPart::refreshTable_configedPlugin(int start_index, int end_index){
	if (this->m_table == nullptr){ return; }
	this->clearTableItem();
	if (start_index < 0){ start_index = 0; }
	if (end_index <= 0){ return; }

	// > 配置的插件
	if (end_index >= this->m_allPluginData.count()){ end_index = this->m_allPluginData.count() - 1; }
	this->m_table->setRowCount(end_index - start_index + 1);
	for (int i = start_index; i <= end_index; i++){
		C_PluginData* c_p = this->m_allPluginData.at(i);

		int index = i - start_index;
		P_PluginAttr_ButtonPart* btn_part = this->getButtonPartByIndex(index);
		if (btn_part != nullptr){ btn_part->setPluginName(c_p->name); };
		this->setOneRow(index, c_p->name, btn_part);
	}
}

/*-------------------------------------------------
		表格结构 - 刷新表格（全部插件，含搜索）
*/
void P_PluginListPart::refreshTable_allPlugin(int start_index, int end_index){
	if (this->m_table == nullptr){ return; }
	this->clearTableItem();
	if (start_index < 0){ start_index = 0; }
	if (end_index <= 0){ return; }

	// > 显示的插件
	if (end_index >= this->m_allAnnotationData.count()){ end_index = this->m_allAnnotationData.count() - 1; }
	this->m_table->setRowCount(end_index - start_index + 1);
	for (int i = start_index; i <= end_index; i++){
		C_ScriptAnnotation data = this->m_allAnnotationData.at(i);
		
		int index = i - start_index;
		P_PluginAttr_ButtonPart* btn_part = this->getButtonPartByIndex(index);
		if (btn_part != nullptr){ btn_part->setPluginName(data.getName()); };
		this->setOneRow(index, data.getName(), btn_part);
	}

}
/*-------------------------------------------------
		私有 - 添加一行
*/
void P_PluginListPart::setOneRow(int row, QString pluginName, QWidget* widget){

	C_PluginData* c_p = S_PluginDataContainer::getInstance()->getPluginData(pluginName);
	C_ScriptAnnotation data = S_InformationDataContainer::getInstance()->getAnnotation(pluginName);

	// > 不标蓝情况
	if(  ui.comboBox_pluginMode->currentIndex() == 0 || 
		(ui.comboBox_pluginMode->currentIndex() == 1 && this->m_searchText.isEmpty())){

		QTableWidgetItem* first_item = new QTableWidgetItem();
		first_item->setText(pluginName);
		first_item->setToolTip(pluginName);
		this->m_table->setItem(row, 0, first_item);

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

		QTableWidgetItem* first_item = new QTableWidgetItem();
		first_item->setToolTip(pluginName);
		this->m_table->setItem(row, 0, first_item);
		this->m_table->setCellWidget(row, 0, this->getLabelWithSign(pluginName, this->m_searchText));

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
				this->m_table->setItem(row, 2, new QTableWidgetItem());
				this->m_table->setItem(row, 3, new QTableWidgetItem());
				this->m_table->setItem(row, 4, new QTableWidgetItem());
				this->m_table->setCellWidget(row, 2, this->getLabelWithSign(version, this->m_searchText));
				this->m_table->setCellWidget(row, 3, this->getLabelWithSign(data.getPlugindesc_type(), this->m_searchText));
				this->m_table->setCellWidget(row, 4, this->getLabelWithSign(data.getPlugindesc_name(), this->m_searchText));
			}else{
				this->m_table->setItem(row, 4, new QTableWidgetItem());
				this->m_table->setCellWidget(row, 4, this->getLabelWithSign(data.getPlugindesc(), this->m_searchText));
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
	result_text.append("<\\p>");
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
		表格事件 - 双击表格节点
*/
void P_PluginListPart::tableDoubled(QTableWidgetItem *item){
	if (this->slot_block){ return; };
	this->slot_block = true;

	QTableWidgetItem * first_item = this->m_table->item(item->row(),0);
	QString plugin_name = first_item->toolTip();
	emit pluginTriggered(plugin_name);

	this->slot_block = false;
}
/*-------------------------------------------------
		表格事件 - 右键表格节点
*/
void P_PluginListPart::tableRightClicked(QPoint p){
	if (this->slot_block){ return; };
	this->slot_block = true;

	if (this->m_table->itemAt(p) == nullptr){ return; }
	QTableWidgetItem* item = this->m_table->itemAt(p);	//QPoint返回的是鼠标坐标值，treeWidget可以通过itemAt()获取到item。

	qDebug() << this->m_table->indexAt(p);
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