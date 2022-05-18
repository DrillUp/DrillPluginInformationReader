#ifndef P_PluginDetailOrgContextPart_H
#define P_PluginDetailOrgContextPart_H

#include <QtWidgets>
#include "ui_P_PluginDetailOrgContextPart.h"

/*
-----==========================================================-----
		类：		原文展开 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	原文展开的编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_PluginDetailOrgContextPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginDetailOrgContextPart(QWidget *parent = 0);
		~P_PluginDetailOrgContextPart();

	//-----------------------------------
	//----控件
	public slots:
										//控件 - 设置文本
		void setContext(QString context);

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_PluginDetailOrgContextPart ui;

};

#endif // P_PluginDetailOrgContextPart_H
