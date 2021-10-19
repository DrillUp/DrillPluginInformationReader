#pragma once
#include <QList>

#include "c_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		�ࣺ		��������-���� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�еĽ������ݡ�
					����ͷ"========"����ļ������ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_SubsectionHeader{

	public:
		C_ScriptHelp_SubsectionHeader();
		~C_ScriptHelp_SubsectionHeader();

	//-----------------------------------
	//----����
	public:
		QString introduction;		//���
		QString package;			//���֧����ʾ
		QStringList condition;		//��Ҫ�����б�
};

/*
-----==========================================================-----
		�ࣺ		��������-�½� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
					��"----�趨ע������"�����С�ֶ����ݡ�
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
					���ۺ� ��������� �� "������"��������ݵ㡿
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
		C_ScriptHelp_SubsectionHeader header;			//��������
		QStringList main_list;							//������˵��
		QList<C_ScriptHelp_SubsectionPage> page_list;	//�½��б�
	public:
								//���� - ��ȡ������
		QStringList getMainContext();
								//���� - ��ȡ��������
		C_ScriptHelp_SubsectionHeader getHeader();
								//���� - ���ж�
		bool isNull();
								//���� - ��ȡ�½ڱ���
		QStringList getAllTitle();
								//���� - ��ȡ�½ڣ����ݱ��⣩
		C_ScriptHelp_SubsectionPage getPageByTitle(QString title);
								//���� - ��ȡ�½����ݣ����ݱ��⣩
		QStringList getPageContextByTitle(QString title);

	//-----------------------------------
	//----��ȡ��
	public:
								//��ȡ�� - ��ȡ ���� ����
		void readHeader(QString header_context);
								//��ȡ�� - ��ȡ �ֶ�˵�� ����
		void readSubsection(QString subsection_context, C_ScriptHelp_Docs* c_docs);
	protected:
								//��ȡ�� - ���һ���½�
		void readNextPage(QString page_context); 
};
