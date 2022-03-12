#include "stdafx.h"
#include "p_DesignTipGeneratorPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		设计灵感生成器 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	设计灵感生成器的编辑块结构。

		说明：		此控件块创建后，直接从当前 已读取的插件数据 中解析。
-----==========================================================-----
*/
P_DesignTipGeneratorPart::P_DesignTipGeneratorPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	this->m_data = C_DesignTipGenerator();
	this->m_data.initData();		//（创建后直接从当前 已读取的插件数据 中解析）

	//-----------------------------------
	//----控件初始化
	this->m_cellTank = QList<P_DesignTip_Cell*>();

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_generate, &QPushButton::clicked, this, &P_DesignTipGeneratorPart::doGenerate);

	this->doGenerate();
}

P_DesignTipGeneratorPart::~P_DesignTipGeneratorPart(){
}

/*-------------------------------------------------
		控件 - 清理控件块
*/
void P_DesignTipGeneratorPart::clearCells(){
	for (int i = this->m_cellTank.count()-1; i >= 0; i--){
		P_DesignTip_Cell* cell = this->m_cellTank.at(i);
		ui.verticalLayout_tip->removeWidget(cell);
		cell->deleteLater();
	}
	this->m_cellTank.clear();
}
/*-------------------------------------------------
		控件 - 执行生成
*/
void P_DesignTipGeneratorPart::doGenerate(){
	this->clearCells();

	// > 随机不重复的序列
	int ran_count = ui.spinBox->value();
	QList<int> indexOrg_list;
	QList<int> indexRan_list;
	for (int i = 0; i < this->m_data.count();i++){
		indexOrg_list.append(i);
	}
	for (int i = 0; i < ran_count; i++){
		if (this->m_data.count() == 0){ break; }
		int ran = qrand() % this->m_data.count();
		indexRan_list.append(indexOrg_list.at(ran));
		indexOrg_list.removeAt(ran);
	}

	// > 添加控件
	for (int i = 0; i < indexRan_list.count(); i++){
		C_DesignTip_Cell c_cell = this->m_data.getCellByIndex(i);
		P_DesignTip_Cell* p_cell = new P_DesignTip_Cell();
		p_cell->setData(c_cell);
		ui.verticalLayout_tip->addWidget(p_cell);
	}
}

/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_DesignTipGeneratorPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_DesignTipGeneratorPart::putUiToData(){
	//（暂无）
}