#ifndef P_DesignTipGeneratorPart_H
#define P_DesignTipGeneratorPart_H

#include <QtWidgets>
#include "ui_P_DesignTipGeneratorPart.h"
#include "c_DesignTipGenerator.h"
#include "private/p_DesignTip_Cell.h"

/*
-----==========================================================-----
		�ࣺ		������������ �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������������ı༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_DesignTipGeneratorPart : public QWidget
{
	Q_OBJECT

	public:
		P_DesignTipGeneratorPart(QWidget *parent = 0);
		~P_DesignTipGeneratorPart();
		
	//-----------------------------------
	//----�ؼ�
	public:
		C_DesignTipGenerator m_data;
		QList<P_DesignTip_Cell*> m_cellTank;
	public slots: 
										//�ؼ� - ����ؼ���
		void clearCells();
										//�ؼ� - ִ������
		void doGenerate();

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_DesignTipGeneratorPart ui;

};

#endif // P_DesignTipGeneratorPart_H
