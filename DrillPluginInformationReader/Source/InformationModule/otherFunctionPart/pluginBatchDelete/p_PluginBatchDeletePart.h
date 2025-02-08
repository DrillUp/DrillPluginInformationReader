﻿#ifndef P_PluginBatchDeletePart_H
#define P_PluginBatchDeletePart_H

#include <QtWidgets>
#include "ui_P_PluginBatchDeletePart.h"

#include "Source/RmmvUtilsPluginModule/StorageData/S_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/InformationData/S_InformationDataContainer.h"

/*
-----==========================================================-----
		类：		清理插件 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	清理插件的编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_PluginBatchDeletePart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginBatchDeletePart(QWidget *parent = 0);
		~P_PluginBatchDeletePart();
		
	//-----------------------------------
	//----控件
	public:
		QTableWidget* m_table;
		QList<QCheckBox*> m_checkBoxList;
		QList<C_ScriptAnnotation> m_allSearchedData;	//当前数据（文件夹插件）
	public slots: 
										//控件 - 初始化列表
		void refreshTable();
										//控件 - 添加一行
		void setOneRow_configedPlugin(int row, QString pluginName);
										//控件 - 全选
		void btn_selectAll();
										//控件 - 取消全选
		void btn_deselectAll();
										//控件 - 执行生成
		void btn_execute();

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_PluginBatchDeletePart ui;

};

#endif // P_PluginBatchDeletePart_H
