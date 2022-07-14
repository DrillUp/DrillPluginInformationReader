#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-��չ�� ������.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_PluginRelationGroup{

	public:
		C_ScriptHelp_PluginRelationGroup();
		~C_ScriptHelp_PluginRelationGroup();

	//-----------------------------------
	//----����
	public:
		QString title;					//����⣨���ͣ�
		QStringList plugin_context;		//���˵��
	public:
								//���� - ���ж�
		bool isNull();
								//���� - ���� ����
		bool isBaseOn();
								//���� - ���� �ɱ���չ/����չ
		bool isBeingExtend();
								//���� - ���� ��������/������
		bool isEffectTo();
								//���� - ��������
		bool isOther();
};

/*
-----==========================================================-----
		�ࣺ		��������-�����չ ������.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_PluginRelation{

	public:
		C_ScriptHelp_PluginRelation();
		~C_ScriptHelp_PluginRelation();

	//-----------------------------------
	//----����
	protected:
		QStringList context;								//�����չ - ������˵��
		QList<C_ScriptHelp_PluginRelationGroup> group_list;	//�����չ - ��չ��
	public:
								//���� - ��ȡ������
		QStringList getMainContext();
								//���� - ��ȡ ���� �Ĳ����Ϣ
		QStringList getContextByBaseOn();
								//���� - ��ȡ �ɱ���չ �Ĳ����Ϣ
		QStringList getContextByBeingExtend();
								//���� - ��ȡ �������� �Ĳ����Ϣ
		QStringList getContextByEffectTo();
								//���� - ��ȡ ���� �����Ϣ
		QStringList getContextByOther();
								//���� - ���ж�
		bool isNull();

	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ �����չ �ַ���
		void readPluginRelation(QString relation_context);

};
