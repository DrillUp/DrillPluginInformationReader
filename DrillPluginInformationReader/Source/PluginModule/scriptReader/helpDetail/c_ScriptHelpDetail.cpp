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
}
C_ScriptHelpDetail::~C_ScriptHelpDetail(){
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

