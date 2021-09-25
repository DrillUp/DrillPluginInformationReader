#include "stdafx.h"
#include "p_CommandSearcherPart.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		指令搜索器 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					
-----==========================================================-----
*/
P_CommandSearcherPart::P_CommandSearcherPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----控件初始化
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_commandType, 30);

	//-----------------------------------
	//----事件绑定

}

P_CommandSearcherPart::~P_CommandSearcherPart(){
}


/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_CommandSearcherPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_CommandSearcherPart::putUiToData(){
	//（暂无）
}