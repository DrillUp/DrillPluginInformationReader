#ifndef P_ScriptHelp_EffectScope_H
#define P_ScriptHelp_EffectScope_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_EffectScope.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_EffectScope.h"

/*
-----==========================================================-----
		�ࣺ		������ �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_EffectScope : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_EffectScope(QWidget *parent = 0);
		~P_ScriptHelp_EffectScope();
		
	//-----------------------------------
	//----�ؼ�
	public slots: 

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_EffectScope* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_EffectScope ui;

};

#endif // P_ScriptHelp_EffectScope_H
