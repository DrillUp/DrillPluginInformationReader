#ifndef P_OtherFunctionPart_H
#define P_OtherFunctionPart_H

#include <QtWidgets>
#include "ui_P_OtherFunctionPart.h"

/*
-----==========================================================-----
		�ࣺ		�������� �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������ܵı༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_OtherFunctionPart : public QWidget
{
	Q_OBJECT

	public:
		P_OtherFunctionPart(QWidget *parent = 0);
		~P_OtherFunctionPart();
		
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
		Ui::P_OtherFunctionPart ui;

};

#endif // P_OtherFunctionPart_H
