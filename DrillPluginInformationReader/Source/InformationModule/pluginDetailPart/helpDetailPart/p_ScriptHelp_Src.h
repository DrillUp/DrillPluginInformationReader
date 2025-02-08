#ifndef P_ScriptHelp_Src_H
#define P_ScriptHelp_Src_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_Src.h"

#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelp_Src.h"

/*
-----==========================================================-----
		类：		资源路径 控件块.h
		作者：		drill_up
		所属模块：	插件模块
		
		主功能：	显示控件信息的结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_ScriptHelp_Src : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_Src(QWidget *parent = 0);
		~P_ScriptHelp_Src();
		
	//-----------------------------------
	//----控件
	public:
		QList<QLabel*> m_labelTank;
	public slots: 
										//控件 - 清空全部子控件
		void clearAllChild();
										//控件 - 链接被点击
		void linkClicked_src(QString data);
										//控件 - 链接"插件清单.xlsx"被点击
		void linkClicked_specific_pluginListing(QString data);

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据
		void setData(C_ScriptHelp_Src* data);
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_ScriptHelp_Src ui;

};

#endif // P_ScriptHelp_Src_H
