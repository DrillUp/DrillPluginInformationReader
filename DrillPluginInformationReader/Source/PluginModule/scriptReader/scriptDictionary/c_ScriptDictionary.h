#pragma once
#include <QList>
#include <QJsonObject>

#include "c_ScriptDictionary_Param.h"

/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.h
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptDictionary{

	public:
		C_ScriptDictionary();
		~C_ScriptDictionary();
		
	public:
		QString name;										//��������ļ�����
		QList<C_ScriptDictionary_Param> param_list;			//�����б�@param��

	//-----------------------------------
	//----������
	public:
										//���������
		const bool operator== (const C_ScriptDictionary& a)const;
										//ʵ���� -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> ʵ����
		void setJsonObject(QJsonObject obj);
};