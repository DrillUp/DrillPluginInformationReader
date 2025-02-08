#ifndef P_ScriptHelp_Docs_H
#define P_ScriptHelp_Docs_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Docs.h"

#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		�ࣺ		����ĵ� �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_Docs : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Docs(QWidget *parent = 0);
		~P_ScriptHelp_Docs();
		
	//-----------------------------------
	//----�ؼ�
	public:
		QList<QLabel*> m_labelTank;
	public slots: 
										//�ؼ� - �����ǩ
		void clearAllLabel();
										//�ؼ� - ���ӱ����
		void linkClicked_docs(QString data);

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_Docs* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Docs ui;

};

#endif // P_ScriptHelp_Docs_H
