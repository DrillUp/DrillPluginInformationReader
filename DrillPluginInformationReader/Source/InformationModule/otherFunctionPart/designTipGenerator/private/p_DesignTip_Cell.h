#ifndef P_DesignTip_Cell_H
#define P_DesignTip_Cell_H

#include <QtWidgets>
#include "ui_P_DesignTip_Cell.h"
#include "c_DesignTip_Cell.h"

/*
-----==========================================================-----
		类：		灵感生成器-单条 控件块.h
		作者：		drill_up
		所属模块：	插件模块
		说明：		显示控件 灵感生成器-单条 信息的结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_DesignTip_Cell : public QWidget
{
	Q_OBJECT

	public:
		P_DesignTip_Cell(QWidget *parent = 0);
		~P_DesignTip_Cell();
		
	//-----------------------------------
	//----控件
	public slots: 
										//控件 - 链接被点击
		void linkClicked_plugin(QString data);

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据
		void setData(C_DesignTip_Cell data);
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();

	private:
		Ui::P_DesignTip_Cell ui;
};

#endif // P_DesignTip_Cell_H
