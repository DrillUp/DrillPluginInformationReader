#include "stdafx.h"
#include "c_DesignTipGenerator.h"

/*
-----==========================================================-----
		�ࣺ		���������-��� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		����������Ĳ�����ݡ�
-----==========================================================-----
*/
C_DesignTip::C_DesignTip(){
	this->plugin_name = "";
	this->plugin_desc = "";
	this->page = C_ScriptHelp_SubsectionPage();
}
C_DesignTip::~C_DesignTip(){
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_DesignTip::isNull(){
	return this->plugin_name == "" || this->page.isNull() == 0;
}


/*
-----==========================================================-----
		�ࣺ		���������-������� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������������õ������ݡ�
-----==========================================================-----
*/
C_DesignTipGenerator::C_DesignTipGenerator(){
	this->tip_list = QList<C_DesignTip>();
}
C_DesignTipGenerator::~C_DesignTipGenerator(){
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_DesignTipGenerator::isNull(){
	return this->tip_list.count() == 0;
}