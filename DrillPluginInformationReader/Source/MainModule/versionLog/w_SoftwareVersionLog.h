#ifndef W_SoftwareVersionLog_H
#define W_SoftwareVersionLog_H

#include <QtWidgets/QDialog>
#include "ui_W_SoftwareVersionLog.h"

/*
-----==========================================================-----
		�ࣺ		�汾��־����.h
		����ģ�飺	������ģ��
		���ܣ�		�汾��־���ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_SoftwareVersionLog : public QDialog
{
	Q_OBJECT

	public:
		W_SoftwareVersionLog(QWidget *parent = 0);		//���캯��
		~W_SoftwareVersionLog();						//��������
		
	//-----------------------------------
	//----����
									//���� - ��������
									//���� - ��ȡ����
									//���� - �������� -> ui����
									//���� - ui���� -> ��������
									//���� - �ύ���ݣ�У�飩
	private:
		Ui::W_SoftwareVersionLog ui;
		
};

#endif // W_QExpressionTest_H
