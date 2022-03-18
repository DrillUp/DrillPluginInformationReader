#include "stdafx.h"
#include "p_PluginBatchUpdatePart.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
#include "Source/Utils/operater/recycleBinOperater/p_RecycleBinOperater.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		更新插件 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	更新插件的编辑块结构。

		说明：		此控件块创建后，直接从当前 已读取的插件数据 中解析。
-----==========================================================-----
*/
P_PluginBatchUpdatePart::P_PluginBatchUpdatePart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	

	//-----------------------------------
	//----控件初始化
	this->m_table = ui.tableWidget_plugin;

	//-----------------------------------
	//----事件绑定
	connect(ui.pushButton_next, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_nextStep);
	connect(ui.pushButton_last, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_lastStep);
	connect(ui.pushButton_selectAll, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_selectAll);
	connect(ui.pushButton_deselectAll, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_deselectAll);
	connect(ui.pushButton_execute, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_execute);

	this->refreshTable();
}

P_PluginBatchUpdatePart::~P_PluginBatchUpdatePart(){
}

/*-------------------------------------------------
		控件 - 下一步
*/
void P_PluginBatchUpdatePart::btn_nextStep(){

	// > 校验
	//if (ui.lineEdit_curProject->text()){
	//
	//}

	ui.stackedWidget->setCurrentIndex(1);
}
/*-------------------------------------------------
		控件 - 上一步
*/
void P_PluginBatchUpdatePart::btn_lastStep(){
	ui.stackedWidget->setCurrentIndex(0);
}


/*-------------------------------------------------
		控件 - 初始化列表
*/
void P_PluginBatchUpdatePart::refreshTable(){

	this->m_table->horizontalHeader()->resizeSection(0, 80);
	this->m_table->horizontalHeader()->resizeSection(1, 160);
	this->m_table->horizontalHeader()->resizeSection(2, 110);
	this->m_table->horizontalHeader()->resizeSection(3, 80);
	this->m_table->horizontalHeader()->resizeSection(4, 220);
	this->m_table->horizontalHeader()->resizeSection(5, 80);

	// > 显示的插件
	this->m_checkBoxList.clear();
	this->m_table->clearContents();
	this->m_table->setRowCount(0);
	this->m_allSearchedData = S_InformationDataContainer::getInstance()->getAnnotationTank();
	int cur_row = 0;
	for (int i = 0; i < this->m_allSearchedData.count(); i++){
		C_ScriptAnnotation data = this->m_allSearchedData.at(i);
		C_PluginData* c_p = S_PluginDataContainer::getInstance()->getPluginData(data.getName());
		if (c_p == nullptr){
			this->setOneRow_configedPlugin(cur_row, data.getName());
			cur_row += 1;
		}
	}
	this->m_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);		//行自适应
}
/*-------------------------------------------------
		文件夹插件 - 添加一行
*/
void P_PluginBatchUpdatePart::setOneRow_configedPlugin(int row, QString pluginName){
	C_ScriptAnnotation data = S_InformationDataContainer::getInstance()->getAnnotation(pluginName);
	if (row >= this->m_table->rowCount()){
		this->m_table->setRowCount(row + 1);
	}

	QWidget* w = new QWidget();
	QHBoxLayout* l = new QHBoxLayout();
	QCheckBox* checkBox = new QCheckBox();
	checkBox->setChecked(true);
	checkBox->setToolTip(pluginName);
	l->addWidget(checkBox);
	w->setLayout(l);
	this->m_table->setCellWidget(row, 0, w);
	this->m_checkBoxList.append(checkBox);

	QTableWidgetItem* first_item = new QTableWidgetItem();
	first_item->setText(pluginName);
	first_item->setToolTip(pluginName);
	this->m_table->setItem(row, 1, first_item);

	// > 分割线
	if (pluginName.contains("---")){
		this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc()));

	// > 插件行
	}else{

		// > 文本
		QString version = data.getPlugindesc_version();
		if (version.isEmpty() == false){
			this->m_table->setItem(row, 2, new QTableWidgetItem(version));
			this->m_table->setItem(row, 3, new QTableWidgetItem(data.getPlugindesc_type()));
			this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc_name()));
		}else{
			this->m_table->setItem(row, 3, new QTableWidgetItem(data.getPlugindesc_type()));
			this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc()));		//（读不到版本时，显示全名）
		}
		this->m_table->setItem(row, 5, new QTableWidgetItem("未装载"));			//（配置中未找到的，标记 未装载）
	}
}
/*-------------------------------------------------
		控件 - 全选
*/
void P_PluginBatchUpdatePart::btn_selectAll(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		checkbox->setChecked(true);
	}
}
/*-------------------------------------------------
		控件 - 取消全选
*/
void P_PluginBatchUpdatePart::btn_deselectAll(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		checkbox->setChecked(false);
	}
}
/*-------------------------------------------------
		控件 - 执行删除
*/
void P_PluginBatchUpdatePart::btn_execute(){
	QStringList data_list = QStringList();
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkBox = this->m_checkBoxList.at(i);
		if (checkBox->isChecked()){
			data_list.append( checkBox->toolTip() );
		}
	}

}

/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_PluginBatchUpdatePart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_PluginBatchUpdatePart::putUiToData(){
	//（暂无）
}