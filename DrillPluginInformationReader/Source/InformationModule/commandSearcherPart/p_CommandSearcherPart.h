#ifndef P_CommandSearcherPart_H
#define P_CommandSearcherPart_H

#include <QtWidgets>
#include "ui_P_CommandSearcherPart.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
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
