#include "stdafx.h"
#include "W_PluginBatchDeletePart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		清理插件 窗口.cpp
		作者：		drill_up
		所属模块：	工具模块

		功能：		清理插件的窗口。

		使用方法：
				>创建填写窗口
					W_PluginBatchDeletePart d(this);
					d.exec();
-----==========================================================-----
*/

W_PluginBatchDeletePart::W_PluginBatchDeletePart(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	this->m_p_PluginBatchDeletePart = new P_PluginBatchDeletePart(this);
	ui.verticalLayout_part->addWidget(this->m_p_PluginBatchDeletePart);

	//-----------------------------------
	//----事件绑定
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &W_PluginBatchDeletePart::acceptData);

	//-----------------------------------
	//----初始化ui
	TTool::_chinese_(ui.buttonBox);
}

W_PluginBatchDeletePart::~W_PluginBatchDeletePart(){
}


/*-------------------------------------------------
		窗口 - 本地数据 -> ui数据
*/
void W_PluginBatchDeletePart::putDataToUi() {
	this->m_p_PluginBatchDeletePart->putDataToUi();
};
/*-------------------------------------------------
		窗口 - ui数据 -> 本地数据
*/
void W_PluginBatchDeletePart::putUiToData() {
	this->m_p_PluginBatchDeletePart->putUiToData();
};
/*-------------------------------------------------
		窗口 - 提交数据（校验）
*/
void W_PluginBatchDeletePart::acceptData(){
	this->putUiToData();
	this->accept();
};