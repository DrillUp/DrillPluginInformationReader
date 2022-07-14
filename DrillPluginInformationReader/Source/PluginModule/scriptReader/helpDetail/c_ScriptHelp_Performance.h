#pragma once
#include <QList>

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		��������-���Խ�� ������.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_PerformanceTestDetail{

	public:
		C_ScriptHelp_PerformanceTestDetail();
		~C_ScriptHelp_PerformanceTestDetail();
		
	//-----------------------------------
	//----����
	protected:
		double cost;					//����ֵ
		QString description;			//��������
		QString condition_scene;		//���� - ����
		int condition_level;			//���� - �̶ȣ�0:���̶ֳȵĽ���������ԣ�1-4:1Ϊ�����̶�,4Ϊ��ǿ�̶ȣ�
	public:
								//���� - ��ȡ����ֵ
		double getCostValue();
								//���� - ��ȡ������ʾ�ı�
		QString getCostString();
								//���� - ��ȡ��������
		QString getDescription();
								//���� - ��ȡ���� - ����
		QString getCondition_scene();
								//���� - ��ȡ���� - �̶�
		int getCondition_level();
								//���� - ���ж�
		bool isNull();
		
	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ ���Խ�� �ַ���
		void readTestDetail(QString one_row);
};

/*
-----==========================================================-----
		�ࣺ		��������-������ ������.h
		���ߣ�		drill_up
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
		QString text_method;									//���Է�������Ϊ�գ�
		QList<C_ScriptHelp_PerformanceTestDetail> detail_list;	//���Խ��
	public:
								//���� - ��ȡ�����б�
		QList<double> getCostList();
								//���� - ��ȡ�������
		double getMaxCost();
								//���� - ��ȡ������ģ�����������
								//		��˵���������û��ֵ���򷵻�-1��
		double getMaxCost_ByLevel(QString scene_name, int level);
								//���� - ��ȡ��С���ģ�����������
								//		��˵���������û��ֵ���򷵻�-1��
		double getMinCost_ByLevel(QString scene_name, int level);
		
	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ ���Խ�� �ַ���
		void readTest(QString test_context);
};
/*
-----==========================================================-----
		�ࣺ		��������-������� ������.h
		���ߣ�		drill_up
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
		double max_cost;									//������ģ��ݴ������
	public:
								//���� - ���ж�
		bool isNull();

								//���� - ��ȡ�������
		double getMaxCost();
								//���� - ��ȡ������ģ�����������
								//		��˵���������û��ֵ���򷵻�-1��
		double getMaxCost_ByLevel(QString scene_name, int level);
								//���� - ��ȡ��С���ģ�����������
								//		��˵���������û��ֵ���򷵻�-1��
		double getMinCost_ByLevel(QString scene_name, int level);

								//���� - �Ƿ������
		bool isHighCost();
								//���� - �Ƿ�������
		bool isMiddleCost();
								//���� - �Ƿ������
		bool isLowCost();
	private:
								//���� - ��ȡ������ģ�˽�У�
		double getMaxCost_Private();

	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ ������� �ַ���
		void readPerformance(QString performance_context);

};
