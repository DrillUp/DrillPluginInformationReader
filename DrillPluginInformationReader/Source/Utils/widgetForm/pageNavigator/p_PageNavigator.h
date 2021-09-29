#ifndef P_PageNavigator_H
#define P_PageNavigator_H

#include <QtWidgets/QDialog>
#include "ui_P_PageNavigator.h"

/*
-----==========================================================-----
		�ࣺ		��ҳ�ؼ���.cpp
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		ʹ�ñ�ǩ���ж����ť����Щ��ť�൱�ڹ�ѡ��
					����ϸ��cpp��
-----==========================================================-----
*/

class P_PageNavigator : public QWidget
{
	Q_OBJECT

	public:
		P_PageNavigator(QWidget *parent = 0);	//���캯��
		~P_PageNavigator();						//��������
		
	//-----------------------------------
	//----��ʾ��
	protected:
		int m_pagePer_count;			//ÿҳ����
		int m_all_count;				//������
		int m_centerPageBtn_count;		//�м䰴ť��
	public:
									//��ʾ�� - ��ʼ��
		void initNavigator(int all_count, int pagePer_count = 100, int centerPageBtn_count = 5);
									//��ʾ�� - �޸�������
									//		��˵�������ɶ�ε��ã���������ͬʱ������ˢ�����ݡ�
		void setAllCount(int all_count);

	//-----------------------------------
	//----��ť��
	protected:
		QList<QToolButton*> m_center_lBtnList;	//��ť������
		QToolButton* m_center_cBtn;				//��ť���м䣩
		QList<QToolButton*> m_center_rBtnList;	//��ť������
	protected slots:
									//��ť�� - �ؽ��в���ť���б�ȫ�ؽ���
		void rebuildCenterPageBtn();
									//��ť�� - ˢ��ҳ�밴ť��ʾ
		void refreshAllPageBtn();
									//��ť�� - ��ť�����
		void centerBtnClicked();
									//��ť�� - ˢ��ҳ�밴���������ֹ�ظ�����ȡ�����������
		void refreshBtnChecked();

	//-----------------------------------
	//----ҳ��
	protected:
		int m_cur_page;
	public slots:
									//ҳ�� - ��ȡ��ǰҳ
									//		��˵������ҳ���0��ʼ������
		int getCurrentPage();
									//ҳ�� - ��ȡ��ǰ��
									//		��˵���������0��ʼ������
		int getCurrentStartIndex();
		int getCurrentEndIndex();
									//ҳ�� - ��ȡҳ������
		int getPageCount();
									//ҳ�� - ˢ��ȫ��ҳ��
		void refreshPages();
									//ѡ�� - ����ҳ��
									//		����������ҳ���0��ʼ���������ֿ�������Խ�磬Խ����ѡ����ӽ���һ�
		void selectPage(int page_index);
									//ѡ�� - ѡ����һ��
		void selectLast();
									//ѡ�� - ѡ����һ��
		void selectNext();
									//ѡ�� - ѡ������
		void selectStart();
									//ѡ�� - ѡ��β��
		void selectEnd();
	protected:
									//ѡ�� - ��ת��ҳ�루action��
		void jumpToPage_Action();
		
	//-----------------------------------
	//----�ź�
	signals:
									//�ź� - ҳ��仯
		void pageChanged(int page);
									//�ź� - ��ʾ��仯
		void indexChanged(int start_index, int end_index );

	//-----------------------------------
	//----��
	private:
		Ui::P_PageNavigator ui;
		
};

#endif // W_QList_H
