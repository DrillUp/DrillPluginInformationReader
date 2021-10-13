#ifndef P_CommandSearcherPart_H
#define P_CommandSearcherPart_H

#include <QtWidgets>
#include "ui_P_CommandSearcherPart.h"

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
