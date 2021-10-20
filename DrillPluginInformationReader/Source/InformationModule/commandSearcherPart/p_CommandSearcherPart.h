#ifndef P_CommandSearcherPart_H
#define P_CommandSearcherPart_H

#include <QtWidgets>
#include "ui_P_CommandSearcherPart.h"

#include "helpDetailPart/p_ScriptHelp_CommandSearchCell.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/Utils/widgetForm/historicalSearchRecord/p_historicalSearchRecord.h"
#include "Source/Utils/widgetForm/pageNavigator/p_PageNavigator.h"

/*
-----==========================================================-----
		�ࣺ		ָ�������� �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_CommandSearcherPart : public QWidget
{
	Q_OBJECT

	public:
		P_CommandSearcherPart(QWidget *parent = 0);
		~P_CommandSearcherPart();
		
	//-----------------------------------
	//----����ָ��
	protected:
		QString m_searchText;							//�������ı�
		QList<C_ScriptAnnotation> m_allSearchedData;	//��ǰ���ݣ��ļ��в����
	private:
										//����ָ�� - ����
		void btn_search();
										//����ָ�� - ˢ�¿ؼ�
		void refreshCellAuto( int start_index, int end_index );
										//����ָ�� - ��ָ���ַ�������
		QLabel* getLabelWithSign(QString text, QString searching_text);

	//-----------------------------------
	//----����
	protected:
		QList<P_ScriptHelp_CommandSearchCell*> m_cellPartList;					//���԰�ť��
	protected:
										//���� - ��ȡ��ť��
		P_ScriptHelp_CommandSearchCell* getButtonPartByIndex(int index);

	//-----------------------------------
	//----�ؼ�
	public:
		P_PageNavigator* m_p_PageNavigator;						//��ҳ�ؼ�
		P_HistoricalSearchRecord* m_p_historicalSearchRecord;	//��ʷ��ѯ�ؼ�
	public slots:
										//�ؼ� - �������ַ��������
		void searchTextClicked(QString text);

	//-----------------------------------
	//----��
	public:
										//�� - �û��Զ���UI��ȡ
		void ui_loadConfig();
										//�� - �û��Զ���UI�洢
		void ui_saveConfig();
	private:
		Ui::P_CommandSearcherPart ui;

};

#endif // P_CommandSearcherPart_H
