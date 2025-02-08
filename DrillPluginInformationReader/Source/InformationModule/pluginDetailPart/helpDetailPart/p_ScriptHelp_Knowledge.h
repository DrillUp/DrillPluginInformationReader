#ifndef P_ScriptHelp_Knowledge_H
#define P_ScriptHelp_Knowledge_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Knowledge.h"

#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelp_Knowledge.h"

/*
-----==========================================================-----
		�ࣺ		ָ�� �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_Knowledge : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Knowledge(QWidget *parent = 0);
		~P_ScriptHelp_Knowledge();
		
	//-----------------------------------
	//----�ؼ�
	public:
		QList<QLabel*> m_labelTank;
	public slots: 
										//�ؼ� - ���ȫ������
		void clearAllChild();
										//�ؼ� - ���ӱ����
		void linkClicked_docs(QString data);

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_Knowledge* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Knowledge ui;

};

#endif // P_ScriptHelp_Knowledge_H
