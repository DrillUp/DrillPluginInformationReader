#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-������ ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_EffectScope{

	public:
		C_ScriptHelp_EffectScope();
		~C_ScriptHelp_EffectScope();

	//-----------------------------------
	//----����
	public:
		QStringList scope_list;		//�����򣨵�ͼ����/ս������/�˵����棩
		QString comments;			//������˵��
	public:
							//���� - �������ڵ�ͼ����
		bool isEnableSceneMap();
							//���� - ��������ս������
		bool isEnableSceneBattle();
							//���� - �������ڲ˵�����
		bool isEnableSceneMenu();
							//���� - �������ڽ���
		bool isEnableScene(QString scene_name);
							//���� - ��ȡ������
		QStringList getEnabledScene();
							//���� - ����������������Ľ���
		QStringList getOtherScene();

};
