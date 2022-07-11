#include "stdafx.h"
#include "c_ScriptHelp_EffectScope.h"

#include "Source/PluginModule/const/s_PluginConstValue.h"

/*
-----==========================================================-----
		�ࣺ		��������-������ ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_EffectScope::C_ScriptHelp_EffectScope(){
	this->scope_list = QStringList();
	this->comments = "";
}
C_ScriptHelp_EffectScope::~C_ScriptHelp_EffectScope(){
}

/*-------------------------------------------------
		���� - �������ڵ�ͼ����
*/
bool C_ScriptHelp_EffectScope::isEnableSenceMap(){
	return this->scope_list.contains(S_PluginConstValue::getInstance()->getSceneName_Map());
}
/*-------------------------------------------------
		���� - ��������ս������
*/
bool C_ScriptHelp_EffectScope::isEnableSenceBattle(){
	return this->scope_list.contains(S_PluginConstValue::getInstance()->getSceneName_Battle());
}
/*-------------------------------------------------
		���� - �������ڲ˵�����
*/
bool C_ScriptHelp_EffectScope::isEnableSenceMenu(){
	return this->scope_list.contains(S_PluginConstValue::getInstance()->getSceneName_Menu());
}
/*-------------------------------------------------
		���� - ����������������Ľ���
*/
QStringList C_ScriptHelp_EffectScope::getOtherSence(){
	QStringList result = QStringList();
	for (int i = 0; i < this->scope_list.count(); i++){
		QString data = this->scope_list.at(i);
		if (data == S_PluginConstValue::getInstance()->getSceneName_Map()){ continue; }
		if (data == S_PluginConstValue::getInstance()->getSceneName_Battle()){ continue; }
		if (data == S_PluginConstValue::getInstance()->getSceneName_Menu()){ continue; }
		result.append(data);
	}
	return result;
}

