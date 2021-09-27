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
	this->m_treeItemList = QList<QTreeWidgetItem*>();

	//-----------------------------------
	//----�ؼ���ʼ��
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_pluginMode, 30);
	this->initTree(ui.treeWidget_plugin);
	ui.widget->setVisible(false);

	//-----------------------------------
	//----�¼���

	// > ����ȫ��ʱ����ˢ��
	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, this, &P_PluginListPart::refreshTree);

	// > ����ȫ��ʱ����ˢ�����е�ע������
	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, S_InformationDataContainer::getInstance(), &S_InformationDataContainer::loadAllAnnotationData);

	// > ������仯ʱ��ˢ��
	connect(ui.comboBox_pluginMode, &QComboBox::currentTextChanged, this, &P_PluginListPart::treeModeChanged);

}
P_PluginListPart::~P_PluginListPart(){
}


/*-------------------------------------------------
		���ṹ - ��ʼ��
*/
void P_PluginListPart::initTree(QTreeWidget* tree){
	this->m_tree = tree;

	// > ui��ʼ��
	this->m_tree->header()->resizeSection(0, 260);
	this->m_tree->header()->resizeSection(1, 120);
	this->m_tree->header()->resizeSection(2, 100);
	this->m_tree->header()->resizeSection(3, 70);
	this->m_tree->header()->resizeSection(4, 200);
	this->m_tree->header()->resizeSection(5, 70);

	// > �¼���
	connect(this->m_tree, &QTreeWidget::itemDoubleClicked, this, &P_PluginListPart::treeDoubled);
	connect(this->m_tree, &QTreeWidget::customContextMenuRequested, this, &P_PluginListPart::treeRightClicked);
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
	this->refreshTree();
}
/*-------------------------------------------------
		���ṹ - ˢ�������Զ���
*/
void P_PluginListPart::refreshTree(){
	if (ui.comboBox_pluginMode->currentIndex() == 0){
		this->refreshTree_configedPlugin();
	}
	if (ui.comboBox_pluginMode->currentIndex() == 1){
		this->refreshTree_allPlugin();
	}
}
/*-------------------------------------------------
		���ṹ - ˢ���������õĲ����
*/
void P_PluginListPart::refreshTree_configedPlugin(){
	if (this->m_tree == nullptr){ return; }
	this->m_tree->clear();
	this->m_treeItemList.clear();

	// > ���õĲ��
	QList<C_PluginData*> data_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < data_list.count(); i++){
		C_PluginData* c_p = data_list.at(i);
		this->addOneRow(c_p->name);
	}

}

/*-------------------------------------------------
		���ṹ - ˢ������ȫ�������
*/
void P_PluginListPart::refreshTree_allPlugin(){
	if (this->m_tree == nullptr){ return; }
	this->m_tree->clear();
	this->m_treeItemList.clear();

	// > ȫ�����
	QList<C_ScriptAnnotation> data_list = S_InformationDataContainer::getInstance()->getAnnotationTank();
	for (int i = 0; i < data_list.count(); i++){
		C_ScriptAnnotation data = data_list.at(i);
		this->addOneRow(data.getName());
	}
}
/*-------------------------------------------------
		˽�� - ���һ��
*/
void P_PluginListPart::addOneRow(QString pluginName){
	QTreeWidgetItem* new_item = new QTreeWidgetItem(this->m_tree);
	new_item->setText(0, pluginName);

	C_PluginData* c_p = S_PluginDataContainer::getInstance()->getPluginData(pluginName);

	C_ScriptAnnotation data = S_InformationDataContainer::getInstance()->getAnnotation(pluginName);

	if (pluginName.contains("---")){

		new_item->setText(4, data.getPlugindesc());
	}else{
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
	this->m_treeItemList.append(new_item);
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