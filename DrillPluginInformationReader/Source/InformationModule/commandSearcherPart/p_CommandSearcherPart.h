#ifndef P_CommandSearcherPart_H
#define P_CommandSearcherPart_H

#include <QtWidgets>
#include "ui_P_CommandSearcherPart.h"

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
	public slots: 


	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_CommandSearcherPart ui;

};

#endif // P_CommandSearcherPart_H
