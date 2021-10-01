#ifndef P_InformationPart_H
#define P_InformationPart_H

#include <QtWidgets>
#include "ui_P_InformationPart.h"
#include "Source/Utils/widgetForm/foldableTabWindow/p_FoldableTabRelater.h"

/*
-----==========================================================-----
		类：		信息模块 主编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_PluginListPart;
class P_PluginDetailPart;
class P_CommandSearcherPart;
class P_InformationPart : public QWidget
{
	Q_OBJECT

	public:
		P_InformationPart(QWidget *parent = 0);
		~P_InformationPart();
		
	//-----------------------------------
	//----大控件
	public:
		P_FoldableTabRelater* m_p_FoldableTabRelater;	//可折叠选项卡
		P_PluginListPart* m_p_pluginListPart;
		P_PluginDetailPart* m_p_pluginDetailPart;
		P_CommandSearcherPart* m_p_commandSearcherPart;

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_InformationPart ui;

};

#endif // P_InformationPart_H
