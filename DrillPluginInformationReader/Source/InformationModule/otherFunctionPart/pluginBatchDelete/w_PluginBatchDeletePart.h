#ifndef W_PluginBatchDeletePart_H
#define W_PluginBatchDeletePart_H

#include "ui_W_PluginBatchDeletePart.h"
#include "p_PluginBatchDeletePart.h"

/*
-----==========================================================-----
		类：		清理插件 窗口.h
		作者：		drill_up
		所属模块：	信息模块

		功能：		清理插件的窗口。
					（详细见cpp）
-----==========================================================-----
*/
class W_PluginBatchDeletePart : public QDialog
{
	Q_OBJECT

	public:
		W_PluginBatchDeletePart(QWidget *parent = 0);
		~W_PluginBatchDeletePart();

	//-----------------------------------
	//----控件
	protected:
		P_PluginBatchDeletePart* m_p_PluginBatchDeletePart;
	public:

	//-----------------------------------
	//----窗口
	public:
										//窗口 - 本地数据 -> ui数据
		void putDataToUi();							
										//窗口 - ui数据 -> 本地数据
		void putUiToData();

	public slots:
										//窗口 - 提交数据（校验）
		void acceptData();	
	signals:
		void acceptDataSignal(QString data);

	private:
		Ui::W_PluginBatchDeletePart ui;
};

#endif // W_PluginBatchDeletePart_H
