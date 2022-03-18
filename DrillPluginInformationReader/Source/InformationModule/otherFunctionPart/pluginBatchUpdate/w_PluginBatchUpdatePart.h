#ifndef W_PluginBatchUpdatePart_H
#define W_PluginBatchUpdatePart_H

#include "ui_W_PluginBatchUpdatePart.h"
#include "p_PluginBatchUpdatePart.h"

/*
-----==========================================================-----
		类：		更新插件 窗口.h
		作者：		drill_up
		所属模块：	信息模块

		功能：		更新插件的窗口。
					（详细见cpp）
-----==========================================================-----
*/
class W_PluginBatchUpdatePart : public QDialog
{
	Q_OBJECT

	public:
		W_PluginBatchUpdatePart(QWidget *parent = 0);
		~W_PluginBatchUpdatePart();

	//-----------------------------------
	//----控件
	protected:
		P_PluginBatchUpdatePart* m_p_PluginBatchUpdatePart;
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
		Ui::W_PluginBatchUpdatePart ui;
};

#endif // W_PluginBatchUpdatePart_H
