#ifndef P_PluginBatchUpdatePart_H
#define P_PluginBatchUpdatePart_H

#include <QtWidgets>
#include "ui_P_PluginBatchUpdatePart.h"

#include "Source/RmmvInteractiveModule/base/c_RmmvProjectData.h"
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
		C_RmmvProjectData m_cur_project;
		C_RmmvProjectData m_tar_project;
		QList<C_PluginData*> m_curPluginData;
		QList<C_PluginData*> m_tarPluginData;
	public slots: 
										//�ؼ� - ������ - ���뵱ǰ����
		void btn_cur_fillCur();
										//�ؼ� - ������ - ѡ��
		void btn_cur_select();
										//�ؼ� - Ŀ�깤�� - ���뵱ǰ����
		void btn_tar_fillCur();
										//�ؼ� - Ŀ�깤�� - ѡ��
		void btn_tar_select();
										//�ؼ� - ��һ��
		void btn_nextStep();
										//�ؼ� - ��һ��
		void btn_lastStep();
										//�ؼ� - ��ˢ�������
		bool reloadPluginData();

	//-----------------------------------
	//----�ؼ�
	public:
		QTableWidget* m_table;
		QList<QCheckBox*> m_checkBoxList;
	public slots: 
										//�ؼ� - ��ʼ���б�
		void refreshTable();
										//�ؼ� - ���һ��
		void setOneRow_configedPlugin(int row, C_PluginData* cur_data, C_PluginData* tar_data);
										//�ؼ� - ȫѡ
		void btn_selectAll();
										//�ؼ� - ȡ��ȫѡ
		void btn_deselectAll();
										//�ؼ� - ֻѡ��������
		void btn_selectLevelUp();
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
