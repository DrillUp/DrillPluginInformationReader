#ifndef P_PluginListPart_H
#define P_PluginListPart_H

#include <QtWidgets>
#include "ui_P_PluginListPart.h"

/*
-----==========================================================-----
		�ࣺ		����б� �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginListPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginListPart(QWidget *parent = 0);
		~P_PluginListPart();
		
	//-----------------------------------
	//----���ṹ
	public:
		bool slot_block;			//�¼�����
		QTreeWidget* m_root;		//����
		QList<QTreeWidgetItem*> list_PluginTreeItems;
	public:
										//���ṹ - ��ʼ��
		void initTree(QTreeWidget* tree);
										//���ṹ - ˢ����
		void refreshTree();

	public slots:
										//���ṹ - ˫�����ڵ�
		void treeDoubled(QTreeWidgetItem *item, int col);
										//���ṹ - �Ҽ����ڵ�
		void treeRightClicked(QPoint p);

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_PluginListPart ui;

};

#endif // P_PluginListPart_H
