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
	//----控件
	public:
									//控件 - 显示信息 - 帮助文档
		void showInformation_word(QString pluginName);
									//控件 - 显示信息 - 资源路径
		void showInformation_src(QString pluginName);
									//控件 - 显示信息 - 高消耗
		void showInformation_highConsumption(QString pluginName);
									//控件 - 显示信息 - 小工具支持
		void showInformation_hasTool(QString pluginName);
									//控件 - 显示信息 - 外键
		void showInformation_foreignKey(QString pluginName);
		
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
