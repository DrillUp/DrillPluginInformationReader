#pragma once
#include <QList>
#include <QJsonObject>


/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.h
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelpDetail{

	public:
		C_ScriptHelpDetail();
		~C_ScriptHelpDetail();
		
	public:
		QString name;				//��������ļ�����
		QString help;				//������Ϣ��@help��

	//-----------------------------------
	//----������
	public:
										//���������
		const bool operator== (const C_ScriptHelpDetail& a)const;
										//ʵ���� -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> ʵ����
		void setJsonObject(QJsonObject obj);
};
