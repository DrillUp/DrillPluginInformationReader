#include "stdafx.h"
#include "c_ScriptHelp_Subsection.h"


/*
-----==========================================================-----
		类：		帮助数据-分段说明 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Subsection::C_ScriptHelp_Subsection(){
	this->m_effectScope = QStringList();
	this->m_effectScopeComments = "";
}
C_ScriptHelp_Subsection::~C_ScriptHelp_Subsection(){
}


