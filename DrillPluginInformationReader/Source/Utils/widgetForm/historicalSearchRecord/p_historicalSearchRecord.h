#ifndef P_HistoricalSearchRecord_H
#define P_HistoricalSearchRecord_H

#include <QtWidgets/QDialog>
#include "ui_P_HistoricalSearchRecord.h"

/*
-----==========================================================-----
		类：		历史搜索记录.h
		版本：		v1.01
		作者：		drill_up
		所属模块：	工具模块
		功能：		显示 历史搜索记录 用的控件。
					（详细见cpp）
-----==========================================================-----
*/

class P_HistoricalSearchRecord : public QWidget
{
	Q_OBJECT

	public:
		P_HistoricalSearchRecord(QWidget *parent = 0);		//构造函数
		~P_HistoricalSearchRecord();						//析构函数
		
	//-----------------------------------
	//----缓冲数据
	protected:
		int m_lengthLimit;				//记录数量限制
		QStringList m_textList;			//记录数据
	public:
										//缓冲数据 - 添加新记录
		void addText(QString text);
										//缓冲数据 - 去除记录
		void removeText(QString text);
		
	//-----------------------------------
	//----控件
	protected:
		QList<QWidget*> m_layerList;
	public slots:
										//控件 - 重建按钮块
		void rebuildUI();
										//控件 - 取下全部按钮块
		void takeAllLayer();
	signals:
										//信号 - 某按钮被点击
		void textClicked(QString text);

	protected slots:
										//控件 - 获取按钮块(根据文本)
		QWidget* getLayerByText(QString text);
										//控件 - 创建按钮块
		QWidget* createLayer(QString text);
										//控件 - 指定 文本按钮 被点击
		void searchBtn_action();
										//控件 - 指定 取消按钮 被点击
		void cancelBtn_action();

	//-----------------------------------
	//----块
	public:
										//块 - 设置数据（修改）
		void setData(QStringList data);
										//块 - 取出数据
		QStringList getData();
	private:
		Ui::P_HistoricalSearchRecord ui;
		
};

#endif // P_HistoricalSearchRecord_H
