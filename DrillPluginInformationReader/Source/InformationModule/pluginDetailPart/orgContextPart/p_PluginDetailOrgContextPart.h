#ifndef P_PluginDetailOrgContextPart_H
#define P_PluginDetailOrgContextPart_H

#include <QtWidgets>
#include "ui_P_PluginDetailOrgContextPart.h"

/*
-----==========================================================-----
		�ࣺ		ԭ��չ�� �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	ԭ��չ���ı༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginDetailOrgContextPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginDetailOrgContextPart(QWidget *parent = 0);
		~P_PluginDetailOrgContextPart();

	//-----------------------------------
	//----�ؼ�
	public slots:
										//�ؼ� - �����ı�
		void setContext(QString context);

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_PluginDetailOrgContextPart ui;

};

#endif // P_PluginDetailOrgContextPart_H
