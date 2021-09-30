#ifndef P_PluginListPart_H
#define P_PluginListPart_H

#include <QtWidgets>
#include "ui_P_PluginListPart.h"

#include "buttonPart/w_PluginAttrComment.h"
#include "buttonPart/p_PluginAttr_ButtonPart.h"
#include "Source/Utils/widgetForm/pageNavigator/p_PageNavigator.h"

/*
-----==========================================================-----
		类：		插件列表 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_PluginListPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginListPart(QWidget *parent = 0);
		~P_PluginListPart();

	//-----------------------------------
	//----表格结构
	public:
		bool slot_block;					//事件阻塞
		QTableWidget* m_table;				//表格结构
	public slots:
										//表格 - 初始化
		void initTable(QTableWidget* table);
										//表格 - 下拉框变化
		void modeChanged(QString text);
										//表格 - 清理项
		void clearTableItem();
										//表格 - 刷新表格（自动）
		void refreshTable();
		void refreshTableAuto( int start_index, int end_index );
										//表格 - 刷新表格（配置的插件）
		void refreshTable_configedPlugin( int start_index, int end_index );
										//表格 - 刷新表格（全部插件）
		void refreshTable_allPlugin( int start_index, int end_index );
	private:
										//私有 - 添加一行
		void setOneRow(int row, QString pluginName, QWidget* widget = nullptr);
										//私有 - 将指定字符串标蓝
		QLabel* getLabelWithSign(QString text, QString searching_text);

	//-----------------------------------
	//----属性
	protected:
		W_PluginAttrComment* m_w_PluginAttrComment;			//属性说明窗口
		QList<P_PluginAttr_ButtonPart*> m_btnPartList;		//属性按钮组
	protected:
										//属性 - 获取按钮组
		P_PluginAttr_ButtonPart* getButtonPartByIndex(int index);

	//-----------------------------------
	//----表格事件
	public slots:
										//表格事件 - 双击表格
		//void treeDoubled(QTreeWidgetItem *item, int col);
										//表格事件 - 右键表格
		//void treeRightClicked(QPoint p);
		
	//-----------------------------------
	//----分页
	public:
		P_PageNavigator* m_p_PageNavigator;

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_PluginListPart ui;

};

#endif // P_PluginListPart_H
