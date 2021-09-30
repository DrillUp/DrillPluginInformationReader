#ifndef P_PluginListPart_H
#define P_PluginListPart_H

#include <QtWidgets>
#include "ui_P_PluginListPart.h"

#include "buttonPart/w_PluginAttrComment.h"
#include "buttonPart/p_PluginAttr_ButtonPart.h"
#include "Source/Utils/widgetForm/pageNavigator/p_PageNavigator.h"

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
		bool slot_block;					//�¼�����
		QTableWidget* m_table;				//���ṹ
	public slots:
										//��� - ��ʼ��
		void initTable(QTableWidget* table);
										//��� - ������仯
		void modeChanged(QString text);
										//��� - ������
		void clearTableItem();
										//��� - ˢ�±���Զ���
		void refreshTable();
		void refreshTableAuto( int start_index, int end_index );
										//��� - ˢ�±�����õĲ����
		void refreshTable_configedPlugin( int start_index, int end_index );
										//��� - ˢ�±��ȫ�������
		void refreshTable_allPlugin( int start_index, int end_index );
	private:
										//˽�� - ���һ��
		void setOneRow(int row, QString pluginName, QWidget* widget = nullptr);
										//˽�� - ��ָ���ַ�������
		QLabel* getLabelWithSign(QString text, QString searching_text);

	//-----------------------------------
	//----����
	protected:
		W_PluginAttrComment* m_w_PluginAttrComment;			//����˵������
		QList<P_PluginAttr_ButtonPart*> m_btnPartList;		//���԰�ť��
	protected:
										//���� - ��ȡ��ť��
		P_PluginAttr_ButtonPart* getButtonPartByIndex(int index);

	//-----------------------------------
	//----����¼�
	public slots:
										//����¼� - ˫�����
		//void treeDoubled(QTreeWidgetItem *item, int col);
										//����¼� - �Ҽ����
		//void treeRightClicked(QPoint p);
		
	//-----------------------------------
	//----��ҳ
	public:
		P_PageNavigator* m_p_PageNavigator;

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
