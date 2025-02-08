#ifndef P_ScriptHelp_Knowledge_H
#define P_ScriptHelp_Knowledge_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Knowledge.h"

#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelp_Knowledge.h"

/*
-----==========================================================-----
		类：		指令 控件块.h
		作者：		drill_up
		所属模块：	插件模块
		
		主功能：	显示控件信息的结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_ScriptHelp_Knowledge : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Knowledge(QWidget *parent = 0);
		~P_ScriptHelp_Knowledge();
		
	//-----------------------------------
	//----控件
	public:
		QList<QLabel*> m_labelTank;
	public slots: 
										//控件 - 清空全部内容
		void clearAllChild();
										//控件 - 链接被点击
		void linkClicked_docs(QString data);

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据
		void setData(C_ScriptHelp_Knowledge* data);
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Knowledge ui;

};

#endif // P_ScriptHelp_Knowledge_H
