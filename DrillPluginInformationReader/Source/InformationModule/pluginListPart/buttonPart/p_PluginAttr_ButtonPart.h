#ifndef P_PluginAttr_ButtonPart_H
#define P_PluginAttr_ButtonPart_H

#include <QtWidgets>
#include "ui_P_PluginAttr_ButtonPart.h"

#include "w_PluginAttrComment.h"

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
		P_PluginAttr_ButtonPart(W_PluginAttrComment* w,QWidget *parent = 0);
		~P_PluginAttr_ButtonPart();

	//-----------------------------------
	//----控件
	protected:
		QString m_pluginName;
		W_PluginAttrComment* m_w_PluginAttrComment;	//控制的窗口
	public slots:
										//控件 - 设置当前插件名
		void setPluginName(QString pluginName);
										//控件 - 获取当前插件名
		QString getPluginName();
										//控件 - 根据属性显示按钮
		void refreshBtnVisible();
										//控件 - 按钮
		void btn_word();
		void btn_src();
		void btn_highConsumption();
		void btn_hasTool();
		void btn_foreignKey();
										//控件 - 全部隐藏
		void hideAll();
		
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
