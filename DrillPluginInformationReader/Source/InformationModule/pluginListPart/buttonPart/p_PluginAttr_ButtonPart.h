#ifndef P_PluginAttr_ButtonPart_H
#define P_PluginAttr_ButtonPart_H

#include <QtWidgets>
#include "ui_P_PluginAttr_ButtonPart.h"

/*
-----==========================================================-----
		类：		插件属性 按钮块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	插件属性显示用的按钮块。
					（详细见cpp）
-----==========================================================-----
*/
class P_PluginAttr_ButtonPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginAttr_ButtonPart(QWidget *parent = 0);
		~P_PluginAttr_ButtonPart();

	//-----------------------------------
	//----控件
	public slots:
										//控件 - 资源按钮
		void btn_src();
		
	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_PluginAttr_ButtonPart ui;

};

#endif // P_PluginAttr_ButtonPart_H
