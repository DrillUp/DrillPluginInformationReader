#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-�ֶ�˵�� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Subsection{

	public:
		C_ScriptHelp_Subsection();
		~C_ScriptHelp_Subsection();

	//-----------------------------------
	//----����
	public:
		QStringList m_effectScope;		//�����򣨵�ͼ����/ս������/�˵����棩
		QString m_effectScopeComments;	//������˵��

};
