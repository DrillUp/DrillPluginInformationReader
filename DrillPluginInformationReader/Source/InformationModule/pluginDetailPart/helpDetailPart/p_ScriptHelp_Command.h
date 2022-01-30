#ifndef P_ScriptHelp_Command_H
#define P_ScriptHelp_Command_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Command.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Command.h"

/*
-----==========================================================-----
		类：		指令 控件块.h
		作者：		drill_up
		所属模块：	插件模块
		
		主功能：	显示控件信息的结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_ScriptHelp_Command : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Command(QWidget *parent = 0);
		~P_ScriptHelp_Command();
		
	//-----------------------------------
	//----控件
	public:
		QList<QLabel*> m_labelTank;
		QList<QToolButton*> m_btnTank;
	public slots: 
										//控件 - 清空全部内容
		void clearAllChild();
										//控件 - 链接被点击
		void linkClicked_docs(QString data);
										//控件 - 复制按钮被点击
		void copyBtnClicked();
										//控件 - 刷新颜色（根据指令类型）
		void refreshLabelStyle(QLabel* label);	

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据
		void setData(C_ScriptHelp_Command* data);
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Command ui;

};

#endif // P_ScriptHelp_Command_H
