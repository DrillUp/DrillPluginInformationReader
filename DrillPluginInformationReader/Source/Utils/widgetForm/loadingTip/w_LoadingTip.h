#ifndef W_LoadingTip_H
#define W_LoadingTip_H

#include <QDialog>

/*
-----==========================================================-----
		类：		无按钮加载提示窗口.h
		所属模块：	工具模块
		功能：		仅仅提示用户进度情况。
-----==========================================================-----
*/
class W_LoadingTip : public QDialog
{
	Q_OBJECT

	public:
		W_LoadingTip(QString text = "加载中...", QWidget *parent = 0);
		~W_LoadingTip();

	//-----------------------------------
	//----控件
	public:
		QVBoxLayout* m_layout;
		QLabel* m_label;
	public slots:
							//控件 - 修改文本
		void changeText(QString text);
		
	//-----------------------------------
	//----窗口
	//	（无）

};

#endif // W_LoadingTip_H
