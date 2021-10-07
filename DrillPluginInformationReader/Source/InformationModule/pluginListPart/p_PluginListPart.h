#ifndef P_PluginListPart_H
#define P_PluginListPart_H

#include <QtWidgets>
#include "ui_P_PluginListPart.h"

#include "buttonPart/w_PluginAttrComment.h"
#include "buttonPart/p_PluginAttr_ButtonPart.h"

#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
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
										//表格 - 刷新横向宽度
		void refreshHorizontalSize(int table_width);
										//表格 - 清理项
		void clearTableItem();
										//表格 - 下拉框变化
		void modeChanged(QString mode_text);
										//表格 - 重刷表格
		void rebuildTable();
										//表格 - 刷新表格（自动）
		void refreshTableAuto( int start_index, int end_index );
		

	//-----------------------------------
	//----配置的插件
	protected:
		QList<C_PluginData*> m_allConfigedData;			//当前数据（配置的插件）
	private:
										//配置的插件 - 下拉框变化
		void pluginTypeChanged(QString type_text);
										//配置的插件 - 刷新表格（配置的插件，含搜索）
		void refreshTable_configedPlugin( int start_index, int end_index );
										//配置的插件 - 添加一行
		void setOneRow_configedPlugin(int row, QString pluginName, QWidget* widget = nullptr);

	//-----------------------------------
	//----文件夹插件
	protected:
		QString m_searchText;							//搜索的文本
		QList<C_ScriptAnnotation> m_allSearchedData;	//当前数据（文件夹插件）
	private:
										//文件夹插件 - 搜索插件
		void btn_search();
										//文件夹插件 - 刷新表格（文件夹插件，含搜索）
		void refreshTable_searchedPlugin( int start_index, int end_index );
										//文件夹插件 - 添加一行
		void setOneRow_searchedPlugin(int row, QString pluginName, QWidget* widget = nullptr);
										//文件夹插件 - 将指定字符串标蓝
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
	//----分页
	public:
		P_PageNavigator* m_p_PageNavigator;

	//-----------------------------------
	//----表格事件
	public slots:
										//表格事件 - 双击表格
		void tableDoubled(QTableWidgetItem *item);
										//表格事件 - 右键表格
		void tableRightClicked(QPoint p);
	signals:
										//信号 - 插件选中
		void pluginTriggered(QString plugin_name);

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
