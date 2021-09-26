#include "stdafx.h"
#include "p_PluginListPart.h"

#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
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
	this->list_PluginTreeItems = QList<QTreeWidgetItem*>();

	//-----------------------------------
	//----�ؼ���ʼ��
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_pluginMode, 30);
	this->initTree(ui.treeWidget_configedPlugin);

	//-----------------------------------
	//----�¼���

}
P_PluginListPart::~P_PluginListPart(){
}


/*-------------------------------------------------
		���ṹ - ��ʼ��
*/
void P_PluginListPart::initTree(QTreeWidget* tree){
	this->m_root = tree;

	/* --------------�¼���--------------*/
	connect(this->m_root, &QTreeWidget::itemDoubleClicked, this, &P_PluginListPart::treeDoubled);
	connect(this->m_root, &QTreeWidget::customContextMenuRequested, this, &P_PluginListPart::treeRightClicked);

	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, this, &P_PluginListPart::refreshTree);
	

	/* --------------ui��ʼ��--------------*/
	this->m_root->header()->resizeSection(0, 320);
	this->m_root->header()->resizeSection(1, 80);
	this->m_root->header()->resizeSection(2, 340);
}

/*-------------------------------------------------
		���ṹ - ˢ����
*/
void P_PluginListPart::refreshTree(){
	if (this->m_root == nullptr){ return; }
	this->m_root->clear();
	this->list_PluginTreeItems.clear();

	/* --------------��ȡ���Ĳ��--------------*/
	QList<C_PluginData*> datas = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < datas.count(); i++){
		C_PluginData* c_p = datas.at(i);
		
		QTreeWidgetItem* new_item = new QTreeWidgetItem(this->m_root);
		new_item->setText(0, c_p->name);
		if (c_p->name.contains("---")){

		}else{
			new_item->setText(1, c_p->status ? "ON" : "OFF");
		}
		new_item->setText(2, c_p->description);
		this->list_PluginTreeItems.append(new_item);
	}

	/* --------------��϶����--------------*/
	this->m_root->header()->resizeSection(0, 320);
	this->m_root->header()->resizeSection(1, 80);
	this->m_root->header()->resizeSection(2, 340);
}


/*-------------------------------------------------
		���ṹ - ˫�����ڵ�
*/
void P_PluginListPart::treeDoubled(QTreeWidgetItem *item, int col){
	if (this->slot_block){ return; };
	this->slot_block = true;

	/* --------------�༭���--------------*/
	QList<C_PluginData*> datas = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < datas.count(); i++) {
		C_PluginData* c_p = datas.at(i);
		if (c_p->name == item->text(0) ) {
			//if (this->list_PluginWindow.at(i) == nullptr) {
			//	this->list_PluginWindow[i] = new W_PluginEntityEdit();
			//	this->list_PluginWindow[i]->setData(c_p);
			//	this->list_PluginWindow[i]->show();
			//}
			//else {
			//	this->list_PluginWindow[i]->show();
			//	this->list_PluginWindow[i]->activateWindow();
			//}
			
		}
	}

	this->slot_block = false;
}
/*-------------------------------------------------
		���ṹ - �Ҽ����ڵ�
*/
void P_PluginListPart::treeRightClicked(QPoint p){
	if (this->slot_block){ return; };
	this->slot_block = true;

	if (this->m_root->itemAt(p) == nullptr){ return; }
	QTreeWidgetItem* item = this->m_root->itemAt(p);	//QPoint���ص����������ֵ��treeWidget����ͨ��itemAt()��ȡ��item��

	qDebug() << this->m_root->indexAt(p);

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