#ifndef P_PluginListPart_H
#define P_PluginListPart_H

#include <QtWidgets>
#include "ui_P_PluginListPart.h"

#include "buttonPart/p_PluginAttr_ButtonPart.h"

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
		bool slot_block;									//�¼�����
		QTreeWidget* m_tree;								//���ṹ
		QList<QTreeWidgetItem*> m_treeItemList;				//��Ҷ
		QList<P_PluginAttr_ButtonPart*> m_treeBtnList;		//���԰�ť��
	public slots:
										//���ṹ - ��ʼ��
		void initTree(QTreeWidget* tree);
										//���ṹ - ������仯
		void treeModeChanged(QString text);
										//���ṹ - ˢ�������Զ���
		void refreshTree();
										//���ṹ - ˢ���������õĲ����
		void refreshTree_configedPlugin();
										//���ṹ - ˢ������ȫ�������
		void refreshTree_allPlugin();
	private:
										//˽�� - ���һ��
		void addOneRow(QString pluginName);

	//-----------------------------------
	//----���¼�
	public slots:
										//���¼� - ˫�����ڵ�
		void treeDoubled(QTreeWidgetItem *item, int col);
										//���¼� - �Ҽ����ڵ�
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
