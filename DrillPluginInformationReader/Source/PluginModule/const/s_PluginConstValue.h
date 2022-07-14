#pragma once
#include <QJsonObject>


/*
-----==========================================================-----
		�ࣺ		��� ����ֵ.h
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���г���ֵ������ֱ�ӻ�ȡ��
-----==========================================================-----
*/
class S_PluginConstValue{

	public:
		S_PluginConstValue();
		~S_PluginConstValue();
		static S_PluginConstValue* cur_instance;		//����
		static S_PluginConstValue* getInstance();		//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		
	//-----------------------------------
	//----���泣��
	protected:
		QList<QString> m_sceneNameList;					//��������
		QList<QList<QString>> m_sceneKeyMatrix;			//����ؼ���
		QList<QList<QString>> m_performanceKeyMatrix;	//���ܹؼ���
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
									//��ȡ - �������ƣ��������ܹؼ��֣�
		QString getSceneName_ByPerformanceWord(QString performanceWord);

									//��ȡ - ����ؼ��֣�ȫ����
		QStringList getSceneKey_All();
									//��ȡ - ����ؼ��֣����ݽ������ƣ�
		QStringList getSceneKey_ByName(QString scene_name);

									//��ȡ - ���ܹؼ��֣�ȫ����
		QStringList getPerformanceWord_All();
									//��ȡ - ���ܹؼ��֣����ݽ������ƣ�
		QStringList getPerformanceWord_ByName(QString scene_name);
									//��ȡ - �̶ȣ��������ܹؼ��֣�
		int getLevel_ByPerformanceWord(QString performanceWord);
};
