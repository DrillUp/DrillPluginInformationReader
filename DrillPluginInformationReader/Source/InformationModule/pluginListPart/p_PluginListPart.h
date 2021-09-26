#ifndef P_PluginListPart_H
#define P_PluginListPart_H

#include <QtWidgets>
#include "ui_P_PluginListPart.h"

/*
-----==========================================================-----
		类：		插件列表 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_PluginListPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginListPart(QWidget *parent = 0);
		~P_PluginListPart();
		
	//-----------------------------------
	//----树结构
	public:
		bool slot_block;			//事件阻塞
		QTreeWidget* m_root;		//树根
		QList<QTreeWidgetItem*> list_PluginTreeItems;
	public:
										//树结构 - 初始化
		void initTree(QTreeWidget* tree);
										//树结构 - 刷新树
		void refreshTree();

	public slots:
										//树结构 - 双击树节点
		void treeDoubled(QTreeWidgetItem *item, int col);
										//树结构 - 右键树节点
		void treeRightClicked(QPoint p);

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_PluginListPart ui;

};

#endif // P_PluginListPart_H
