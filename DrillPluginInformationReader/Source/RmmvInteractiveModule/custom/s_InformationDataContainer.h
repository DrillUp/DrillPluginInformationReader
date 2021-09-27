#pragma once

#include "Source/PluginModule/scriptReader/s_ScriptAnnotationReader.h"

/*
-----==========================================================-----
		�ࣺ		�����ϸ��Ϣ ����.h
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		����ָ�������е�ȫ������������ݡ�
					����װ�������ṹ��ע����ն�ȡ���źš�
					����ϸ��.cpp��
-----==========================================================-----
*/
class S_InformationDataContainer : public QObject
{
	Q_OBJECT

	public:
		S_InformationDataContainer();
		~S_InformationDataContainer();
		static S_InformationDataContainer* cur_manager;			//����
		static S_InformationDataContainer* getInstance();		//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩

	//-----------------------------------
	//----����
	private:
		QList<C_ScriptAnnotation> data_AnnotationTank;
	public:
										//���� - ��ȡȫ���������
										//		��˵��������ȡ����ǰ��Ҫȷ����֮ǰ �ֶ� ִ����read��ȡ����Ȼ��ȡ�������ݡ�
		QList<C_ScriptAnnotation> getAnnotationTank();
										//���� - ��ȡ��Ӧ�Ĳ������
										//		��˵��������ȡ����ǰ��Ҫȷ����֮ǰ �ֶ� ִ����read��ȡ����Ȼ��ȡ�������ݡ�
										//		��˵������û���򷵻ؿ�ָ�롣
		C_ScriptAnnotation getAnnotation(QString pluginName);


	//-----------------------------------
	//----��ȡ
	public slots:
										//��ȡ - ��ȡȫ���������ݣ�plugins�ļ��������в����
		void loadAllAnnotationData();

};
