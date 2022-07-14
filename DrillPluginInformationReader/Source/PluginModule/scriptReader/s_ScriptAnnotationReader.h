#pragma once

#include "c_ScriptAnnotation.h"

/*
-----==========================================================-----
		�ࣺ		���ע���ȡ��.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		��ȡjs�ļ��ڵ��������� @��ע�� ���ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/

class S_ScriptAnnotationReader : public QObject
{
	Q_OBJECT

	public:
		S_ScriptAnnotationReader();
		~S_ScriptAnnotationReader();
		static S_ScriptAnnotationReader* cur_manager;			//����
		static S_ScriptAnnotationReader* getInstance();			//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩

	//-----------------------------------
	//----��ȡ
	public:
										//��ȡ - �����������Ҫ��
										//		�����������ļ�����·����"C:/aaa/ccc/DrillTip1.js"��
										//		��˵������ֻ�� ������������ϸ�����ߡ�������Ϣ��
		C_ScriptAnnotation readPlugin_simple(QString file_fullPath);
										//��ȡ - ���������������
										//		�����������ļ�����·����"C:/aaa/ccc/DrillTip1.js"��
										//		��˵�������������ȫ����������Ϣ��
		C_ScriptAnnotation readPlugin_complete(QString file_fullPath);
	
	private:
										//˽�� - ����������Ϣ ��ȡ�� ����
		C_ScriptHelpDetail* readScriptHelpDetail(QString help_context);
										//˽�� - ���������Ϣ ��ȡ�� ����
		C_ScriptDictionary* readScriptDictionary(QString plugin_context);
		
	//-----------------------------------
	//----����
	public:
										//���� - ������
		//QString getContentField(QString plugin_helpContext);
										//���� - �����ļ�
		//QString getContentFiles(QString plugin_helpContext);
};
