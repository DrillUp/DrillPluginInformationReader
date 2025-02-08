#ifndef P_ScriptHelp_Docs_H
#define P_ScriptHelp_Docs_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Docs.h"

#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		类：		插件文档 控件块.h
		作者：		drill_up
		所属模块：	插件模块
		
		主功能：	显示控件信息的结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_ScriptHelp_Docs : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Docs(QWidget *parent = 0);
		~P_ScriptHelp_Docs();
		
	//-----------------------------------
	//----控件
	public:
		QList<QLabel*> m_labelTank;
	public slots: 
										//控件 - 清除标签
		void clearAllLabel();
										//控件 - 链接被点击
		void linkClicked_docs(QString data);

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据
		void setData(C_ScriptHelp_Docs* data);
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Docs ui;

};

#endif // P_ScriptHelp_Docs_H
