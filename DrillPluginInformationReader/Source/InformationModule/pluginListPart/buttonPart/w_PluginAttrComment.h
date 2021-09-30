#ifndef W_PluginAttrComment_H
#define W_PluginAttrComment_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttrComment.h"

/*
-----==========================================================-----
		类：		属性说明窗口.h
		所属模块：	信息模块
		功能：		属性说明窗口。
					（详细见cpp）
-----==========================================================-----
*/

class W_PluginAttrComment : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttrComment(QWidget *parent = 0);		//构造函数
		~W_PluginAttrComment();							//析构函数
		
		
	//-----------------------------------
	//----窗口
									//窗口 - 设置数据
									//窗口 - 获取数据
									//窗口 - 本地数据 -> ui数据
									//窗口 - ui数据 -> 本地数据
									//窗口 - 提交数据（校验）
	private:
		Ui::W_PluginAttrComment ui;
		
};

#endif // W_QExpressionTest_H
