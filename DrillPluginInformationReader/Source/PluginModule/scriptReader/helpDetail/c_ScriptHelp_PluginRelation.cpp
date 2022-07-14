#include "stdafx.h"
#include "c_ScriptHelp_PluginRelation.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��������-��չ�� ������.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_PluginRelationGroup::C_ScriptHelp_PluginRelationGroup(){
	this->title = "";
	this->plugin_context = QStringList();
}
C_ScriptHelp_PluginRelationGroup::~C_ScriptHelp_PluginRelationGroup(){
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_ScriptHelp_PluginRelationGroup::isNull(){
	return this->title == "" || this->plugin_context.count() == 0;
}
/*-------------------------------------------------
		���� - ����
*/
bool C_ScriptHelp_PluginRelationGroup::isBaseOn(){
	return this->title == "����";
}
/*-------------------------------------------------
		���� - �ɱ���չ/����չ
*/
bool C_ScriptHelp_PluginRelationGroup::isBeingExtend(){
	return this->title == "�ɱ���չ" || this->title == "����չ";
}
/*-------------------------------------------------
		���� - ��������/������
*/
bool C_ScriptHelp_PluginRelationGroup::isEffectTo(){
	return this->title == "��������" || this->title == "������";
}
/*-------------------------------------------------
		���� - ��������
*/
bool C_ScriptHelp_PluginRelationGroup::isOther(){
	if (this->isBaseOn()){ return false; }
	if (this->isBeingExtend()){ return false; }
	if (this->isEffectTo()){ return false; }
	return true;
}

/*
-----==========================================================-----
		�ࣺ		��������-�����չ ������.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_PluginRelation::C_ScriptHelp_PluginRelation(){
	this->context = QStringList();
	this->group_list = QList<C_ScriptHelp_PluginRelationGroup>();
}
C_ScriptHelp_PluginRelation::~C_ScriptHelp_PluginRelation(){
}

/*-------------------------------------------------
		���� - ��ȡ������
*/
QStringList C_ScriptHelp_PluginRelation::getMainContext(){
	return this->context;
}
/*-------------------------------------------------
		���� - ��ȡ ���� �Ĳ����Ϣ
*/
QStringList C_ScriptHelp_PluginRelation::getContextByBaseOn(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isBaseOn()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡ �ɱ���չ �Ĳ����Ϣ
*/
QStringList C_ScriptHelp_PluginRelation::getContextByBeingExtend(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isBeingExtend()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡ �������� �Ĳ����Ϣ
*/
QStringList C_ScriptHelp_PluginRelation::getContextByEffectTo(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isEffectTo()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡ ���� �����Ϣ
*/
QStringList C_ScriptHelp_PluginRelation::getContextByOther(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_PluginRelationGroup group = this->group_list.at(i);
		if (group.isOther()){
			result_list.append(group.plugin_context);
		}
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_ScriptHelp_PluginRelation::isNull(){
	return this->context.count() == 0 && this->group_list.count() == 0;
}


/*-------------------------------------------------
		��ȡ�� - ��ȡ �����չ �ַ���
*/
void C_ScriptHelp_PluginRelation::readPluginRelation(QString relation_context){
	QStringList context_list = relation_context.split(QRegExp("[\n\r]+"));
	TTool::_QStringList_clearEmptyRows_(&context_list);

	// > ������
	int i_context = 0;
	for (int i = 0; i < context_list.count(); i++){
		QString data = context_list.at(i);
		if (data.at(0) != ' ' && data.count() <= 5){	//���򵥴ֱ�������5���ֵ�����⣩
			i_context = i;		//����������ʱ��ֹ��
			break;
		}else{
			this->context.append(data);
		}
	}

	// > ��չ��
	C_ScriptHelp_PluginRelationGroup cur_group = C_ScriptHelp_PluginRelationGroup();
	for (int i = i_context; i < context_list.count(); i++){
		QString data = context_list.at(i);

		// > ��չ�����
		if ( data.at(0) != ' ' && data.count() <= 5 ){

			if (cur_group.isNull() == false){
				this->group_list.append(cur_group);
			}

			cur_group = C_ScriptHelp_PluginRelationGroup();
			cur_group.title = data.replace(QRegExp("[:��]"), "");
		
		// > ��չ������
		}else{
			data = data.trimmed().replace(QRegExp("^\\-[ ]+"), "��");
			cur_group.plugin_context.append(data);
		}
	}
	if (cur_group.isNull() == false){
		this->group_list.append(cur_group);
	}
}
