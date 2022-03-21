#pragma once
#include <QJsonObject>

/*
-----==========================================================-----
		�ࣺ		rmmv�������� ʵ����.h
		�汾��		v1.01
		����ģ�飺	����ģ��
		���ܣ�		���̻�����Ϣ���ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_RmmvProjectData{

	public:
		C_RmmvProjectData();
		~C_RmmvProjectData();
		
	//-----------------------------------
	//----����
	protected:
		QString name;				//������
		QString version;			//���̰汾
		QString path;				//���̸�·��
	public:
												//���� - ���������ļ�
												//		��˵�������ļ�������Game.rpgproject�ļ���ȫ·����
		void initFromFile(QString full_filePath);
												//���� - ��ȡ��������
												//		��˵������index.html�е������������ơ�
		QString getName();
												//���� - ��ȡ���̰汾
		QString getVersion();
												//���� - ��ȡ���̸�·��
												//		��˵���������̸�·��������"C:/aaa/�������ʾ��"��
		QString getRootPath();
												//���� - �жϹ����Ƿ����
		bool isProjectExist();

	//-----------------------------------
	//----��ݲ���
	public:
												//��ݲ��� - �����ļ�ѡ�� ��ȡ��������
		static C_RmmvProjectData callRmmvSelectDialog();

	//-----------------------------------
	//----������
	public:
												//���ж�
		bool isNull();
												//ʵ���� -> QJsonObject
		QJsonObject getJsonObject();
												//QJsonObject -> ʵ����
		void setJsonObject(QJsonObject obj);
												//���������
		const bool operator== (const C_RmmvProjectData& a)const;
};
