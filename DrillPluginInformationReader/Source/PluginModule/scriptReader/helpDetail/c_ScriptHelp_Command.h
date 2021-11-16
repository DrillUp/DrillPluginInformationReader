#pragma once
#include <QList>

#include "c_ScriptHelp_Docs.h"

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
		QString group_name;						//�����ƣ���Ϊ�գ�
		bool is_important;						//�Ƿ�Ϊ��������
		QStringList note_context;				//˵���б�

		QString command_context;				//ָ��ȫ��
												//		��ע�⣬���� �¼���ע���ű� ��
		QStringList command_PluginCommand;		//ָ�� - ���ָ��
		QStringList command_PluginCommand_old;	//ָ�� - ���ָ��(��)
		QStringList command_EventComment;		//ָ�� - �¼�ע��
		QStringList command_EventComment_old;	//ָ�� - �¼�ע��(��)
		QStringList command_MapNote;			//ָ�� - ��ͼ��ע
		QStringList command_ActorNote;			//ָ�� - ��ɫע��
		QStringList command_EnemyNote;			//ָ�� - ����ע��
		QStringList command_StateNote;			//ָ�� - ״̬ע��
		QStringList command_ItemNote;			//ָ�� - ��Ʒ/����/����ע��
		QStringList command_SkillNote;			//ָ�� - ����ע��
		QStringList command_MoveRoute;			//ָ�� - �ƶ�·��ָ��
		QStringList command_Other;				//ָ�� - ����
	public:
									//���� - ���ָ��
		void addOneRowCommand(QString command_row);
									//���� - ��ȡȫ��ָ���������ָ�
		QStringList getAllAvailableCommand();
									//���� - ��ȡȫ��ָ��
		QStringList getAllCommand();
									//���� - ��ȡ����
		QString getGroupFullName();
									//���� - �������� - ��ȡȫ����ǩ
									//		��˵�������� ָ��ȫ�� "���ָ�>xxxx" ���У��г������ı������� \n ���з���
		QStringList getGrid_TagList();
									//���� - �������� - ��ȡȫ��ָ��
		QStringList getGrid_CommandList();

	//-----------------------------------
	//----����
	public:
									//���� - ����ָ��ָ��ؼ���
		bool hasCommandKeyWord(QString keyWord);
									//���� - ָ����������
		QRegExp commandRe();
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
								//���� - ָ��б�
		QList<C_ScriptHelp_CommandGroup> getGroupList();
								//���� - ��ȡȫ��ָ�� - ���ָ��
		QStringList getAllCommand_PluginCommand();
								//���� - ��ȡȫ��ָ�� - ���ָ��(��)
		QStringList getAllCommand_PluginCommandOld();
								//���� - ��ȡȫ��ָ�� - �¼�ע��
		QStringList getAllCommand_EventComment();
								//���� - ��ȡȫ��ָ�� - �¼�ע��(��)
		QStringList getAllCommand_EventCommentOld();
								//���� - ��ȡȫ��ָ�� - ��ͼ��ע
		QStringList getAllCommand_MapNote();
								//���� - ��ȡȫ��ָ�� - ��ɫע��
		QStringList getAllCommand_ActorNote();
								//���� - ��ȡȫ��ָ�� - ����ע��
		QStringList getAllCommand_EnemyNote();
								//���� - ��ȡȫ��ָ�� - ״̬ע��
		QStringList getAllCommand_StateNote();
								//���� - ��ȡȫ��ָ�� - ��Ʒ/����/����ע��
		QStringList getAllCommand_ItemNote();
								//���� - ��ȡȫ��ָ�� - ����ע��
		QStringList getAllCommand_SkillNote();
								//���� - ��ȡȫ��ָ�� - �ƶ�·��ָ��
		QStringList getAllCommand_MoveRoute();
								//���� - ��ȡȫ��ָ�� - ����
		QStringList getAllCommand_Other();
		
	//-----------------------------------
	//----����
	public:
								//���� - ����ָ��ָ��ؼ���
		bool hasCommandKeyWord_All(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ���ָ��
		bool hasCommandKeyWord_PluginCommand(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ���ָ��(��)
		bool hasCommandKeyWord_PluginCommandOld(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - �¼�ע��
		bool hasCommandKeyWord_EventComment(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - �¼�ע��(��)
		bool hasCommandKeyWord_EventCommentOld(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ��ͼ��ע
		bool hasCommandKeyWord_MapNote(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ��ɫע��
		bool hasCommandKeyWord_ActorNote(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ����ע��
		bool hasCommandKeyWord_EnemyNote(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ״̬ע��
		bool hasCommandKeyWord_StateNote(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ��Ʒ/����/����ע��
		bool hasCommandKeyWord_ItemNote(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ����ע��
		bool hasCommandKeyWord_SkillNote(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - �ƶ�·��ָ��
		bool hasCommandKeyWord_MoveRoute(QString keyWord);
								//���� - ����ָ��ָ��ؼ��� - ����
		bool hasCommandKeyWord_Other(QString keyWord);
	protected:
								//˽�� - �жϹؼ���
		bool searchCommandKeyWord(QStringList* command_list, QString keyWord);

	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ�µ�ָ��ַ���
		void readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs);
};
