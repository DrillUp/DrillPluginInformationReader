#include "stdafx.h"
#include "c_ScriptHelp_Performance.h"


/*
-----==========================================================-----
		�ࣺ		��������-������� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Performance::C_ScriptHelp_Performance(){
	this->performance = QStringList();
	this->note = QStringList();
}
C_ScriptHelp_Performance::~C_ScriptHelp_Performance(){
}

/*-------------------------------------------------
		��ȡ�� - ��ȡ ������� �ַ���
*/
void C_ScriptHelp_Performance::readPerformance(QString performance_context){

	//...
}


//���� - �Ƿ������
bool C_ScriptHelp_Performance::isHighCost(){
	return false;
}
//���� - �Ƿ�������
bool C_ScriptHelp_Performance::isMiddleCost(){
	return false;
}
//���� - �Ƿ������
bool C_ScriptHelp_Performance::isLowCost(){
	return false;
}