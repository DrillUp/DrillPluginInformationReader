#ifndef P_ScriptHelp_CommandSearchCell_H
#define P_ScriptHelp_CommandSearchCell_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_CommandSearchCell.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Command.h"

/*
-----==========================================================-----
		类：		指令 控件块.h
		作者：		drill_up
		所属模块：	插件模块
		说明：		显示控件 指令 信息的结构。
					【注意，由于需要反复查询，那么就一定不要用临时new的控件，必须用现成的控件填内容】
					（详细见cpp）
-----==========================================================-----
*/
class P_ScriptHelp_CommandSearchCell : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_CommandSearchCell(QWidget *parent = 0);
		~P_ScriptHelp_CommandSearchCell();
		
		
	//-----------------------------------
	//----控件
	public slots: 
										//控件 - 清空全部内容（不删除控件）
		void clearAllChild();
										//控件 - 链接被点击
		void linkClicked_plugin(QString data);

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据
		void setData(C_ScriptHelp_Command* data, QString plugin_name);
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_ScriptHelp_CommandSearchCell ui;

};

#endif // P_ScriptHelp_CommandSearchCell_H
