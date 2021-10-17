#ifndef W_PluginAttr_Docs_H
#define W_PluginAttr_Docs_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttr_Docs.h"

#include "Source/InformationModule/pluginDetailPart/helpDetailPart/p_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		类：		属性说明窗口 插件文档.h
		所属模块：	信息模块
		功能：		属性说明窗口。
					（详细见cpp）
-----==========================================================-----
*/

class W_PluginAttr_Docs : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttr_Docs(QWidget *parent = 0);		//构造函数
		~W_PluginAttr_Docs();							//析构函数
		
	//-----------------------------------
	//----控件
	public:
		P_ScriptHelp_Docs* m_p_docs;
	public:
									//控件 - 显示信息 - 帮助文档
		void showInformation_word(QString pluginName);
		
	//-----------------------------------
	//----窗口
									//窗口 - 设置数据
									//窗口 - 获取数据
									//窗口 - 本地数据 -> ui数据
									//窗口 - ui数据 -> 本地数据
									//窗口 - 提交数据（校验）
	private:
		Ui::W_PluginAttr_Docs ui;
		
};

#endif // W_QExpressionTest_H
