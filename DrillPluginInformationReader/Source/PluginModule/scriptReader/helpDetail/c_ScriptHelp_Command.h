#pragma once
#include <QList>

#include "c_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		�ࣺ		��������-ָ� ԭ����.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е���ָ��������ࡣ
-----==========================================================-----
*/
class C_ScriptHelp_CommandCell{

	public:
		C_ScriptHelp_CommandCell();
		~C_ScriptHelp_CommandCell();
		
	public:
		QString type;		//ָ������
		QString command;	//ָ������
		QString note;		//ָ��󸽼�ע��
};
/*
-----==========================================================-----
		�ࣺ		��������-ָ� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
					
		˵����		ע�⣬ָ���Ϊ�������֣������ݣ���ʾ��ϸ��Ϣ�ã���������������ʾ������Ϣ�ã���
					�������ݿ��Էֱ��ȡ��������ء�
					- ���ݣ�������Ϊ ָ��ȫ�� �� ��ָ��ȫ�ģ��ı��������У���ʾʱ��Ҫ ���� ��
					- ����������ָ��� ���� ���ڸ����ַ��������С�	
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

		QStringList context_note;				//˵���б�
		QString context_command;				//ָ��ȫ��
		QString context_command_old;			//��ָ��ȫ��
	public:
									//���� - ��ȡ����
		QString getGroupFullName();
									//���� - �Ӷ����б��У���ȡָ���ַ����б�
		QStringList getCommandListByObjList(QList<C_ScriptHelp_CommandCell> cell_list);

									//���� - �������� - ��ȡȫ����ǩ
									//		��˵�������� ָ��ȫ�� "���ָ�>xxxx" ���У��г������ı������� \n ���з���
		QStringList getGrid_TagList();
									//���� - �������� - ��ȡȫ��ָ��
		QStringList getGrid_CommandList();
									//���� - �������� - ��ȡȫ������ע��
		QStringList getGrid_NoteList();
									//���� - �������� - ��ȡȫ����ǩ����ȫ���ã�
		QStringList getGrid_OldTagList();
									//���� - �������� - ��ȡȫ��ָ���ȫ���ã�
		QStringList getGrid_OldCommandList();

	//-----------------------------------
	//----����	��ע�⣬���� �¼���ע���ű� ��
	public:
		QList<C_ScriptHelp_CommandCell> command_Available;			//ָ�� - ��Чָ��
		QList<C_ScriptHelp_CommandCell> command_Other;				//ָ�� - ����

		QList<C_ScriptHelp_CommandCell> command_PluginCommand;		//ָ�� - ���ָ��
		QList<C_ScriptHelp_CommandCell> command_EventComment;		//ָ�� - �¼�ע��
		QList<C_ScriptHelp_CommandCell> command_MapNote;			//ָ�� - ��ͼ��ע
		QList<C_ScriptHelp_CommandCell> command_ActorNote;			//ָ�� - ��ɫע��
		QList<C_ScriptHelp_CommandCell> command_EnemyNote;			//ָ�� - ����ע��
		QList<C_ScriptHelp_CommandCell> command_StateNote;			//ָ�� - ״̬ע��
		QList<C_ScriptHelp_CommandCell> command_ItemNote;			//ָ�� - ��Ʒ/����/����ע��
		QList<C_ScriptHelp_CommandCell> command_SkillNote;			//ָ�� - ����ע��
		QList<C_ScriptHelp_CommandCell> command_MoveRoute;			//ָ�� - �ƶ�·��ָ��
		QList<C_ScriptHelp_CommandCell> command_WindowChar;			//ָ�� - �����ַ�
		QList<C_ScriptHelp_CommandCell> command_PluginCommand_old;	//ָ�� - ���ָ��(��)
		QList<C_ScriptHelp_CommandCell> command_EventComment_old;	//ָ�� - �¼�ע��(��)
	public:
									//���� - ��ȡ��Чָ���������ָ�
		QList<C_ScriptHelp_CommandCell> getAllAvailableCommand();
									//���� - ��ȡȫ��ָ��
		QList<C_ScriptHelp_CommandCell> getAllCommand();
									//���� - ����ָ��ָ��ؼ���
		bool hasCommandKeyWord(QString keyWord);
									//���� - ָ�������������ͱ�ǩ��
		QRegExp commandRe_tag();
									//���� - ָ���������򣨸���ע�ͣ�
		QRegExp commandRe_note();
		
	//-----------------------------------
	//----��ȡ��
	public:
									//��ȡ�� - ���ָ��
									//		��˵���������һ���ַ�������ʽ��Ҫ��ָ��ṹ��
									//		��ʾ��1����"���ָ�>ĳ��� : ����[21]   �����ָ������ݽ��ܣ�"
									//		��ʾ��2����"�����ַ���<br>   ���ڱ�ʾ����"
		void addOneRowCommand(QString command_row);

};
/*
-----==========================================================-----
		�ࣺ		��������-ָ�� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
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
								//���� - ��ȡȫ��ָ�� - �����ַ�
		QStringList getAllCommand_WindowChar();
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
								//���� - ����ָ��ָ��ؼ��� - �����ַ�
		bool hasCommandKeyWord_WindowChar(QString keyWord);
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
	protected:
								//��ȡ�� - ��ȡĬ�Ϲؼ���
		QString getOldKeyword();

};
