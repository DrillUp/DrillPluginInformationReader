#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-��Դ·�� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Src{

	public:
		C_ScriptHelp_Src();
		~C_ScriptHelp_Src();

	//-----------------------------------
	//----����
	public:
		QStringList src_list;		//��Դ·��
		QString context;			//·��˵��
		QString example;			//����˵��

	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ ��Դ·�� �ַ���
		void readSrc(QStringList src_contextRows);

};
