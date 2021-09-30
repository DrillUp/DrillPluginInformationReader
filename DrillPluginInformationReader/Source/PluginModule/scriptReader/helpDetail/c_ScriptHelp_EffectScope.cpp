#include "stdafx.h"
#include "c_ScriptHelp_EffectScope.h"


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
	return this->scope_list.contains("��ͼ����");
}
/*-------------------------------------------------
		���� - ��������ս������
*/
bool C_ScriptHelp_EffectScope::isEnableSenceBattle(){
	return this->scope_list.contains("ս������");
}
/*-------------------------------------------------
		���� - �������ڲ˵�����
*/
bool C_ScriptHelp_EffectScope::isEnableSenceMenu(){
	return this->scope_list.contains("�˵�����");
}
/*-------------------------------------------------
		���� - ����������������Ľ���
*/
QStringList C_ScriptHelp_EffectScope::getOtherSence(){
	QStringList result = QStringList();
	for (int i = 0; i < this->scope_list.count(); i++){
		QString data = this->scope_list.at(i);
		if (data == "��ͼ����"){ continue; }
		if (data == "ս������"){ continue; }
		if (data == "�˵�����"){ continue; }
		result.append(data);
	}
	return result;
}

