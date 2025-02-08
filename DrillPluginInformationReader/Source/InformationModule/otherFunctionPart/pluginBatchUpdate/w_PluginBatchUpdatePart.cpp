#include "stdafx.h"
#include "W_PluginBatchUpdatePart.h"

#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		类：		更新插件 窗口.cpp
		作者：		drill_up
		所属模块：	工具模块

		功能：		更新插件的窗口。

		使用方法：
				>创建填写窗口
					W_PluginBatchUpdatePart d(this);
					d.exec();
-----==========================================================-----
*/

W_PluginBatchUpdatePart::W_PluginBatchUpdatePart(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数
	this->m_p_PluginBatchUpdatePart = new P_PluginBatchUpdatePart(this);
	ui.verticalLayout_part->addWidget(this->m_p_PluginBatchUpdatePart);

	//-----------------------------------
	//----事件绑定
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &W_PluginBatchUpdatePart::acceptData);

	//-----------------------------------
	//----初始化ui
	TTool::_chinese_(ui.buttonBox);
}

W_PluginBatchUpdatePart::~W_PluginBatchUpdatePart(){
}


/*-------------------------------------------------
		窗口 - 本地数据 -> ui数据
*/
void W_PluginBatchUpdatePart::putDataToUi() {
	this->m_p_PluginBatchUpdatePart->putDataToUi();
};
/*-------------------------------------------------
		窗口 - ui数据 -> 本地数据
*/
void W_PluginBatchUpdatePart::putUiToData() {
	this->m_p_PluginBatchUpdatePart->putUiToData();
};
/*-------------------------------------------------
		窗口 - 提交数据（校验）
*/
void W_PluginBatchUpdatePart::acceptData(){
	this->putUiToData();
	this->accept();
};