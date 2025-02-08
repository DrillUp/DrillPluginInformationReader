#include "stdafx.h"
#include "p_DesignTipGeneratorPart.h"

#include "Source/Utils/Common/TTool.h"

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
	this->m_indexOrgTank = QList<int>();

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_generate, &QPushButton::clicked, this, &P_DesignTipGeneratorPart::doGenerate);
	connect(ui.toolButton_resetAll, &QPushButton::clicked, this, &P_DesignTipGeneratorPart::resetAll);

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
		控件 - 重新开始全部
*/
void P_DesignTipGeneratorPart::resetAll(){
	this->resetIndexTank();
	this->doGenerate();
}
/*-------------------------------------------------
		控件 - 重设序列
*/
void P_DesignTipGeneratorPart::resetIndexTank(){
	this->m_indexOrgTank.clear();
	for (int i = 0; i < this->m_data.count(); i++){
		this->m_indexOrgTank.append(i);
	}
}
/*-------------------------------------------------
		控件 - 刷新进度
*/
void P_DesignTipGeneratorPart::refreshProcess(){
	QString msg = "";
	msg.append("(");
	msg.append(QString::number(this->m_data.count() - m_indexOrgTank.count()));
	msg.append("/");
	msg.append(QString::number(this->m_data.count()));
	msg.append(")");
	ui.label_process->setText(msg);
}
/*-------------------------------------------------
		控件 - 执行生成
*/
void P_DesignTipGeneratorPart::doGenerate(){
	this->clearCells();

	// > 翻到了最后项，则重新开始
	if (this->m_indexOrgTank.count() == 0){
		this->resetIndexTank();
	}

	// > 随机不重复的序列
	int ran_count = ui.spinBox->value();
	QList<int> curRan_list;
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	for (int i = 0; i < ran_count; i++){
		if (this->m_data.count() == 0){ break; }
		if (this->m_indexOrgTank.count() == 0){ break; }
		int ran = qrand() % this->m_indexOrgTank.count();
		curRan_list.append(this->m_indexOrgTank.at(ran));
		this->m_indexOrgTank.removeAt(ran);
	}
	//qDebug() << curRan_list;（随机数列表）

	// > 添加控件
	for (int i = 0; i < curRan_list.count(); i++){
		int index = curRan_list.at(i);
		C_DesignTip_Cell c_cell = this->m_data.getCellByIndex(index);
		P_DesignTip_Cell* p_cell = new P_DesignTip_Cell();
		p_cell->setData(c_cell);
		this->m_cellTank.append(p_cell);
		ui.verticalLayout_tip->addWidget(p_cell);
	}

	// > 记录随机项
	this->refreshProcess();
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