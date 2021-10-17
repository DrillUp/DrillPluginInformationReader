#ifndef W_PluginAttr_Src_H
#define W_PluginAttr_Src_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttr_Src.h"

#include "Source/InformationModule/pluginDetailPart/helpDetailPart/p_ScriptHelp_Src.h"

/*
-----==========================================================-----
		类：		属性说明窗口 资源路径.h
		所属模块：	信息模块
		功能：		属性说明窗口。
					（详细见cpp）
-----==========================================================-----
*/

class W_PluginAttr_Src : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttr_Src(QWidget *parent = 0);		//构造函数
		~W_PluginAttr_Src();							//析构函数
		
	//-----------------------------------
	//----控件
	public:
		P_ScriptHelp_Src* m_p_src;
	public:
									//控件 - 显示信息 - 资源路径
		void showInformation_src(QString pluginName);
		
	//-----------------------------------
	//----窗口
									//窗口 - 设置数据
									//窗口 - 获取数据
									//窗口 - 本地数据 -> ui数据
									//窗口 - ui数据 -> 本地数据
									//窗口 - 提交数据（校验）
	private:
		Ui::W_PluginAttr_Src ui;
		
};

#endif // W_QExpressionTest_H
