#pragma once
#include <QList>

#include "c_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		�ࣺ		��������-֪ʶ�� ������.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
					
		˵����		������Ϊ ָ�� �Ķ��ⲹ�����ݡ�
-----==========================================================-----
*/
class C_ScriptHelp_KnowledgeGroup{

	public:
		C_ScriptHelp_KnowledgeGroup();
		~C_ScriptHelp_KnowledgeGroup();

	//-----------------------------------
	//----����
	public:
		QString group_name;					//�����ƣ���Ϊ�գ�
		QStringList context_data;			//�����б�
		QStringList context_note;			//˵���б�

};
/*
-----==========================================================-----
		�ࣺ		��������-ָ�� ������.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Knowledge{

	public:
		C_ScriptHelp_Knowledge();
		~C_ScriptHelp_Knowledge();

	//-----------------------------------
	//----����
	protected:
		QList<C_ScriptHelp_KnowledgeGroup> group_list;	//ָ��б�
	public:
								//���� - ���ж�
		bool isNull();
								//���� - ָ��б�
		QList<C_ScriptHelp_KnowledgeGroup> getGroupList();

	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ�µ�ָ��ַ���
		void readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs);

};
