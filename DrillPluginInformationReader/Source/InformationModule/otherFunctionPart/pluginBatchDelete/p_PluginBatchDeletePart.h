#ifndef P_PluginBatchDeletePart_H
#define P_PluginBatchDeletePart_H

#include <QtWidgets>
#include "ui_P_PluginBatchDeletePart.h"

#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"

/*
-----==========================================================-----
		�ࣺ		������ �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������ı༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginBatchDeletePart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginBatchDeletePart(QWidget *parent = 0);
		~P_PluginBatchDeletePart();
		
	//-----------------------------------
	//----�ؼ�
	public:
		QTableWidget* m_table;
		QList<QCheckBox*> m_checkBoxList;
		QList<C_ScriptAnnotation> m_allSearchedData;	//��ǰ���ݣ��ļ��в����
	public slots: 
										//�ؼ� - ��ʼ���б�
		void refreshTable();
										//�ؼ� - ���һ��
		void setOneRow_configedPlugin(int row, QString pluginName);
										//�ؼ� - ȫѡ
		void btn_selectAll();
										//�ؼ� - ȡ��ȫѡ
		void btn_deselectAll();
										//�ؼ� - ִ������
		void btn_execute();

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_PluginBatchDeletePart ui;

};

#endif // P_PluginBatchDeletePart_H
