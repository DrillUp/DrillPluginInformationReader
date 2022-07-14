#pragma once
#include <QJsonObject>


/*
-----==========================================================-----
		�ࣺ		��� ����ֵ.h
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���г���ֵ������ֱ�ӻ�ȡ��
					����ϸ��.cpp��
-----==========================================================-----
*/
class S_Const_PluginValue{

	public:
		S_Const_PluginValue();
		~S_Const_PluginValue();
		static S_Const_PluginValue* cur_instance;		//����
		static S_Const_PluginValue* getInstance();		//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		
	//-----------------------------------
	//----���泣��
	protected:
		QList<QString> m_sceneNameList;					//��������
		QList<QList<QString>> m_sceneKeyMatrix;			//����ؼ���
	public:
									//��ȡ - �������ƣ�ȫ����
		QStringList getSceneName_All();
									//��ȡ - �������� - ��ͼ����
		QString getSceneName_Map();
									//��ȡ - �������� - ս������
		QString getSceneName_Battle();
									//��ȡ - �������� - �˵�����
		QString getSceneName_Menu();
									//��ȡ - �������� - ��������
		QStringList getSceneName_Other();
									//��ȡ - �������ƣ����ݽ���ؼ��֣�
		QString getSceneName_BySceneKey(QString sceneKey);

									//��ȡ - ����ؼ��֣�ȫ����
		QStringList getSceneKey_All();
									//��ȡ - ����ؼ��֣����ݽ������ƣ�
		QStringList getSceneKey_ByName(QString scene_name);
};
