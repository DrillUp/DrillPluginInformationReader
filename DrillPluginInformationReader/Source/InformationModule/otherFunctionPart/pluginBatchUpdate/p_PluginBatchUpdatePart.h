#ifndef P_PluginBatchUpdatePart_H
#define P_PluginBatchUpdatePart_H

#include <QtWidgets>
#include "ui_P_PluginBatchUpdatePart.h"

#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"

/*
-----==========================================================-----
		�ࣺ		���²�� �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	���²���ı༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginBatchUpdatePart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginBatchUpdatePart(QWidget *parent = 0);
		~P_PluginBatchUpdatePart();
		
	//-----------------------------------
	//----����ѡ��
	public:
		QList<C_PluginData*> m_curPluginData;
		QList<C_PluginData*> m_tarPluginData;
	public slots: 
										//�ؼ� - ��һ��
		void btn_nextStep();
										//�ؼ� - ��һ��
		void btn_lastStep();

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
		Ui::P_PluginBatchUpdatePart ui;

};

#endif // P_PluginBatchUpdatePart_H
