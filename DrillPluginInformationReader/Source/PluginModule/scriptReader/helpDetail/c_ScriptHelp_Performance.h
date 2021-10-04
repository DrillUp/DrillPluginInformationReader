#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-������� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Performance{

	public:
		C_ScriptHelp_Performance();
		~C_ScriptHelp_Performance();

	//-----------------------------------
	//----����
	public:
		QStringList performance;		//�������
		QStringList note;				//�������˵��
	public:
								//���� - �Ƿ������
		bool isHighCost();
								//���� - �Ƿ�������
		bool isMiddleCost();
								//���� - �Ƿ������
		bool isLowCost();

};
