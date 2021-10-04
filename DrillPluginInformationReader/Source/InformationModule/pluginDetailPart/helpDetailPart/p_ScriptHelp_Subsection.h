#ifndef P_ScriptHelp_Subsection_H
#define P_ScriptHelp_Subsection_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Subsection.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Subsection.h"

/*
-----==========================================================-----
		�ࣺ		�ֶ�˵�� �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_Subsection : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Subsection(QWidget *parent = 0);
		~P_ScriptHelp_Subsection();
		
	//-----------------------------------
	//----�ؼ�
	public:
		QList<QLabel*> m_labelTank;
	public slots: 
										//�ؼ� - ���ȫ���ӿؼ�
		void clearAllChild();
										//�ؼ� - ���ӱ����
		void linkClicked_docs(QString data);

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_Subsection* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Subsection ui;

};

#endif // P_ScriptHelp_Subsection_H
