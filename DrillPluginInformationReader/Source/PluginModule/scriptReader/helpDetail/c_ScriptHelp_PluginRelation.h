#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-�����չ ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_PluginRelation{

	public:
		C_ScriptHelp_PluginRelation();
		~C_ScriptHelp_PluginRelation();

	//-----------------------------------
	//----����
	public:
		QStringList base;			//�����չ - ����
		QStringList beingExtend;	//�����չ - �ɱ���չ/����չ
		QStringList effectTo;		//�����չ - ��������/������
	public:

};
