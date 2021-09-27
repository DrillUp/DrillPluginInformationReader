#ifndef P_PluginAttr_ButtonPart_H
#define P_PluginAttr_ButtonPart_H

#include <QtWidgets>
#include "ui_P_PluginAttr_ButtonPart.h"

/*
-----==========================================================-----
		�ࣺ		������� ��ť��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	���������ʾ�õİ�ť�顣
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginAttr_ButtonPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginAttr_ButtonPart(QWidget *parent = 0);
		~P_PluginAttr_ButtonPart();

	//-----------------------------------
	//----�ؼ�
	public slots:
										//�ؼ� - ��Դ��ť
		void btn_src();
		
	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_PluginAttr_ButtonPart ui;

};

#endif // P_PluginAttr_ButtonPart_H
