#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-������ ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_EffectScope{

	public:
		C_ScriptHelp_EffectScope();
		~C_ScriptHelp_EffectScope();

	//-----------------------------------
	//----����
	public:
		QStringList scope_list;		//�����򣨵�ͼ����/ս������/�˵����棩
		QString comments;			//������˵��
	public:
							//���� - �������ڵ�ͼ����
		bool isEnableSenceMap();
							//���� - ��������ս������
		bool isEnableSenceBattle();
							//���� - �������ڲ˵�����
		bool isEnableSenceMenu();
							//���� - ����������������Ľ���
		QStringList getOtherSence();

};
