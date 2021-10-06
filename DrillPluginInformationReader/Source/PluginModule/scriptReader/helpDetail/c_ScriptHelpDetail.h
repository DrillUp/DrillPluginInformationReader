#pragma once
#include <QList>
#include <QJsonObject>

#include "c_ScriptHelp_EffectScope.h"
#include "c_ScriptHelp_PluginRelation.h"
#include "c_ScriptHelp_Src.h"
#include "c_ScriptHelp_Docs.h"
#include "c_ScriptHelp_Subsection.h"
#include "c_ScriptHelp_Command.h"
#include "c_ScriptHelp_Performance.h"

/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.h
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_ScriptHelpDetail{

	public:
		C_ScriptHelpDetail();
		~C_ScriptHelpDetail();
		
	//-----------------------------------
	//----��������
	protected:
		QString name;				//��������ļ�����
		QString help;				//������Ϣ��@help��
	public:
									//���� - ���ò����
		void setName(QString name);
									//���� - ���ð�����Ϣ
		void setHelpContext(QString help);
									//���� - ��ȡ�����
		QString getName();
									//���� - ��ȡ������Ϣ
		QString getHelpContext();
	private:
									//˽�� - ������Ϣ��ʼ��
		void initHelpContext();

	//-----------------------------------
	//----��������
	protected:
		C_ScriptHelp_EffectScope* m_effectScope;		//������
		C_ScriptHelp_PluginRelation* m_pluginRelation;	//�����չ
		C_ScriptHelp_Src* m_src;						//��Դ·��
		C_ScriptHelp_Docs* m_docs;						//����ĵ�
		C_ScriptHelp_Subsection* m_subsection;			//�ֶ�˵��
		C_ScriptHelp_Command* m_command;				//ָ��
		C_ScriptHelp_Performance* m_performance;		//�������
	public:
									//���� - ��ȡ������
		C_ScriptHelp_EffectScope* getEffectScope();
									//���� - ��ȡ�����չ
		C_ScriptHelp_PluginRelation* getPluginRelation();
									//���� - ��ȡ��Դ·��
		C_ScriptHelp_Src* getSrc();
									//���� - ��ȡ����ĵ�
		C_ScriptHelp_Docs* getDocs();
									//���� - ��ȡ�ֶ�˵��
		C_ScriptHelp_Subsection* getSubsection();
									//���� - ��ȡָ��
		C_ScriptHelp_Command* getCommand();
									//���� - ��ȡ�������
		C_ScriptHelp_Performance* getPerformance();

	protected:
									//˽�� - Ѱ���ĵ�����
									//		��˵�������ĵ����� docx �� xlsx������ǰ����Ҫ�ո�����ţ����ʽ"xxx.docx"�� xxxx xxx.docx��
		QStringList findDocsNameList(QString context);

	//-----------------------------------
	//----������
	public:
										//���ж�
		bool isNull();
										//���������
		const bool operator== (const C_ScriptHelpDetail& a)const;
										//ʵ���� -> QJsonObject
		QJsonObject getJsonObject();
										//QJsonObject -> ʵ����
		void setJsonObject(QJsonObject obj);
};
