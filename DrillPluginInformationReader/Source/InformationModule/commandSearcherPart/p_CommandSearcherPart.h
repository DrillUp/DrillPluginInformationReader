#ifndef P_CommandSearcherPart_H
#define P_CommandSearcherPart_H

#include <QtWidgets>
#include "ui_P_CommandSearcherPart.h"

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
	public slots: 


	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_CommandSearcherPart ui;

};

#endif // P_CommandSearcherPart_H
