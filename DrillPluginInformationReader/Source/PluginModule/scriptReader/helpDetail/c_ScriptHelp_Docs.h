#pragma once
#include <QList>


/*
-----==========================================================-----
		�ࣺ		��������-����ĵ� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�ֻ�����ĵ����ƣ�û���ļ��С�
					���ĵ����Ʊ����һ�޶������Ӷ���������ĵ���������·������
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelp_Docs{

	public:
		C_ScriptHelp_Docs();
		~C_ScriptHelp_Docs();

	//-----------------------------------
	//----����
	public:
		QStringList main_docx;		//��Ҫ �ĵ�����
		QStringList relative_docx;	//��� �ĵ�����
	public:
									//���� - ���ж�
		bool isNull();
									//���� - �Ƿ����ĵ�
		bool hasAnyDocx();
									//���� - �����Ҫ�ĵ�����
		void addMainDocx(QString docx);
		void addMainDocx(QStringList docx_list);
									//���� - �������ĵ�����
		void addRelativeDocx(QString docx);
		void addRelativeDocx(QStringList docx_list);
		
	//-----------------------------------
	//----��ȡ��
	public:
									//��ȡ�� - Ѱ���ĵ�����
									//		��˵��1�����ĵ����� docx �� xlsx������ǰ����Ҫ�ո�����ţ����ʽ"xxx.docx"�� xxxx xxx.docx��
									//		��˵��2�����ú���ֻ�Ǹ����ߺ��������صĽ������ѡ���ֶ���ӵ����������С�
		QStringList findDocsNameList(QString context);
};
