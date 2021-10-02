#ifndef P_ScriptHelp_Performance_H
#define P_ScriptHelp_Performance_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Performance.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Performance.h"

/*
-----==========================================================-----
		�ࣺ		������� �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_Performance : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Performance(QWidget *parent = 0);
		~P_ScriptHelp_Performance();
		
	//-----------------------------------
	//----�ؼ�
	public slots: 

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_Performance* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Performance ui;

};

#endif // P_ScriptHelp_Performance_H
