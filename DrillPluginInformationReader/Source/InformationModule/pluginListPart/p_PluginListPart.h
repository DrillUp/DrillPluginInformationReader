#ifndef P_PluginListPart_H
#define P_PluginListPart_H

#include <QtWidgets>
#include "ui_P_PluginListPart.h"

#include "buttonPart/p_PluginAttr_ButtonPart.h"
#include "buttonPart/w_PluginAttr_Docs.h"
#include "buttonPart/w_PluginAttr_Src.h"
#include "buttonPart/w_PluginAttr_HighConsumption.h"
#include "buttonPart/w_PluginAttr_HasTool.h"
#include "buttonPart/w_PluginAttr_ForeignKey.h"

#include "Source/RmmvUtilsPluginModule/storageData/s_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/Utils/widgetForm/historicalSearchRecord/p_historicalSearchRecord.h"
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
										//��� - ˢ�º�����
		void refreshHorizontalSize(int table_width);
										//��� - ������
		void clearTableItem();
										//��� - ������仯
		void modeChanged(QString mode_text);
										//��� - ��ˢ���
		void rebuildTable();
										//��� - ˢ�±���Զ���
		void refreshTableAuto( int start_index, int end_index );
		

	//-----------------------------------
	//----���õĲ��
	protected:
		QList<C_PluginData*> m_allConfigedData;			//��ǰ���ݣ����õĲ����
	private:
										//���õĲ�� - ������仯
		void pluginTypeChanged(QString type_text);
										//���õĲ�� - ˢ�±�����õĲ������������
		void refreshTable_configedPlugin( int start_index, int end_index );
										//���õĲ�� - ���һ��
		void setOneRow_configedPlugin(int row, QString pluginName, QWidget* widget = nullptr);

	//-----------------------------------
	//----�ļ��в��
	protected:
		QString m_searchText;							//�������ı�
		QList<C_ScriptAnnotation> m_allSearchedData;	//��ǰ���ݣ��ļ��в����
	private:
										//�ļ��в�� - �������
		void btn_search();
										//�ļ��в�� - ˢ�±���ļ��в������������
		void refreshTable_searchedPlugin( int start_index, int end_index );
										//�ļ��в�� - ���һ��
		void setOneRow_searchedPlugin(int row, QString pluginName, QWidget* widget = nullptr);
										//�ļ��в�� - ��ָ���ַ�������
		QLabel* getLabelWithSign(QString text, QString searching_text);

	//-----------------------------------
	//----����
	protected:
		QList<P_PluginAttr_ButtonPart*> m_btnPartList;					//���԰�ť��
		W_PluginAttr_Docs* m_w_PluginAttr_Docs;							//����˵������
		W_PluginAttr_Src* m_w_PluginAttr_Src;							//����˵������
		W_PluginAttr_HighConsumption* m_w_PluginAttr_HighConsumption;	//����˵������
		W_PluginAttr_HasTool* m_w_PluginAttr_HasTool;					//����˵������
		W_PluginAttr_ForeignKey* m_w_PluginAttr_ForeignKey;				//����˵������
	protected:
										//���� - ��ȡ��ť��
		P_PluginAttr_ButtonPart* getButtonPartByIndex(int index);

	//-----------------------------------
	//----�ؼ�
	public:
		P_PageNavigator* m_p_PageNavigator;						//��ҳ�ؼ�
		P_HistoricalSearchRecord* m_p_historicalSearchRecord;	//��ʷ��ѯ�ؼ�
	public slots:
										//�ؼ� - �������ַ��������
		void searchTextClicked(QString text);
		
	//-----------------------------------
	//----����¼�
	public slots:
										//����¼� - ˫�����
		void tableDoubled(QTableWidgetItem *item);
										//����¼� - �Ҽ����
		void tableRightClicked(QPoint p);
	signals:
										//�ź� - ���ѡ��
		void pluginTriggered(QString plugin_name);

	//-----------------------------------
	//----��
	public:
										//�� - �û��Զ���UI��ȡ
		void ui_loadConfig();
										//�� - �û��Զ���UI�洢
		void ui_saveConfig();
	private:
		Ui::P_PluginListPart ui;

};

#endif // P_PluginListPart_H
