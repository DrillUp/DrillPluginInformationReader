#ifndef P_ScriptHelp_Src_H
#define P_ScriptHelp_Src_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Src.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Src.h"

/*
-----==========================================================-----
		�ࣺ		��Դ·�� �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_Src : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Src(QWidget *parent = 0);
		~P_ScriptHelp_Src();
		
	//-----------------------------------
	//----�ؼ�
	public slots: 

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_Src* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Src ui;

};

#endif // P_ScriptHelp_Src_H
