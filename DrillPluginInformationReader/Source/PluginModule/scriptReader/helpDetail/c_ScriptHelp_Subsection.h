#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-�½� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_SubsectionPage{

	public:
		C_ScriptHelp_SubsectionPage();
		~C_ScriptHelp_SubsectionPage();

	//-----------------------------------
	//----����
	public:
		QString title;				//�½ڱ���
		QStringList comment_list;	//�����б�

};
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
		QStringList main_list;							//������˵��
	protected:
		QList<C_ScriptHelp_SubsectionPage> page_list;	//�½��б�
	public:
								//���� - ����½�
		void addPage(QString page_context); 
};
