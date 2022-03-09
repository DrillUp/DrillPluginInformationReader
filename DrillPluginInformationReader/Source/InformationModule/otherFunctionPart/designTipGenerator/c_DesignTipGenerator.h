#pragma once
#include <QList>
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Subsection.h"

/*
-----==========================================================-----
		�ࣺ		���������-��� ������.h
		����ģ�飺	���ģ��
		���ܣ�		����������Ĳ�����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_DesignTip{

	public:
		C_DesignTip();
		~C_DesignTip();

	//-----------------------------------
	//----����
	public:
		QString plugin_name;					//���������Ӣ������
		QString plugin_desc;					//�����������������
		C_ScriptHelp_SubsectionPage page;		//�����б�
	public:
									//���� - ���ж�
		bool isNull();
};

/*
-----==========================================================-----
		�ࣺ		���������-������� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������������õ������ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_DesignTipGenerator{

	public:
		C_DesignTipGenerator();
		~C_DesignTipGenerator();

	//-----------------------------------
	//----����
	protected:
		QList<C_DesignTip> tip_list;	//��м���
	public:
								//���� - ���ж�
		bool isNull();
	public:
								//���� - ��ȡ�½ڱ���
		void initData();

};
