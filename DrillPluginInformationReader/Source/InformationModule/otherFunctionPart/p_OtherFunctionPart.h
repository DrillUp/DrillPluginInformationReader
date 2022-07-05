#ifndef P_OtherFunctionPart_H
#define P_OtherFunctionPart_H

#include <QtWidgets>
#include "ui_P_OtherFunctionPart.h"

/*
-----==========================================================-----
		类：		其它功能 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	其它功能的编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_OtherFunctionPart : public QWidget
{
	Q_OBJECT

	public:
		P_OtherFunctionPart(QWidget *parent = 0);
		~P_OtherFunctionPart();
		
	//-----------------------------------
	//----控件
	public slots:
										//控件 - 选择 灵感生成器
		void btn_DesignTipGenerator();
										//控件 - 选择 插件清理器（清理未使用的插件）
		void btn_PluginBatchDelete();
										//控件 - 选择 插件更新器
		void btn_PluginBatchUpdate();
										//控件 - 选择 版本日志
		void btn_VersionLog();
										//控件 - 生成 插件清单
		void btn_ExcelPluginList();
										//控件 - 生成 插件示例位置表
		void btn_ExcelMapPosList();
	signals: 
										//控件 - 选择 灵感生成器
		void selected_DesignTipGenerator();

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_OtherFunctionPart ui;

};

#endif // P_OtherFunctionPart_H
