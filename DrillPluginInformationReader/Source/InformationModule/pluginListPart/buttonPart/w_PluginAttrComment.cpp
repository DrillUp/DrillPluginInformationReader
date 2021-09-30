#include "stdafx.h"
#include "W_PluginAttrComment.h"

#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		类：		属性说明窗口.cpp
		所属模块：	信息模块
		功能：		属性说明窗口。

		使用方法：
				>打开窗口
					W_PluginAttrComment d;
					d.exec();

-----==========================================================-----
*/
W_PluginAttrComment::W_PluginAttrComment(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定

	//-----------------------------------
	//----ui初始化
	TTool::_chinese_(ui.buttonBox);

}

W_PluginAttrComment::~W_PluginAttrComment(){
}

