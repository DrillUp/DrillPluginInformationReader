#include "stdafx.h"
#include "c_ScriptHelpDetail.h"


/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.cpp
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�

		��Ҫ���	> �������Ϊ��js�ű��ж�ȡ�������ݡ�
					  ����js�ű���ʱ�ɱ䣬���Բ�����洢��
-----==========================================================-----
*/
C_ScriptHelpDetail::C_ScriptHelpDetail(){
	this->name = "";			 	//��������ļ�����
	this->help = "";				//������Ϣ��@help��

	this->m_effectScope = nullptr;			//������
	this->m_pluginRelation = nullptr;		//�����չ
	this->m_docs = nullptr;					//����ĵ�
	this->m_subsection = nullptr;			//�ֶ�˵��
	this->m_command = nullptr;				//ָ��
	this->m_performance = nullptr;			//�������
}
C_ScriptHelpDetail::~C_ScriptHelpDetail(){
}


/*-------------------------------------------------
		���� - ���ò����
*/
void C_ScriptHelpDetail::setName(QString name){
	this->name = name;
}
/*-------------------------------------------------
		���� - ���ð�����Ϣ
*/
void C_ScriptHelpDetail::setHelpContext(QString help){
	this->help = help;
	this->initHelpContext();
}
/*-------------------------------------------------
		���� - ��ȡ�����
*/
QString C_ScriptHelpDetail::getName(){
	return this->name;
}
/*-------------------------------------------------
		���� - ��ȡ������Ϣ
*/
QString C_ScriptHelpDetail::getHelpContext(){
	return this->help;
}


/*-------------------------------------------------
		˽�� - ������Ϣ��ʼ��
*/
void C_ScriptHelpDetail::initHelpContext(){
	//...
}
/*-------------------------------------------------
		���� - ��ȡ������
*/
C_ScriptHelp_EffectScope* C_ScriptHelpDetail::getEffectScope(){
	return this->m_effectScope;
}
/*-------------------------------------------------
		���� - ��ȡ�����չ
*/
C_ScriptHelp_PluginRelation* C_ScriptHelpDetail::getPluginRelation(){
	return this->m_pluginRelation;
}
/*-------------------------------------------------
		���� - ��ȡ����ĵ�
*/
C_ScriptHelp_Docs* C_ScriptHelpDetail::getDocs(){
	return this->m_docs;
}
/*-------------------------------------------------
		���� - ��ȡ�ֶ�˵��
*/
C_ScriptHelp_Subsection* C_ScriptHelpDetail::getSubsection(){
	return this->m_subsection;
}
/*-------------------------------------------------
		���� - ��ȡָ��
*/
C_ScriptHelp_Command* C_ScriptHelpDetail::getCommand(){
	return this->m_command;
}
/*-------------------------------------------------
		���� - ��ȡ�������
*/
C_ScriptHelp_Performance* C_ScriptHelpDetail::getPerformance(){
	return this->m_performance;
}


/*-------------------------------------------------
		���ж�
*/
bool C_ScriptHelpDetail::isNull(){
	return this->name == "";
}
/*-------------------------------------------------
		���������
*/
const bool C_ScriptHelpDetail::operator== (const C_ScriptHelpDetail& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		ʵ���� -> QJsonObject
*/
QJsonObject C_ScriptHelpDetail::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("help", this->help);
	return obj;
}
/*-------------------------------------------------
		QJsonObject -> ʵ����
*/
void C_ScriptHelpDetail::setJsonObject(QJsonObject obj){

	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("help").isUndefined() == false){ this->help = obj.value("help").toString(); }

}

