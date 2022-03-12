#ifndef P_DesignTipGeneratorPart_H
#define P_DesignTipGeneratorPart_H

#include <QtWidgets>
#include "ui_P_DesignTipGeneratorPart.h"
#include "c_DesignTipGenerator.h"
#include "private/p_DesignTip_Cell.h"

/*
-----==========================================================-----
		类：		设计灵感生成器 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	设计灵感生成器的编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_DesignTipGeneratorPart : public QWidget
{
	Q_OBJECT

	public:
		P_DesignTipGeneratorPart(QWidget *parent = 0);
		~P_DesignTipGeneratorPart();
		
	//-----------------------------------
	//----控件
	public:
		C_DesignTipGenerator m_data;
		QList<P_DesignTip_Cell*> m_cellTank;
	public slots: 
										//控件 - 清理控件块
		void clearCells();
										//控件 - 执行生成
		void doGenerate();

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_DesignTipGeneratorPart ui;

};

#endif // P_DesignTipGeneratorPart_H
