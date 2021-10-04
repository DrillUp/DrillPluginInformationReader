#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-����ĵ� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Docs{

	public:
		C_ScriptHelp_Docs();
		~C_ScriptHelp_Docs();

	//-----------------------------------
	//----����
	public:
		QStringList main_docx;		//��Ҫ�����ĵ�
		QStringList relative_docx;	//��ذ����ĵ�
	public:
									//���� - �����Ҫ�ĵ�
		void addMainDocx(QString docx);
		void addMainDocx(QStringList docx_list);
									//���� - �������ĵ�
		void addRelativeDocx(QString docx);
		void addRelativeDocx(QStringList docx_list);
									//���� - �Ƿ����ĵ�
		bool hasAnyDocx();

};
