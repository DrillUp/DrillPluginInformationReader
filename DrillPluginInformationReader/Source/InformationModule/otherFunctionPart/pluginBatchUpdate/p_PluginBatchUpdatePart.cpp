#include "stdafx.h"
#include "p_PluginBatchUpdatePart.h"

#include "Source/RmmvUtilsProjectModule/ProjectData/S_RmmvProjectDataContainer.h"
#include "Source/Utils/operater/recycleBinOperater/p_RecycleBinOperater.h"
#include "Source/Utils/Common/P_FileOperater.h"
#include "Source/Utils/Common/TTool.h"

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
	//----控件初始化
	this->m_table = ui.tableWidget_plugin;

	//-----------------------------------
	//----事件绑定
	connect(ui.pushButton_cur_1, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_cur_fillCur);
	connect(ui.pushButton_cur_2, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_cur_select);
	connect(ui.pushButton_tar_1, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_tar_fillCur);
	connect(ui.pushButton_tar_2, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_tar_select);

	connect(ui.pushButton_next, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_nextStep);
	connect(ui.pushButton_last, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_lastStep);
	connect(ui.pushButton_selectAll, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_selectAll);
	connect(ui.pushButton_deselectAll, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_deselectAll);
	connect(ui.pushButton_selectLevelUp, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_selectLevelUp);
	connect(ui.pushButton_execute, &QPushButton::clicked, this, &P_PluginBatchUpdatePart::btn_execute);

	ui.stackedWidget->setCurrentIndex(0);	//（强制回到第一页）
	this->refreshTable();
}

P_PluginBatchUpdatePart::~P_PluginBatchUpdatePart(){
}

/*-------------------------------------------------
		控件 - 主工程 - 填入当前工程
*/
void P_PluginBatchUpdatePart::btn_cur_fillCur(){
	this->m_cur_project = S_RmmvProjectDataContainer::getInstance()->getData();
	ui.lineEdit_curProject->setText(this->m_cur_project.getName());
}
/*-------------------------------------------------
		控件 - 主工程 - 选择
*/
void P_PluginBatchUpdatePart::btn_cur_select(){
	C_RmmvProjectData temp_data = C_RmmvProjectData::callRmmvSelectDialog();
	if (temp_data.isNull()){ return; }

	this->m_cur_project = temp_data;
	ui.lineEdit_curProject->setText(temp_data.getName());
}
/*-------------------------------------------------
		控件 - 目标工程 - 填入当前工程
*/
void P_PluginBatchUpdatePart::btn_tar_fillCur(){
	this->m_tar_project = S_RmmvProjectDataContainer::getInstance()->getData();
	ui.lineEdit_tarProject->setText(this->m_tar_project.getName());
}
/*-------------------------------------------------
		控件 - 目标工程 - 选择
*/
void P_PluginBatchUpdatePart::btn_tar_select(){
	C_RmmvProjectData temp_data = C_RmmvProjectData::callRmmvSelectDialog();
	if (temp_data.isNull()){ return; }

	this->m_tar_project = temp_data;
	ui.lineEdit_tarProject->setText(temp_data.getName());
}

/*-------------------------------------------------
		控件 - 下一步
*/
void P_PluginBatchUpdatePart::btn_nextStep(){

	// > 校验
	if (this->m_cur_project.isNull() || this->m_tar_project.isNull()){
		QMessageBox::warning(this, "错误", "填入的两个工程不能为空。", QMessageBox::Yes);
		return;
	}
	if (this->m_cur_project.getRootPath() == this->m_tar_project.getRootPath()){
		QMessageBox::warning(this, "错误", "填入不能是同一个工程。", QMessageBox::Yes);
		return;
	}

	bool success = this->reloadPluginData();
	if (success){
		ui.stackedWidget->setCurrentIndex(1);
	}
}
/*-------------------------------------------------
		控件 - 上一步
*/
void P_PluginBatchUpdatePart::btn_lastStep(){
	ui.stackedWidget->setCurrentIndex(0);
}
/*-------------------------------------------------
		控件 - 重刷插件数据
*/
bool P_PluginBatchUpdatePart::reloadPluginData(){
	this->m_curPluginData.clear();
	this->m_tarPluginData.clear();

	// > 准备数据（主工程）
	if (this->m_cur_project == S_RmmvProjectDataContainer::getInstance()->getData()){
		this->m_curPluginData = S_PluginDataContainer::getInstance()->getPluginDataTank();
	}else{
		// > 读取插件文件
		QString file_path = this->m_cur_project.getRootPath() + "/js/plugins.js";
		QFile plugin_file(file_path);
		if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(nullptr, "错误", "未找到plugins.js文件。", QMessageBox::Yes);
			return false;
		}
		QString plugin_context = plugin_file.readAll();

		// > 全部数据初始化
		this->m_curPluginData = S_PluginDataContainer::getInstance()->loadPluginDataDirectly(plugin_context);
	}

	// > 准备数据（目标工程）
	if (this->m_tar_project == S_RmmvProjectDataContainer::getInstance()->getData()){
		this->m_tarPluginData = S_PluginDataContainer::getInstance()->getPluginDataTank();
	}else{
		// > 读取插件文件
		QString file_path = this->m_tar_project.getRootPath() + "/js/plugins.js";
		QFile plugin_file(file_path);
		if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(nullptr, "错误", "未找到plugins.js文件。", QMessageBox::Yes);
			return false;
		}
		QString plugin_context = plugin_file.readAll();

		// > 全部数据初始化
		this->m_tarPluginData = S_PluginDataContainer::getInstance()->loadPluginDataDirectly(plugin_context);
	}

	this->refreshTable();
	return true;
}


/*-------------------------------------------------
		控件 - 初始化列表
*/
void P_PluginBatchUpdatePart::refreshTable(){

	this->m_table->horizontalHeader()->resizeSection(0, 70);
	this->m_table->horizontalHeader()->resizeSection(1, 170);
	this->m_table->horizontalHeader()->resizeSection(2, 210);
	this->m_table->horizontalHeader()->resizeSection(3, 80);
	this->m_table->horizontalHeader()->resizeSection(4, 220);
	this->m_table->horizontalHeader()->resizeSection(5, 80);

	bool has_rows = true;
	if (this->m_tarPluginData.count() == 0){ has_rows = false; }
	if (this->m_curPluginData.count() == 0){ has_rows = false; }

	if (has_rows == true){

		// > 显示的插件
		this->m_checkBoxList.clear();
		this->m_table->clearContents();
		this->m_table->setRowCount(0);

		int cur_row = 0;
		for (int i = 0; i < this->m_tarPluginData.count(); i++){
			C_PluginData* tar_data = this->m_tarPluginData.at(i);
			if (tar_data->name.contains("---")){ continue; }

			for (int j = 0; j < this->m_curPluginData.count(); j++){
				C_PluginData* cur_data = this->m_curPluginData.at(j);
				if (cur_data->name == tar_data->name){	//（匹配的插件名时，添加一行）
					this->setOneRow_configedPlugin(cur_row, cur_data, tar_data);
					cur_row += 1;
					break;
				}
			}
		}
		this->m_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);		//行自适应

		if (cur_row == 0){ has_rows = false; }
	}
	
	// > 没有行时
	if (has_rows == false){
		ui.widget_btns->setEnabled(false);
		ui.tableWidget_plugin->setVisible(false);
		ui.label_tableTip->setVisible(false);
		ui.label_noTableItemTip->setVisible(true);
	}else{
		ui.widget_btns->setEnabled(true);
		ui.tableWidget_plugin->setVisible(true);
		ui.label_tableTip->setVisible(true);
		ui.label_noTableItemTip->setVisible(false);
	}
}
/*-------------------------------------------------
		文件夹插件 - 添加一行
*/
void P_PluginBatchUpdatePart::setOneRow_configedPlugin(int row, C_PluginData* cur_data, C_PluginData* tar_data){
	if (row >= this->m_table->rowCount()){
		this->m_table->setRowCount(row + 1);
	}

	double cur_version = cur_data->getDescription_versionNum();
	double tar_version = tar_data->getDescription_versionNum();

	QWidget* w = new QWidget();
	QHBoxLayout* l = new QHBoxLayout();
	QCheckBox* checkBox = new QCheckBox();
	checkBox->setChecked(false);
	checkBox->setToolTip(cur_data->name);
	if (cur_version == -1 || tar_version == -1){
		checkBox->setStatusTip("未识别");
	}else if (tar_version < cur_version){
		checkBox->setStatusTip("升级");
	}else if (tar_version == cur_version){
		checkBox->setStatusTip("同步");
	}else if (tar_version > cur_version){
		checkBox->setStatusTip("降级");
	}
	l->addWidget(checkBox);
	w->setLayout(l);
	this->m_table->setCellWidget(row, 0, w);
	this->m_checkBoxList.append(checkBox);

	QTableWidgetItem* first_item = new QTableWidgetItem();
	first_item->setText(cur_data->name);
	first_item->setToolTip(cur_data->name);
	this->m_table->setItem(row, 1, first_item);

	// > 文本
	if (cur_version == -1 || tar_version == -1){
		this->m_table->setItem(row, 2, new QTableWidgetItem("【未识别】"));
		this->m_table->setItem(row, 3, new QTableWidgetItem(cur_data->getDescription_type()));
		this->m_table->setItem(row, 4, new QTableWidgetItem(cur_data->description));		//（读不到版本时，显示全名）
	}else{
		QString version_text = "";
		if (cur_version == tar_version){
			version_text.append( cur_data->getDescription_version() );
			version_text.append(" 无需更新");
		}else{
			//version_text.append(QString::number(tar_version, 'f', 2));
			//version_text.append(" -> ");
			//version_text.append(QString::number(cur_version, 'f', 2));
			version_text.append( tar_data->getDescription_version() );
			version_text.append(" -> ");
			version_text.append( cur_data->getDescription_version() );
			version_text.append("【");
			if (cur_version > tar_version){
				version_text.append("可升级");
			}else{
				version_text.append("会降级");
			}
			version_text.append("】");
		}
		this->m_table->setItem(row, 2, new QTableWidgetItem(version_text));
		this->m_table->setItem(row, 3, new QTableWidgetItem(cur_data->getDescription_type()));
		this->m_table->setItem(row, 4, new QTableWidgetItem(cur_data->getDescription_name()));
	}
	this->m_table->setItem(row, 5, new QTableWidgetItem(tar_data->status ? "ON" : "OFF"));
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
		控件 - 只选可升级项
*/
void P_PluginBatchUpdatePart::btn_selectLevelUp(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		if (checkbox->statusTip() == "升级"){
			checkbox->setChecked(true);
		}else{
			checkbox->setChecked(false);
		}
	}
}
/*-------------------------------------------------
		控件 - 执行更新
*/
void P_PluginBatchUpdatePart::btn_execute(){
	QStringList data_list = QStringList();

	// > 空列表情况
	if (this->m_checkBoxList.count() == 0){
		QMessageBox::warning(nullptr, "提示", "没有任何需要更新的插件。", QMessageBox::Yes);
		return;
	}

	// > 检查勾选
	bool has_check = false;
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		if (checkbox->isChecked() == true){
			has_check = true;
			break;
		}
	}
	if (has_check == false){
		QMessageBox::warning(nullptr, "提示", "你未勾选任何插件。", QMessageBox::Yes);
		return;
	}

	// > 检查升级/降级情况
	bool has_des = false;
	bool has_inc = false;
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		if (checkbox->isChecked() == true){
			if (checkbox->statusTip() == "降级"){
				has_des = true;
			}
			else if (checkbox->statusTip() == "升级"){
				has_inc = true;
			}
			else if (checkbox->statusTip() == "未识别"){	//（未识别算升级项）
				has_inc = true;
			}
		}
	}

	// > 更新提示
	if (has_des == true){
		switch (QMessageBox::information(this, "提示", "勾选中包含降级的插件，\n\r并且更新后被覆盖的文件无法找回，是否执行更新？", "确定", "取消", 0, 1)){
			case 0:
				break;
			case 1:
			default:
				return;
			}
	}else if (has_inc == false){
		switch (QMessageBox::information(this, "提示", "勾选中没有可升级的插件，\n\r并且更新后被覆盖的文件无法找回，是否执行更新？", "确定", "取消", 0, 1)){
			case 0:
				break;
			case 1:
			default:
				return;
		}
	}else{
		switch (QMessageBox::information(this, "提示", "更新后被覆盖的文件无法找回，是否执行更新？", "确定", "取消", 0, 1)){
			case 0:
				break;
			case 1:
			default:
				return;
		}
	}

	// > 生成更新清单
	QStringList pluginList;
	QString context;
	context.append(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
	context.append("\r\n");
	context.append("\r\n");
	context.append("\t注意，更新只替换插件文件，插件的参数配置仍需要你去打开 插件管理器 点开插件然后确定对话框 才能更新。");
	context.append("\r\n");
	context.append("\r\n");
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		if (checkbox->isChecked() == false){ continue; }
		pluginList.append(checkbox->toolTip());
		context.append("\t");
		context.append(checkbox->toolTip());
		context.append("\t");
		context.append(this->m_table->item(i, 2)->text());
		context.append("\r\n");
	}

	// > 生成更新清单（根据勾选生成）
	if (ui.checkBox_makeList->isChecked()){
		QString context_path = this->m_tar_project.getRootPath() + "/js/plugins/插件更新" + QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".txt";
		QFile file_to(context_path);
		if (!file_to.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			QMessageBox::warning(this, "错误", "无法生成插件清单。", QMessageBox::Yes);
			return;
		}
		file_to.write(context.toLocal8Bit());
		file_to.close();
	}

	// > 更新插件
	P_FileOperater p_FileOperater;
	for (int i = 0; i < pluginList.count(); i++){
		QString plugin_name = pluginList.at(i);
		QString cur_path = this->m_cur_project.getRootPath() + "/js/plugins/" + plugin_name + ".js";
		QString tar_path = this->m_tar_project.getRootPath() + "/js/plugins/" + plugin_name + ".js";
		p_FileOperater.remove_File(QFileInfo(tar_path));
		p_FileOperater.copy_File(QFileInfo(cur_path), QFileInfo(tar_path));
	}

	// > 更新插件列表
	for (int i = 0; i < pluginList.count(); i++){
		QString plugin_name = pluginList.at(i);
		C_PluginData* cur_data = nullptr;
		C_PluginData* tar_data = nullptr;
		for (int j = 0; j < this->m_curPluginData.count(); j++){
			C_PluginData* data = this->m_curPluginData.at(j);
			if (data->name == plugin_name){
				cur_data = data;
				break;
			}
		}
		for (int j = 0; j < this->m_tarPluginData.count(); j++){
			C_PluginData* data = this->m_tarPluginData.at(j);
			if (data->name == plugin_name){
				tar_data = data;
				break;
			}
		}
		if (cur_data == nullptr){ continue; }
		if (tar_data == nullptr){ continue; }
		tar_data->description = cur_data->description;
	}
	QString plugin_context = S_PluginDataContainer::getInstance()->writePluginDataDirectly(this->m_tarPluginData);
	QString plugin_tar_path = this->m_tar_project.getRootPath() + "/js/plugins.js";
	QFile file_plugin(plugin_tar_path);
	if (!file_plugin.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		QMessageBox::warning(this, "错误", "无法更新插件配置。", QMessageBox::Yes);
		return;
	}
	file_plugin.write(plugin_context.toUtf8());
	file_plugin.close();

	QMessageBox::warning(this, "提示", "更新完成。", QMessageBox::Yes);

	// > 重刷插件数据
	bool success = this->reloadPluginData();
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