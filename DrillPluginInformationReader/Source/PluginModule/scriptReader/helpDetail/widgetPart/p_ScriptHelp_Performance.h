#ifndef P_ScriptHelp_Performance_H
#define P_ScriptHelp_Performance_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Performance.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Performance.h"

/*
-----==========================================================-----
		类：		插件性能 控件块.h
		作者：		drill_up
		所属模块：	插件模块
		
		主功能：	显示控件信息的结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_ScriptHelp_Performance : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Performance(QWidget *parent = 0);
		~P_ScriptHelp_Performance();
		
	//-----------------------------------
	//----控件
	public slots: 

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据
		void setData(C_ScriptHelp_Performance* data);
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Performance ui;

};

#endif // P_ScriptHelp_Performance_H
