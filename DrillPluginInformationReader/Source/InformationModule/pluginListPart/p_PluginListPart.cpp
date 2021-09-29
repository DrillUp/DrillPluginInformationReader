#include "stdafx.h"
#include "p_PluginListPart.h"

#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		����б� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					
-----==========================================================-----
*/
P_PluginListPart::P_PluginListPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_pluginMode, 30);
	this->initTable(ui.treeWidget_plugin);
	ui.widget->setVisible(false);

	// > ����ť�ؼ�
	this->m_treeBtnList = QList<P_PluginAttr_ButtonPart*>();
	for (int i = 0; i < 100; i++){
		P_PluginAttr_ButtonPart* btn_part = new P_PluginAttr_ButtonPart(this);
		btn_part->setVisible(false);
		this->m_treeBtnList.append(btn_part);
	}

	// > ��ҳ�ؼ�
	this->m_p_PageNavigator = new P_PageNavigator();
	this->m_p_PageNavigator->initNavigator(100, 100, 5);
	ui.verticalLayout->addWidget(this->m_p_PageNavigator);

	//-----------------------------------
	//----�¼���

	// > ����ȫ��ʱ����ˢ��
	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, this, &P_PluginListPart::refreshTable);

	// > ����ȫ��ʱ����ˢ�����е�ע������
	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, S_InformationDataContainer::getInstance(), &S_InformationDataContainer::loadAllAnnotationData);

	// > ������仯ʱ��ˢ��
	connect(ui.comboBox_pluginMode, &QComboBox::currentTextChanged, this, &P_PluginListPart::treeModeChanged);

	// > ��ҳ�仯ʱ
	connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &P_PluginListPart::refreshTableAuto);

}
P_PluginListPart::~P_PluginListPart(){
}


/*-------------------------------------------------
		���ṹ - ��ʼ��
*/
void P_PluginListPart::initTable(QTableWidget* table){
	this->m_table = table;

	// > ui��ʼ��
	this->m_table->horizontalHeader()->resizeSection(0, 260);
	this->m_table->horizontalHeader()->resizeSection(1, 120);
	this->m_table->horizontalHeader()->resizeSection(2, 100);
	this->m_table->horizontalHeader()->resizeSection(3, 70);
	this->m_table->horizontalHeader()->resizeSection(4, 200);
	this->m_table->horizontalHeader()->resizeSection(5, 70);

	// > �¼���
	connect(this->m_table, &QTreeWidget::itemDoubleClicked, this, &P_PluginListPart::treeDoubled);
	connect(this->m_table, &QTreeWidget::customContextMenuRequested, this, &P_PluginListPart::treeRightClicked);


}

/*-------------------------------------------------
		���ṹ - ������仯
*/
void P_PluginListPart::treeModeChanged(QString text){

	// > ������ʾ
	if (ui.comboBox_pluginMode->currentIndex() == 0){
		ui.widget->setVisible(false);
	}
	if (ui.comboBox_pluginMode->currentIndex() == 1){
		ui.widget->setVisible(true);
	}
	
	// > ˢ����
	this->refreshTable();
}
/*-------------------------------------------------
		���ṹ - ������
*/
void P_PluginListPart::clearTreeItem(){

	// > �˰�ť��
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

	// > ������ؼ�
	this->m_treeItemList.clear();
	this->m_tree->clear();
}

/*-------------------------------------------------
		���ṹ - ˢ�������Զ���
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
		���ṹ - ˢ���������õĲ����
*/
void P_PluginListPart::refreshTable_configedPlugin(int start_index, int end_index){
	if (this->m_tree == nullptr){ return; }
	this->clearTreeItem();

	// > ���õĲ��
	QList<C_PluginData*> data_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = start_index; i < end_index; i++){
		if (i >= data_list.count()){ return; }
		C_PluginData* c_p = data_list.at(i);

		int index = i - start_index;
		this->addOneRow(c_p->name, this->getButtonPartByIndex(index));
	}

	// > ˢ�·�ҳ��
	this->m_p_PageNavigator->setAllCount(data_list.count());
}

/*-------------------------------------------------
		���ṹ - ˢ������ȫ�������
*/
void P_PluginListPart::refreshTable_allPlugin(int start_index, int end_index){
	if (this->m_tree == nullptr){ return; }
	this->clearTreeItem();

	// > ȫ�����
	QList<C_ScriptAnnotation> data_list = S_InformationDataContainer::getInstance()->getAnnotationTank();
	for (int i = start_index; i < end_index; i++){
		if (i >= data_list.count()){ return; }
		C_ScriptAnnotation data = data_list.at(i);
		
		int index = i - start_index;
		this->addOneRow(data.getName(), this->getButtonPartByIndex(index));
	}

	// > ˢ�·�ҳ��
	this->m_p_PageNavigator->setAllCount(data_list.count());
}
/*-------------------------------------------------
		˽�� - ���һ��
*/
void P_PluginListPart::addOneRow(QString pluginName, QWidget* widget){
	QTreeWidgetItem* new_item = new QTreeWidgetItem(this->m_tree);
	this->m_tree->addTopLevelItem(new_item);
	this->m_treeItemList.append(new_item);
	new_item->setText(0, pluginName);

	C_PluginData* c_p = S_PluginDataContainer::getInstance()->getPluginData(pluginName);
	C_ScriptAnnotation data = S_InformationDataContainer::getInstance()->getAnnotation(pluginName);

	// > �ָ���
	if (pluginName.contains("---")){
		new_item->setText(4, data.getPlugindesc());

	// > �����
	}else{
		
		// > ��ť��
		if (widget != nullptr){
			this->m_tree->setItemWidget(new_item, 1, widget);
			widget->setVisible(true);
		}

		// > �ı�
		QString version = data.getPlugindesc_version();
		if (version.isEmpty() == false){
			new_item->setText(2, version);
			new_item->setText(3, data.getPlugindesc_type());
			new_item->setText(4, data.getPlugindesc_name());
		}else{
			new_item->setText(4, data.getPlugindesc());		//���������汾ʱ����ʾȫ����
		}
		if (c_p == nullptr){
			new_item->setText(5, "δװ��");		//��������δ�ҵ��ģ���� δװ�أ�
		}else{
			new_item->setText(5, c_p->status ? "ON" : "OFF");
		}
	}
}

/*-------------------------------------------------
		��ť�� - ��ȡ��ť��
*/
P_PluginAttr_ButtonPart* P_PluginListPart::getButtonPartByIndex(int index){
	if (index < 0){ return nullptr; }
	if (index >= this->m_treeBtnList.count()){ return nullptr; }
	return this->m_treeBtnList.at(index);
}


/*-------------------------------------------------
		���¼� - ˫�����ڵ�
*/
void P_PluginListPart::treeDoubled(QTreeWidgetItem *item, int col){
	if (this->slot_block){ return; };
	this->slot_block = true;

	/* --------------�༭���--------------*/
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
		���¼� - �Ҽ����ڵ�
*/
void P_PluginListPart::treeRightClicked(QPoint p){
	if (this->slot_block){ return; };
	this->slot_block = true;

	if (this->m_tree->itemAt(p) == nullptr){ return; }
	QTreeWidgetItem* item = this->m_tree->itemAt(p);	//QPoint���ص����������ֵ��treeWidget����ͨ��itemAt()��ȡ��item��

	qDebug() << this->m_tree->indexAt(p);
	//...

	this->slot_block = false;
}


/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginListPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginListPart::putUiToData(){
	//�����ޣ�
}