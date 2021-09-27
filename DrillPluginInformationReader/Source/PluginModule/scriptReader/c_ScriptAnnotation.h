#pragma once
#include <QList>
#include <QMap>


/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.h
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�
					����������ĳ�ʼ��ͨ����ȡ����ֵ����ɡ���
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelpDetail;
class C_ScriptDictionary;
class C_ScriptAnnotation{

	public:
		C_ScriptAnnotation();
		~C_ScriptAnnotation();
		
	//-----------------------------------
	//----����
	protected:
		QString name;								//��������ļ�����
		QString plugindesc;							//���������@plugindesc��
		QString author;								//���ߣ�@author��
		C_ScriptHelpDetail* helpDetail;				//������Ϣ��@help + �������ݣ�
		C_ScriptDictionary* dictionary;				//�����ֵ䣨@paramȫ�����ݣ�

	public:
										//���� - ��ȡ��������ļ�����
		QString getName();
										//���� - ��ȡ���������@plugindesc��
		QString getPlugindesc();
										//���� - ��ȡ���ߣ�@author��
		QString getAuthor();
										//���� - ��ȡ������Ϣȫ�ģ�@help��
		QString getHelp();
										//���� - �Ƿ�Ϊ��������������
		bool isCompleted();
										//���� - ������Ϣ����
		C_ScriptHelpDetail* getScriptHelpDetail();
										//���� - �����ֵ�����
		C_ScriptDictionary* getScriptDictionary();
										//���� - ��ȡ�汾��������� ��ȡ�Σ�
		QString getPlugindesc_version();
										//���� - ��ȡ���ͣ�������� ��ȡ�Σ�
		QString getPlugindesc_type();
										//���� - ��ȡ��������������� ��ȡ�Σ�
		QString getPlugindesc_name();
		
										//���� - ���ò�������ļ�����
		void setName(QString name);
										//���� - ���ò��������@plugindesc��
		void setPlugindesc(QString plugindesc);
										//���� - �������ߣ�@author��
		void setAuthor(QString author);
										//���� - ���ð�����Ϣ����
		void setScriptHelpDetail(C_ScriptHelpDetail* helpDetail);
										//���� - ���ò����ֵ�����
		void setScriptDictionary(C_ScriptDictionary* dictionary);

	//-----------------------------------
	//----������
	public:
										//���ж�
		bool isNull();	
										//���������
		const bool operator== (const C_ScriptAnnotation& a)const;
										//ʵ���� -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> ʵ����
		void setJsonObject(QJsonObject obj);
};
