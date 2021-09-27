#include "stdafx.h"
#include "c_ScriptAnnotation.h"

#include "helpDetail/c_ScriptHelpDetail.h"
#include "scriptDictionary/c_ScriptDictionary.h"

/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.cpp
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�
					����������ĳ�ʼ��ͨ����ȡ����ֵ����ɡ���
					
		ע�⣺		> �������Ϊ��js�ű��ж�ȡ�������ݡ�
					  ����js�ű���ʱ�ɱ䣬���Բ�����洢��
-----==========================================================-----
*/
C_ScriptAnnotation::C_ScriptAnnotation(){
	this->name = "";					//��������ļ�����
	this->plugindesc = "";				//���������@plugindesc��
	this->author = "";					//���ߣ�@author��
	this->helpDetail = nullptr;		 	//������Ϣ��@help + �������ݣ�
	this->dictionary = nullptr; 		//�����ֵ䣨@paramȫ�����ݣ�
}
C_ScriptAnnotation::~C_ScriptAnnotation(){
}


//���� - ��ȡ��������ļ�����
QString C_ScriptAnnotation::getName(){ return this->name; }
//���� - ��ȡ���������@plugindesc��
QString C_ScriptAnnotation::getPlugindesc(){ return this->plugindesc; }
//���� - ��ȡ���ߣ�@author��
QString C_ScriptAnnotation::getAuthor(){ return this->author; }
//���� - ��ȡ������Ϣȫ�ģ�@help��
QString C_ScriptAnnotation::getHelp(){
	if (this->helpDetail == nullptr){ return ""; }
	return this->helpDetail->help;
}
//���� - �Ƿ�Ϊ��������������
bool C_ScriptAnnotation::isCompleted(){
	if (this->helpDetail == nullptr){ return false; }
	if (this->dictionary == nullptr){ return false; }
	return true;
}
//���� - ������Ϣ����
C_ScriptHelpDetail* C_ScriptAnnotation::getScriptHelpDetail(){ return this->helpDetail; }
//���� - �����ֵ�����
C_ScriptDictionary* C_ScriptAnnotation::getScriptDictionary(){ return this->dictionary; }

//���� - ��ȡ�汾��������� ��ȡ�Σ�
QString C_ScriptAnnotation::getPlugindesc_version(){
	if (this->plugindesc.isEmpty()){ return ""; }			//�����ݷ����Ž�ȡ���ݣ�
	QString data = this->plugindesc.trimmed();
	if (data.at(0) != '[' && data.at(0) != '(' && data.at(0) != '��' && data.at(0) != 'v'){ return ""; }
	QStringList data_list = this->plugindesc.split("]");
	if (data_list.count() < 2){ return ""; }
	return data_list.at(0) + "]";
}
//���� - ��ȡ���ͣ�������� ��ȡ�Σ�
QString C_ScriptAnnotation::getPlugindesc_type(){
	QStringList data_list = this->plugindesc.split(" - ");	//��ȡ��ܵ�������ݣ�
	if (data_list.count() < 2){ return ""; }
	QStringList data_list2 = data_list.at(0).trimmed().split(QRegExp("[ \\]\\)]+"));
	return data_list2.last();
}
//���� - ��ȡ��������������� ��ȡ�Σ�
QString C_ScriptAnnotation::getPlugindesc_name(){
	QStringList data_list = this->plugindesc.split(" ");
	return data_list.last();
}


//���� - ���ò�������ļ�����
void C_ScriptAnnotation::setName(QString name){ this->name = name; }
//���� - ���ò��������@plugindesc��
void C_ScriptAnnotation::setPlugindesc(QString plugindesc){ this->plugindesc = plugindesc; }
//���� - �������ߣ�@author��
void C_ScriptAnnotation::setAuthor(QString author){ this->author = author; }
//���� - ���ð�����Ϣ����
void C_ScriptAnnotation::setScriptHelpDetail(C_ScriptHelpDetail* helpDetail){ this->helpDetail = helpDetail; }
//���� - ���ò����ֵ�����
void C_ScriptAnnotation::setScriptDictionary(C_ScriptDictionary* dictionary){ this->dictionary = dictionary; }


/*-------------------------------------------------
		���ж�
*/
bool C_ScriptAnnotation::isNull(){
	return this->name == "";
}
/*-------------------------------------------------
		���������
*/
const bool C_ScriptAnnotation::operator== (const C_ScriptAnnotation& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		ʵ���� -> QJsonObject
*/
QJsonObject C_ScriptAnnotation::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("plugindesc", this->plugindesc);
	obj.insert("author", this->author);
	if (this->helpDetail != nullptr){ obj.insert("helpDetail", this->helpDetail->getJsonObject()); }
	if (this->dictionary != nullptr){ obj.insert("dictionary", this->dictionary->getJsonObject()); }	
	return obj;
}
/*-------------------------------------------------
		QJsonObject -> ʵ����
*/
void C_ScriptAnnotation::setJsonObject(QJsonObject obj){
	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("plugindesc").isUndefined() == false){ this->plugindesc = obj.value("plugindesc").toString(); }
	if (obj.value("author").isUndefined() == false){ this->author = obj.value("author").toString(); }

	if (obj.value("helpDetail").isUndefined() == false){ 
		this->helpDetail = new C_ScriptHelpDetail();
		this->helpDetail->setJsonObject(obj.value("helpDetail").toObject());
	}
	if (obj.value("dictionary").isUndefined() == false){
		this->dictionary = new C_ScriptDictionary();
		this->dictionary->setJsonObject(obj.value("dictionary").toObject());
	}
}
