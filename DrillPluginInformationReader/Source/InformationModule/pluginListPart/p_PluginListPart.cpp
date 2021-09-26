#include "stdafx.h"
#include "p_PluginListPart.h"

#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
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
	this->list_PluginTreeItems = QList<QTreeWidgetItem*>();

	//-----------------------------------
	//----控件初始化
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_pluginMode, 30);
	this->initTree(ui.treeWidget_configedPlugin);

	//-----------------------------------
	//----事件绑定

}
P_PluginListPart::~P_PluginListPart(){
}


/*-------------------------------------------------
		树结构 - 初始化
*/
void P_PluginListPart::initTree(QTreeWidget* tree){
	this->m_root = tree;

	/* --------------事件绑定--------------*/
	connect(this->m_root, &QTreeWidget::itemDoubleClicked, this, &P_PluginListPart::treeDoubled);
	connect(this->m_root, &QTreeWidget::customContextMenuRequested, this, &P_PluginListPart::treeRightClicked);

	connect(S_PluginDataContainer::getInstance(), &S_PluginDataContainer::pluginDataReloaded, this, &P_PluginListPart::refreshTree);
	

	/* --------------ui初始化--------------*/
	this->m_root->header()->resizeSection(0, 320);
	this->m_root->header()->resizeSection(1, 80);
	this->m_root->header()->resizeSection(2, 340);
}

/*-------------------------------------------------
		树结构 - 刷新树
*/
void P_PluginListPart::refreshTree(){
	if (this->m_root == nullptr){ return; }
	this->m_root->clear();
	this->list_PluginTreeItems.clear();

	/* --------------读取到的插件--------------*/
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

	/* --------------间隙调整--------------*/
	this->m_root->header()->resizeSection(0, 320);
	this->m_root->header()->resizeSection(1, 80);
	this->m_root->header()->resizeSection(2, 340);
}


/*-------------------------------------------------
		树结构 - 双击树节点
*/
void P_PluginListPart::treeDoubled(QTreeWidgetItem *item, int col){
	if (this->slot_block){ return; };
	this->slot_block = true;

	/* --------------编辑插件--------------*/
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
		树结构 - 右键树节点
*/
void P_PluginListPart::treeRightClicked(QPoint p){
	if (this->slot_block){ return; };
	this->slot_block = true;

	if (this->m_root->itemAt(p) == nullptr){ return; }
	QTreeWidgetItem* item = this->m_root->itemAt(p);	//QPoint返回的是鼠标坐标值，treeWidget可以通过itemAt()获取到item。

	qDebug() << this->m_root->indexAt(p);

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