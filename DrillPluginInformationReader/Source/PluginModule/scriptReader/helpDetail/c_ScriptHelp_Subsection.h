#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-分段说明 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Subsection{

	public:
		C_ScriptHelp_Subsection();
		~C_ScriptHelp_Subsection();

	//-----------------------------------
	//----数据
	public:
		QStringList m_effectScope;		//作用域（地图界面/战斗界面/菜单界面）
		QString m_effectScopeComments;	//作用域说明

};
