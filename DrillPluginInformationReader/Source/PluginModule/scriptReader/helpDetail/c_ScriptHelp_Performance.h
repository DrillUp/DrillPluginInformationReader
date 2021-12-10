#pragma once
#include <QList>

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		��������-���Խ�� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_PerformanceTest{

	public:
		C_ScriptHelp_PerformanceTest();
		~C_ScriptHelp_PerformanceTest();
		
	//-----------------------------------
	//----����
	public:
		QString text_method;				//���Է���
		QStringList condition_list;			//�����б�
		QStringList cost_list;				//�����б�
	public:
								//���� - ��ȡ�����б�
		QList<double> getCostList();
								//���� - ��ȡ�������
		double getMaxCost();
		
	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ ���Խ�� �ַ���
		void readTest(QString test_context);
};
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
		QString working_type;								//��������
		QString time_complexity;							//ʱ�临�Ӷ�
		QList<C_ScriptHelp_PerformanceTest> test_list;		//���Խ���б�
		QStringList context_note;							//�����б�
	public:
								//���� - ��ȡ�������
		double getMaxCost();
								//���� - �Ƿ������
		bool isHighCost();
								//���� - �Ƿ�������
		bool isMiddleCost();
								//���� - �Ƿ������
		bool isLowCost();

	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ ������� �ַ���
		void readPerformance(QString performance_context);

};
