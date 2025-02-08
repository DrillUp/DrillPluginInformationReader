#ifndef P_PageNavigator_H
#define P_PageNavigator_H
#include "stdafx.h"

#include <QtWidgets/QDialog>
#include "ui_P_PageNavigator.h"

/*
-----==========================================================-----
		类：		分页控件组.cpp
		版本：		v1.01
		作者：		drill_up
		所属模块：	工具模块
		功能：		使得标签带有多个按钮，这些按钮相当于勾选框。
					（详细见cpp）
-----==========================================================-----
*/

class P_PageNavigator : public QWidget
{
	Q_OBJECT

	public:
		P_PageNavigator(QWidget *parent = 0);	//构造函数
		~P_PageNavigator();						//析构函数
		
	//-----------------------------------
	//----显示项
	protected:
		int m_pagePer_count;			//每页项数
		int m_all_count;				//总项数
		int m_centerPageBtn_count;		//中间按钮数
	public:
									//显示项 - 初始化
		void initNavigator(int all_count, int pagePer_count = 100, int centerPageBtn_count = 5);
									//显示项 - 修改项数量
		void setAllCount(int all_count);
		
	//-----------------------------------
	//----按钮组
	protected:
		QList<QToolButton*> m_center_lBtnList;	//按钮（左翼）
		QToolButton* m_center_cBtn;				//按钮（中间）
		QList<QToolButton*> m_center_rBtnList;	//按钮（右翼）
	protected slots:
									//按钮组 - 重建中部按钮（列表全重建）
		void rebuildCenterPageBtn();
									//按钮组 - 刷新页码按钮显示
		void refreshAllPageBtn();
									//按钮组 - 按钮被点击
		void centerBtnClicked();
									//按钮组 - 刷新页码按下情况（防止重复按下取消按的情况）
		void refreshBtnChecked();

	//-----------------------------------
	//----页码
	protected:
		int m_cur_page;
	public slots:
									//页码 - 获取当前页
									//		【说明】：页码从0开始计数。
		int getCurrentPage();
									//页码 - 获取当前项
									//		【说明】：项从0开始计数。
		int getCurrentStartIndex();
		int getCurrentEndIndex();
									//页码 - 获取页码数量
		int getPageCount();
									//页码 - 刷新全部页码
		void refreshPages();
									//选中 - 设置页码
									//		【参数】：页码从0开始计数。数字可以随意越界，越界后会选择最接近的一项。
		void selectPage(int page_index);
									//选中 - 选中上一项
		void selectLast();
									//选中 - 选中下一项
		void selectNext();
									//选中 - 选中首项
		void selectStart();
									//选中 - 选中尾项
		void selectEnd();
	protected:
									//选中 - 跳转到页码（action）
		void jumpToPage_Action();
		
	//-----------------------------------
	//----信号
	signals:
									//信号 - 页码变化
		void pageChanged(int page);
									//信号 - 显示项变化
		void indexChanged(int start_index, int end_index );

	//-----------------------------------
	//----块
	private:
		Ui::P_PageNavigator ui;
		
};

#endif // W_QList_H
