#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-ָ�� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Command{

	public:
		C_ScriptHelp_Command();
		~C_ScriptHelp_Command();

	//-----------------------------------
	//----����
	public:
		QStringList pluginCommand;		//ȫ�����ָ��
		QStringList pluginNote;			//ȫ�����ע��

};
