#include "stdafx.h"
#include "c_ScriptDictionary.h"


/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�

		��Ҫ���	> �������Ϊ��js�ű��ж�ȡ�������ݡ�
					  ����js�ű���ʱ�ɱ䣬���Բ�����洢��
-----==========================================================-----
*/
C_ScriptDictionary::C_ScriptDictionary(){
	this->name = "";									  	//�����
	this->param_list = QList<C_ScriptDictionary_Param>(); 	//�����б�
}
C_ScriptDictionary::~C_ScriptDictionary(){
}

/*-------------------------------------------------
		���������
*/
const bool C_ScriptDictionary::operator== (const C_ScriptDictionary& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		ʵ���� -> QJsonObject
*/
QJsonObject C_ScriptDictionary::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	QJsonArray arr_param_list = QJsonArray();
	for (int i = 0; i < this->param_list.count(); i++){ 
		C_ScriptDictionary_Param c_p = this->param_list.at(i);
		arr_param_list.append(c_p.getJsonObject());
	}
	obj.insert("param_list", arr_param_list);

	return obj;
}
/*-------------------------------------------------
		QJsonObject -> ʵ����
*/
void C_ScriptDictionary::setJsonObject(QJsonObject obj){

	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("param_list").isUndefined() == false){
		QJsonArray arr_option = QJsonArray();
		this->param_list = QList<C_ScriptDictionary_Param>();
		for (int i = 0; i < arr_option.count(); i++){ 
			C_ScriptDictionary_Param c_p = C_ScriptDictionary_Param();
			c_p.setJsonObject(arr_option.at(i).toObject());
			this->param_list.append(c_p);
		}
	}
}

