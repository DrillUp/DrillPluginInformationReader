#ifndef P_ScriptHelp_Command_H
#define P_ScriptHelp_Command_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Command.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Command.h"

/*
-----==========================================================-----
		�ࣺ		ָ�� �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_Command : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Command(QWidget *parent = 0);
		~P_ScriptHelp_Command();
		
	//-----------------------------------
	//----�ؼ�
	public slots: 

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_Command* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Command ui;

};

#endif // P_ScriptHelp_Command_H