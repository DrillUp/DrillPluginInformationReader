#include "stdafx.h"
#include "p_PluginBatchUpdatePart.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
#include "Source/Utils/operater/recycleBinOperater/p_RecycleBinOperater.h"
#include "Source/Utils/common/p_FileOperater.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		���²�� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	���²���ı༭��ṹ��

		˵����		�˿ؼ��鴴����ֱ�Ӵӵ�ǰ �Ѷ�ȡ�Ĳ������ �н�����
-----==========================================================-----
*/
P_PluginBatchUpdatePart::P_PluginBatchUpdatePart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	

	//-----------------------------------
	//----�ؼ���ʼ��
	this->m_table = ui.tableWidget_plugin;

	//-----------------------------------
	//----�¼���
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

	this->refreshTable();
}

P_PluginBatchUpdatePart::~P_PluginBatchUpdatePart(){
}

/*-------------------------------------------------
		�ؼ� - ������ - ���뵱ǰ����
*/
void P_PluginBatchUpdatePart::btn_cur_fillCur(){
	this->m_cur_project = S_RmmvDataContainer::getInstance()->getRmmvProjectData();
	ui.lineEdit_curProject->setText(this->m_cur_project.getName());
}
/*-------------------------------------------------
		�ؼ� - ������ - ѡ��
*/
void P_PluginBatchUpdatePart::btn_cur_select(){
	C_RmmvProjectData temp_data = C_RmmvProjectData::callRmmvSelectDialog();
	if (temp_data.isNull()){ return; }

	this->m_cur_project = temp_data;
	ui.lineEdit_curProject->setText(temp_data.getName());
}
/*-------------------------------------------------
		�ؼ� - Ŀ�깤�� - ���뵱ǰ����
*/
void P_PluginBatchUpdatePart::btn_tar_fillCur(){
	this->m_tar_project = S_RmmvDataContainer::getInstance()->getRmmvProjectData();
	ui.lineEdit_tarProject->setText(this->m_tar_project.getName());
}
/*-------------------------------------------------
		�ؼ� - Ŀ�깤�� - ѡ��
*/
void P_PluginBatchUpdatePart::btn_tar_select(){
	C_RmmvProjectData temp_data = C_RmmvProjectData::callRmmvSelectDialog();
	if (temp_data.isNull()){ return; }

	this->m_tar_project = temp_data;
	ui.lineEdit_tarProject->setText(temp_data.getName());
}

/*-------------------------------------------------
		�ؼ� - ��һ��
*/
void P_PluginBatchUpdatePart::btn_nextStep(){

	// > У��
	if (this->m_cur_project.isNull() || this->m_tar_project.isNull()){
		QMessageBox::warning(this, "����", "������������̲���Ϊ�ա�", QMessageBox::Yes);
		return;
	}
	if (this->m_cur_project.getRootPath() == this->m_tar_project.getRootPath()){
		QMessageBox::warning(this, "����", "���벻����ͬһ�����̡�", QMessageBox::Yes);
		return;
	}

	bool success = this->reloadPluginData();
	if (success){
		ui.stackedWidget->setCurrentIndex(1);
	}
}
/*-------------------------------------------------
		�ؼ� - ��һ��
*/
void P_PluginBatchUpdatePart::btn_lastStep(){
	ui.stackedWidget->setCurrentIndex(0);
}
/*-------------------------------------------------
		�ؼ� - ��ˢ�������
*/
bool P_PluginBatchUpdatePart::reloadPluginData(){
	this->m_curPluginData.clear();
	this->m_tarPluginData.clear();

	// > ׼�����ݣ������̣�
	if (this->m_cur_project == S_RmmvDataContainer::getInstance()->getRmmvProjectData()){
		this->m_curPluginData = S_PluginDataContainer::getInstance()->getPluginDataTank();
	}else{
		// > ��ȡ����ļ�
		QString file_path = this->m_cur_project.getRootPath() + "/js/plugins.js";
		QFile plugin_file(file_path);
		if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(nullptr, "����", "δ�ҵ�plugins.js�ļ���", QMessageBox::Yes);
			return false;
		}
		QString plugin_context = plugin_file.readAll();

		// > ȫ�����ݳ�ʼ��
		this->m_curPluginData = S_PluginDataContainer::getInstance()->loadPluginDataDirectly(plugin_context);
	}

	// > ׼�����ݣ�Ŀ�깤�̣�
	if (this->m_tar_project == S_RmmvDataContainer::getInstance()->getRmmvProjectData()){
		this->m_tarPluginData = S_PluginDataContainer::getInstance()->getPluginDataTank();
	}else{
		// > ��ȡ����ļ�
		QString file_path = this->m_tar_project.getRootPath() + "/js/plugins.js";
		QFile plugin_file(file_path);
		if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(nullptr, "����", "δ�ҵ�plugins.js�ļ���", QMessageBox::Yes);
			return false;
		}
		QString plugin_context = plugin_file.readAll();

		// > ȫ�����ݳ�ʼ��
		this->m_tarPluginData = S_PluginDataContainer::getInstance()->loadPluginDataDirectly(plugin_context);
	}

	this->refreshTable();
	return true;
}


/*-------------------------------------------------
		�ؼ� - ��ʼ���б�
*/
void P_PluginBatchUpdatePart::refreshTable(){

	this->m_table->horizontalHeader()->resizeSection(0, 70);
	this->m_table->horizontalHeader()->resizeSection(1, 170);
	this->m_table->horizontalHeader()->resizeSection(2, 210);
	this->m_table->horizontalHeader()->resizeSection(3, 80);
	this->m_table->horizontalHeader()->resizeSection(4, 220);
	this->m_table->horizontalHeader()->resizeSection(5, 80);

	if (this->m_tarPluginData.count() == 0){ return; }
	if (this->m_curPluginData.count() == 0){ return; }

	// > ��ʾ�Ĳ��
	this->m_checkBoxList.clear();
	this->m_table->clearContents();
	this->m_table->setRowCount(0);

	int cur_row = 0;
	for (int i = 0; i < this->m_tarPluginData.count(); i++){
		C_PluginData* tar_data = this->m_tarPluginData.at(i);
		if (tar_data->name.contains("---")){ continue; }

		for (int j = 0; j < this->m_curPluginData.count(); j++){
			C_PluginData* cur_data = this->m_curPluginData.at(j);
			if (cur_data->name == tar_data->name){	//��ƥ��Ĳ����ʱ�����һ�У�
				this->setOneRow_configedPlugin(cur_row, cur_data, tar_data);
				cur_row += 1;
				break;
			}
		}
	}
	this->m_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);		//������Ӧ
}
/*-------------------------------------------------
		�ļ��в�� - ���һ��
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
		checkBox->setStatusTip("δʶ��");
	}else if (tar_version < cur_version){
		checkBox->setStatusTip("����");
	}else if (tar_version == cur_version){
		checkBox->setStatusTip("ͬ��");
	}else if (tar_version > cur_version){
		checkBox->setStatusTip("����");
	}
	l->addWidget(checkBox);
	w->setLayout(l);
	this->m_table->setCellWidget(row, 0, w);
	this->m_checkBoxList.append(checkBox);

	QTableWidgetItem* first_item = new QTableWidgetItem();
	first_item->setText(cur_data->name);
	first_item->setToolTip(cur_data->name);
	this->m_table->setItem(row, 1, first_item);

	// > �ı�
	if (cur_version == -1 || tar_version == -1){
		this->m_table->setItem(row, 2, new QTableWidgetItem("��δʶ��"));
		this->m_table->setItem(row, 3, new QTableWidgetItem(cur_data->getDescription_type()));
		this->m_table->setItem(row, 4, new QTableWidgetItem(cur_data->description));		//���������汾ʱ����ʾȫ����
	}else{
		QString version_text = "";
		if (cur_version == tar_version){
			version_text.append( cur_data->getDescription_version() );
			version_text.append(" �������");
		}else{
			//version_text.append(QString::number(tar_version, 'f', 2));
			//version_text.append(" -> ");
			//version_text.append(QString::number(cur_version, 'f', 2));
			version_text.append( tar_data->getDescription_version() );
			version_text.append(" -> ");
			version_text.append( cur_data->getDescription_version() );
			version_text.append("��");
			if (cur_version > tar_version){
				version_text.append("������");
			}else{
				version_text.append("�ή��");
			}
			version_text.append("��");
		}
		this->m_table->setItem(row, 2, new QTableWidgetItem(version_text));
		this->m_table->setItem(row, 3, new QTableWidgetItem(cur_data->getDescription_type()));
		this->m_table->setItem(row, 4, new QTableWidgetItem(cur_data->getDescription_name()));
	}
	this->m_table->setItem(row, 5, new QTableWidgetItem(tar_data->status ? "ON" : "OFF"));
}
/*-------------------------------------------------
		�ؼ� - ȫѡ
*/
void P_PluginBatchUpdatePart::btn_selectAll(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		checkbox->setChecked(true);
	}
}
/*-------------------------------------------------
		�ؼ� - ȡ��ȫѡ
*/
void P_PluginBatchUpdatePart::btn_deselectAll(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		checkbox->setChecked(false);
	}
}
/*-------------------------------------------------
		�ؼ� - ֻѡ��������
*/
void P_PluginBatchUpdatePart::btn_selectLevelUp(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		if (checkbox->statusTip() == "����"){
			checkbox->setChecked(true);
		}else{
			checkbox->setChecked(false);
		}
	}
}
/*-------------------------------------------------
		�ؼ� - ִ�и���
*/
void P_PluginBatchUpdatePart::btn_execute(){
	QStringList data_list = QStringList();

	// > ���б����
	if (this->m_checkBoxList.count() == 0){
		QMessageBox::warning(nullptr, "��ʾ", "û���κ���Ҫ���µĲ����", QMessageBox::Yes);
		return;
	}

	// > ��鹴ѡ
	bool has_check = false;
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		if (checkbox->isChecked() == true){
			has_check = true;
			break;
		}
	}
	if (has_check == false){
		QMessageBox::warning(nullptr, "��ʾ", "��δ��ѡ�κβ����", QMessageBox::Yes);
		return;
	}

	// > �������/�������
	bool has_des = false;
	bool has_inc = false;
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		if (checkbox->isChecked() == true){
			if (checkbox->statusTip() == "����"){
				has_des = true;
			}
			else if (checkbox->statusTip() == "����"){
				has_inc = true;
			}
			else if (checkbox->statusTip() == "δʶ��"){	//��δʶ���������
				has_inc = true;
			}
		}
	}

	// > ������ʾ
	if (has_des == true){
		switch (QMessageBox::information(this, "��ʾ", "��ѡ�а��������Ĳ����\n\r���Ҹ��º󱻸��ǵ��ļ��޷��һأ��Ƿ�ִ�и��£�", "ȷ��", "ȡ��", 0, 1)){
			case 0:
				break;
			case 1:
			default:
				return;
			}
	}else if (has_inc == false){
		switch (QMessageBox::information(this, "��ʾ", "��ѡ��û�п������Ĳ����\n\r���Ҹ��º󱻸��ǵ��ļ��޷��һأ��Ƿ�ִ�и��£�", "ȷ��", "ȡ��", 0, 1)){
			case 0:
				break;
			case 1:
			default:
				return;
		}
	}else{
		switch (QMessageBox::information(this, "��ʾ", "���º󱻸��ǵ��ļ��޷��һأ��Ƿ�ִ�и��£�", "ȷ��", "ȡ��", 0, 1)){
			case 0:
				break;
			case 1:
			default:
				return;
		}
	}

	// > ���ɸ����嵥
	QStringList pluginList;
	QString context;
	context.append(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
	context.append("\r\n");
	context.append("\r\n");
	context.append("\tע�⣬����ֻ�滻����ļ�������Ĳ�����������Ҫ��ȥ�� ��������� �㿪���Ȼ��ȷ���Ի��� ���ܸ��¡�");
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

	// > ���ɸ����嵥�����ݹ�ѡ���ɣ�
	if (ui.checkBox_makeList->isChecked()){
		QString context_path = this->m_tar_project.getRootPath() + "/js/plugins/�������" + QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".txt";
		QFile file_to(context_path);
		if (!file_to.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			QMessageBox::warning(this, "����", "�޷����ɲ���嵥��", QMessageBox::Yes);
			return;
		}
		file_to.write(context.toLocal8Bit());
		file_to.close();
	}

	// > ���²��
	P_FileOperater p_FileOperater;
	for (int i = 0; i < pluginList.count(); i++){
		QString plugin_name = pluginList.at(i);
		QString cur_path = this->m_cur_project.getRootPath() + "/js/plugins/" + plugin_name + ".js";
		QString tar_path = this->m_tar_project.getRootPath() + "/js/plugins/" + plugin_name + ".js";
		p_FileOperater.remove_File(QFileInfo(tar_path));
		p_FileOperater.copy_File(QFileInfo(cur_path), QFileInfo(tar_path));
	}

	// > ���²���б�
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
		QMessageBox::warning(this, "����", "�޷����²�����á�", QMessageBox::Yes);
		return;
	}
	file_plugin.write(plugin_context.toUtf8());
	file_plugin.close();

	QMessageBox::warning(this, "��ʾ", "������ɡ�", QMessageBox::Yes);
	this->reloadPluginData();
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginBatchUpdatePart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginBatchUpdatePart::putUiToData(){
	//�����ޣ�
}