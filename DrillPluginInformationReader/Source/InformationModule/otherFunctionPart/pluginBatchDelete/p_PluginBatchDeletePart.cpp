#include "stdafx.h"
#include "p_PluginBatchDeletePart.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
#include "Source/Utils/operater/recycleBinOperater/p_RecycleBinOperater.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������ �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������ı༭��ṹ��

		˵����		�˿ؼ��鴴����ֱ�Ӵӵ�ǰ �Ѷ�ȡ�Ĳ������ �н�����
-----==========================================================-----
*/
P_PluginBatchDeletePart::P_PluginBatchDeletePart(QWidget *parent)
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
	connect(ui.pushButton_selectAll, &QPushButton::clicked, this, &P_PluginBatchDeletePart::btn_selectAll);
	connect(ui.pushButton_deselectAll, &QPushButton::clicked, this, &P_PluginBatchDeletePart::btn_deselectAll);
	connect(ui.pushButton_execute, &QPushButton::clicked, this, &P_PluginBatchDeletePart::btn_execute);

	this->refreshTable();
}

P_PluginBatchDeletePart::~P_PluginBatchDeletePart(){
}

/*-------------------------------------------------
		�ؼ� - ��ʼ���б�
*/
void P_PluginBatchDeletePart::refreshTable(){

	this->m_table->horizontalHeader()->resizeSection(0, 80);
	this->m_table->horizontalHeader()->resizeSection(1, 140);
	this->m_table->horizontalHeader()->resizeSection(2, 110);
	this->m_table->horizontalHeader()->resizeSection(3, 80);
	this->m_table->horizontalHeader()->resizeSection(4, 220);
	this->m_table->horizontalHeader()->resizeSection(5, 80);

	// > ��ʾ�Ĳ��
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
	this->m_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);		//������Ӧ
}
/*-------------------------------------------------
		�ļ��в�� - ���һ��
*/
void P_PluginBatchDeletePart::setOneRow_configedPlugin(int row, QString pluginName){
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

	// > �ָ���
	if (pluginName.contains("---")){
		this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc()));

	// > �����
	}else{

		// > �ı�
		QString version = data.getPlugindesc_version();
		if (version.isEmpty() == false){
			this->m_table->setItem(row, 2, new QTableWidgetItem(version));
			this->m_table->setItem(row, 3, new QTableWidgetItem(data.getPlugindesc_type()));
			this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc_name()));
		}else{
			this->m_table->setItem(row, 3, new QTableWidgetItem(data.getPlugindesc_type()));
			this->m_table->setItem(row, 4, new QTableWidgetItem(data.getPlugindesc()));		//���������汾ʱ����ʾȫ����
		}
		this->m_table->setItem(row, 5, new QTableWidgetItem("δװ��"));			//��������δ�ҵ��ģ���� δװ�أ�
	}
}
/*-------------------------------------------------
		�ؼ� - ȫѡ
*/
void P_PluginBatchDeletePart::btn_selectAll(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		checkbox->setChecked(true);
	}
}
/*-------------------------------------------------
		�ؼ� - ȡ��ȫѡ
*/
void P_PluginBatchDeletePart::btn_deselectAll(){
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkbox = this->m_checkBoxList.at(i);
		checkbox->setChecked(false);
	}
}
/*-------------------------------------------------
		�ؼ� - ִ��ɾ��
*/
void P_PluginBatchDeletePart::btn_execute(){
	QStringList data_list = QStringList();
	for (int i = 0; i < this->m_checkBoxList.count(); i++){
		QCheckBox* checkBox = this->m_checkBoxList.at(i);
		if (checkBox->isChecked()){
			data_list.append( checkBox->toolTip() );
		}
	}

	// > �ƶ�������վ
	if (ui.radioButton_recycleBin->isChecked()){
		for (int i = 0; i < data_list.count(); i++){
			QFileInfo fileinfo = S_RmmvDataContainer::getInstance()->getRmmvFile_Plugin(data_list.at(i));
			P_RecycleBinOperater::moveToRecycleBin(fileinfo.absoluteFilePath());
		}

		S_InformationDataContainer::getInstance()->removeAnnotation(data_list);
		this->refreshTable();
	}

	// > ֱ��ɾ��
	if (ui.radioButton_delete->isChecked()){
		for (int i = 0; i < data_list.count(); i++){
			QFileInfo fileinfo = S_RmmvDataContainer::getInstance()->getRmmvFile_Plugin(data_list.at(i));
			QFile file(fileinfo.absoluteFilePath());
			file.remove();
		}

		S_InformationDataContainer::getInstance()->removeAnnotation(data_list);
		this->refreshTable();
	}
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginBatchDeletePart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginBatchDeletePart::putUiToData(){
	//�����ޣ�
}