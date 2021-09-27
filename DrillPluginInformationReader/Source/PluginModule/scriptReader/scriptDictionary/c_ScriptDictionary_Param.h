#pragma once
#include <QList>
#include <QJsonObject>


/*
-----==========================================================-----
		�ࣺ		�����ܲ��� ʵ����.h
		����ģ�飺	���ģ��
		���ܣ�		�����Ĳ���ʶ��
-----==========================================================-----
*/
class C_ScriptDictionary_Param {

	public:
		C_ScriptDictionary_Param();
		~C_ScriptDictionary_Param();
		
	//-----------------------------------
	//----����
	public:
		QString name;			//��������@param��
		QString parent;			//������������@parent��
		QString type;			//�������ͣ�@type��
		QString desc;			//����������@desc��
		QString default_;		//����Ĭ��ֵ��@default��

		int min;				//��������-������Сֵ��@min��
		int max;				//��������-�������ֵ��@max��
		QString on;				//��������-�����ı���@on��
		QString off;			//��������-�����ı���@off��
		QStringList option;		//��������-����������ݣ�@option��
		int require;			//��������-�ļ���@require��
		QString dir;			//��������-�ļ���@dir��
		
	//-----------------------------------
	//----������
	public:
										//���������
		const bool operator== (const C_ScriptDictionary_Param& a)const;
										//ʵ���� -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> ʵ����
		void setJsonObject(QJsonObject obj);
};