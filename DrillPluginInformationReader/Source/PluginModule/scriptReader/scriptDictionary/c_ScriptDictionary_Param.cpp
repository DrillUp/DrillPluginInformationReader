#include "stdafx.h"
#include "C_ScriptDictionary_Param.h"


/*
-----==========================================================-----
		�ࣺ		�����ܲ��� ʵ����.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		�����Ĳ���ʶ��
-----==========================================================-----
*/
C_ScriptDictionary_Param::C_ScriptDictionary_Param(){
	this->name = "";				//��������@param��
	this->parent = "";				//������������@parent��
	this->type = "";				//�������ͣ�@type��
	this->desc = "";				//����������@desc��
	this->default_ = "";			//����Ĭ��ֵ��@default��

	this->min = -1;					//��������-������Сֵ��@min��
	this->max = -1;					//��������-�������ֵ��@max��
	this->on = "";					//��������-�����ı���@on��
	this->off = "";					//��������-�����ı���@off��
	this->option = QStringList(); 	//��������-����������ݣ�@option��
	this->require = -1;				//��������-�ļ���@require��
	this->dir = "";					//��������-�ļ���@dir��
}
C_ScriptDictionary_Param::~C_ScriptDictionary_Param(){
}
/*-------------------------------------------------
		���������
*/
const bool C_ScriptDictionary_Param::operator== (const C_ScriptDictionary_Param& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		ʵ���� -> QJsonObject
*/
QJsonObject C_ScriptDictionary_Param::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("parent", this->parent);
	obj.insert("type", this->type);
	obj.insert("desc", this->desc);
	obj.insert("default_", this->default_);

	obj.insert("min", this->min);
	obj.insert("max", this->max);
	obj.insert("on", this->on);
	obj.insert("off", this->off);
	QJsonArray arr_option = QJsonArray();
	for (int i = 0; i < this->option.count(); i++){ 
		arr_option.append(this->option.at(i)); 
	}
	obj.insert("option", arr_option);
	obj.insert("require", this->require);
	obj.insert("dir", this->dir);

	return obj;
}
/*-------------------------------------------------
		QJsonObject -> ʵ����
*/
void C_ScriptDictionary_Param::setJsonObject(QJsonObject obj){

	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("parent").isUndefined() == false){ this->parent = obj.value("parent").toString(); }
	if (obj.value("type").isUndefined() == false){ this->type = obj.value("type").toString(); }
	if (obj.value("desc").isUndefined() == false){ this->desc = obj.value("desc").toString(); }
	if (obj.value("default_").isUndefined() == false){ this->default_ = obj.value("default_").toString(); }

	if (obj.value("min").isUndefined() == false){ this->min = obj.value("min").toInt(); }
	if (obj.value("max").isUndefined() == false){ this->max = obj.value("max").toInt(); }
	if (obj.value("on").isUndefined() == false){ this->on = obj.value("on").toString(); }
	if (obj.value("off").isUndefined() == false){ this->off = obj.value("off").toString(); }
	if (obj.value("option").isUndefined() == false){
		QJsonArray arr_option = QJsonArray();
		this->option = QStringList();
		for (int i = 0; i < arr_option.count(); i++){ this->option.append(arr_option.at(i).toString()); }
	}
	if (obj.value("require").isUndefined() == false){ this->require = obj.value("require").toInt(); }
	if (obj.value("dir").isUndefined() == false){ this->dir = obj.value("dir").toString(); }
}
