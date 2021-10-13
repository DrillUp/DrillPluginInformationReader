#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-ָ� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_CommandGroup{

	public:
		C_ScriptHelp_CommandGroup();
		~C_ScriptHelp_CommandGroup();

	//-----------------------------------
	//----����
	public:
		QString group_name;			//�����ƣ���Ϊ�գ�
		bool is_important;			//�Ƿ�Ϊ��������
		QStringList context;		//�����б�

		QStringList command_PluginCommand;		//ָ�� - ���ָ��
		QStringList command_PluginCommand_old;	//��ָ�� - ���ָ��
		QStringList command_EventComment;		//ָ�� - �¼�ע��
		QStringList command_EventComment_old;	//��ָ�� - �¼�ע��
		QStringList command_EventNote;			//ָ�� - �¼���ע
		QStringList command_MapNote;			//ָ�� - ��ͼ��ע
		QStringList command_ActorNote;			//ָ�� - ��ɫ��ע
		QStringList command_EnemyNote;			//ָ�� - ���˱�ע
		
};
/*
-----==========================================================-----
		�ࣺ		��������-ָ�� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Command{

	public:
		C_ScriptHelp_Command();
		~C_ScriptHelp_Command();

	//-----------------------------------
	//----����
	protected:
		QList<C_ScriptHelp_CommandGroup> group_list;	//ָ��б�
	public:
								//���� - ���ж�
		bool isNull();
	public:
								//���� - ��ȡ�µ�ָ��ַ���
		void readNextGroup(QString group_context); 
};
