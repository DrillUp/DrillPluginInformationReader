#ifndef P_DesignTip_Cell_H
#define P_DesignTip_Cell_H

#include <QtWidgets>
#include "ui_P_DesignTip_Cell.h"
#include "c_DesignTip_Cell.h"

/*
-----==========================================================-----
		�ࣺ		���������-���� �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		˵����		��ʾ�ؼ� ���������-���� ��Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_DesignTip_Cell : public QWidget
{
	Q_OBJECT

	public:
		P_DesignTip_Cell(QWidget *parent = 0);
		~P_DesignTip_Cell();
		
	//-----------------------------------
	//----�ؼ�
	public slots: 
										//�ؼ� - ���ӱ����
		void linkClicked_plugin(QString data);

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_DesignTip_Cell data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();

	private:
		Ui::P_DesignTip_Cell ui;
};

#endif // P_DesignTip_Cell_H
