#ifndef P_CommandSearcherPart_H
#define P_CommandSearcherPart_H

#include <QtWidgets>
#include "ui_P_CommandSearcherPart.h"

#include "helpDetailPart/p_ScriptHelp_CommandSearchCell.h"
#include "Source/RmmvInteractiveModule/InformationData/S_InformationDataContainer.h"
#include "Source/Utils/widgetForm/historicalSearchRecord/p_historicalSearchRecord.h"
#include "Source/Utils/widgetForm/pageNavigator/p_PageNavigator.h"

/*
-----==========================================================-----
		类：		指令搜索器 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_CommandSearcherPart : public QWidget
{
	Q_OBJECT

	public:
		P_CommandSearcherPart(QWidget *parent = 0);
		~P_CommandSearcherPart();
		
	//-----------------------------------
	//----搜索指令
	protected:
		QString m_searchText;							//搜索的文本
		QList<C_ScriptAnnotation> m_allSearchedData;	//当前数据（文件夹插件）
	private:
										//搜索指令 - 搜索
		void btn_search();
										//搜索指令 - 刷新控件
		void refreshCellAuto( int start_index, int end_index );

	//-----------------------------------
	//----属性
	protected:
		QList<P_ScriptHelp_CommandSearchCell*> m_cellPartList;					//属性按钮组
	protected:
										//属性 - 获取按钮组
		P_ScriptHelp_CommandSearchCell* getButtonPartByIndex(int index);

	//-----------------------------------
	//----控件
	public:
		P_PageNavigator* m_p_PageNavigator;						//分页控件
		P_HistoricalSearchRecord* m_p_historicalSearchRecord;	//历史查询控件
	public slots:
										//控件 - 搜索的字符串被点击
		void searchTextClicked(QString text);

	//-----------------------------------
	//----块
	public:
										//块 - 用户自定义UI读取
		void ui_loadConfig();
										//块 - 用户自定义UI存储
		void ui_saveConfig();
	private:
		Ui::P_CommandSearcherPart ui;

};

#endif // P_CommandSearcherPart_H
