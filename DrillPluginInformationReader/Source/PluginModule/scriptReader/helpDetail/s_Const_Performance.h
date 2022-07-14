#pragma once
#include <QJsonObject>

#include "Source/PluginModule/const/s_Const_PluginValue.h"

/*
-----==========================================================-----
		�ࣺ		������� ����ֵ.h
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���г���ֵ������ֱ�ӻ�ȡ��
					����ϸ��.cpp��
-----==========================================================-----
*/
class S_Const_Performance : public S_Const_PluginValue{

	public:
		S_Const_Performance();
		~S_Const_Performance();
		static S_Const_Performance* cur_instance;		//����
		static S_Const_Performance* getInstance();		//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		
	//-----------------------------------
	//----���ܳ���
	protected:
		QList<QList<QString>> m_performanceKeyMatrix;	//���ܹؼ���
	public:
									//��ȡ - �������ƣ��������ܹؼ��֣�
		QString getSceneName_ByPerformanceWord(QString performanceWord);

									//��ȡ - ���ܹؼ��֣�ȫ����
		QStringList getPerformanceWord_All();
									//��ȡ - ���ܹؼ��֣����ݽ������ƣ�
		QStringList getPerformanceWord_ByName(QString scene_name);
									//��ȡ - �̶ȣ��������ܹؼ��֣�
									//		��˵����������ֵΪ 1��4 �� -1��
		int getLevel_ByPerformanceWord(QString performanceWord);
};
