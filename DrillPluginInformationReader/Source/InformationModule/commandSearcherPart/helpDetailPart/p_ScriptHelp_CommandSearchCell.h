#ifndef P_ScriptHelp_CommandSearchCell_H
#define P_ScriptHelp_CommandSearchCell_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_CommandSearchCell.h"

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
class P_ScriptHelp_CommandSearchCell : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_CommandSearchCell(QWidget *parent = 0);
		~P_ScriptHelp_CommandSearchCell();
		
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
		Ui::P_ScriptHelp_CommandSearchCell ui;

};

#endif // P_ScriptHelp_CommandSearchCell_H
