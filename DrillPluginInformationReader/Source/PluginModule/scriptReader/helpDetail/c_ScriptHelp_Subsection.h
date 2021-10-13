#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-�½� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_SubsectionPage{

	public:
		C_ScriptHelp_SubsectionPage();
		~C_ScriptHelp_SubsectionPage();

	//-----------------------------------
	//----����
	public:
		QString title;				//�½ڱ���
		QStringList context;		//�����б�

};
/*
-----==========================================================-----
		�ࣺ		��������-�ֶ�˵�� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Subsection{

	public:
		C_ScriptHelp_Subsection();
		~C_ScriptHelp_Subsection();

	//-----------------------------------
	//----����
	protected:
		QStringList main_list;							//������˵��
		QList<C_ScriptHelp_SubsectionPage> page_list;	//�½��б�
	public:
								//���� - ���ж�
		bool isNull();
								//���� - ��ȡ������
		QStringList getMainContext();
								//���� - ��ȡ�½ڱ���
		QStringList getAllTitle();
								//���� - ��ȡ�½ڣ����ݱ��⣩
		C_ScriptHelp_SubsectionPage getPageByTitle(QString title);
								//���� - ��ȡ�½����ݣ����ݱ��⣩
		QStringList getPageContextByTitle(QString title);
	public:
								//���� - ����������
		void setMainContext(QStringList mainContext_list);
								//���� - ����½�
		void readNextPage(QString page_context); 
};
