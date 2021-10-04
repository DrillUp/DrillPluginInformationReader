#include "stdafx.h"
#include "c_ScriptHelp_Docs.h"


/*
-----==========================================================-----
		�ࣺ		��������-����ĵ� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Docs::C_ScriptHelp_Docs(){
	this->main_docx = QStringList();
	this->relative_docx = QStringList();
}
C_ScriptHelp_Docs::~C_ScriptHelp_Docs(){
}

/*-------------------------------------------------
		���� - �����Ҫ�ĵ�
*/
void C_ScriptHelp_Docs::addMainDocx(QString docx){
	if (this->main_docx.contains(docx)){ return; }	//��ȥ�أ�
	if (this->relative_docx.contains(docx)){ return; }
	this->main_docx.append(docx);
}
void C_ScriptHelp_Docs::addMainDocx(QStringList docx_list){
	for (int i = 0; i < docx_list.count(); i++){
		this->addMainDocx(docx_list.at(i));
	}
}
/*-------------------------------------------------
		���� - �������ĵ�
*/
void C_ScriptHelp_Docs::addRelativeDocx(QString docx){
	if (this->main_docx.contains(docx)){ return; }	//��ȥ�أ�
	if (this->relative_docx.contains(docx)){ return; }
	this->relative_docx.append(docx);
}
void C_ScriptHelp_Docs::addRelativeDocx(QStringList docx_list){
	for (int i = 0; i < docx_list.count(); i++){
		this->addRelativeDocx(docx_list.at(i));
	}
}
/*-------------------------------------------------
		���� - �Ƿ����ĵ�
*/
bool C_ScriptHelp_Docs::hasAnyDocx(){
	if (this->main_docx.count() > 0){ return true; }
	if (this->relative_docx.count() > 0){ return true; }
	return false;
}

