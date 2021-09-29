#include "stdafx.h"
#include "P_PageNavigator.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��ҳ�ؼ���.cpp
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		ʹ�ñ�ǩ���ж����ť����Щ��ť�൱�ڹ�ѡ��

		ʹ�÷�����
				> ��ʼ��
					this->m_p_PageNavigator = new P_PageNavigator();
					this->m_p_PageNavigator->initNavigator(all_count, pagePer_count, 5);
					ui.horizontalLayout_page->addWidget(this->m_p_PageNavigator);
					//���¼��󶨣�
					connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &W_PageNavigatorTest::indexChanged);
					this->m_p_PageNavigator->refreshPages();

				> ҳ���ȡ
					int page_index = this->m_p_PageNavigator.getCurrentPage();	//����0��ʼ������


		˵����		ע���ʼ���е�refreshPages��ҳ�뷢���仯����֮�󣬲Żᷢ���źš�
-----==========================================================-----
*/
P_PageNavigator::P_PageNavigator(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----������ʼ��
	this->m_cur_page = -1;
	this->m_all_count = 0;
	this->m_pagePer_count = 100;
	this->m_centerPageBtn_count = 5;
	this->m_center_lBtnList = QList<QToolButton*>();
	this->m_center_cBtn = nullptr;
	this->m_center_rBtnList = QList<QToolButton*>();

	//-----------------------------------
	//----ui��ʼ��
	ui.lineEdit_jumpTo->setValidator(new QIntValidator());

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_jumpTo, &QToolButton::clicked, this, &P_PageNavigator::jumpToPage_Action);
	connect(ui.toolButton_last, &QToolButton::clicked, this, &P_PageNavigator::selectLast);
	connect(ui.toolButton_next, &QToolButton::clicked, this, &P_PageNavigator::selectNext);

	connect(ui.toolButton_start, &QToolButton::clicked, this, &P_PageNavigator::selectStart);
	connect(ui.toolButton_end, &QToolButton::clicked, this, &P_PageNavigator::selectEnd);
	connect(ui.toolButton_start, &QToolButton::clicked, this, &P_PageNavigator::refreshBtnChecked);
	connect(ui.toolButton_end, &QToolButton::clicked, this, &P_PageNavigator::refreshBtnChecked);

}

P_PageNavigator::~P_PageNavigator(){
}


/*-------------------------------------------------
		��ʾ�� - ��ʼ��
*/
void P_PageNavigator::initNavigator(int all_count, int pagePer_count, int centerPageBtn_count){
	if (centerPageBtn_count < 3){ centerPageBtn_count = 3; }
	this->m_all_count = all_count;
	this->m_pagePer_count = pagePer_count;
	this->m_centerPageBtn_count = centerPageBtn_count;
	this->rebuildCenterPageBtn();
	this->refreshAllPageBtn();

	// > ǿѡ��ʼ��
	this->selectStart();
}
/*-------------------------------------------------
		��ʾ�� - �޸�������
*/
void P_PageNavigator::setAllCount(int all_count){
	if (this->m_all_count == all_count){ return; }
	this->m_all_count = all_count;
	this->rebuildCenterPageBtn();
	this->refreshAllPageBtn();

	// > ǿѡ��ʼ��
	this->selectStart();
}
/*-------------------------------------------------
		��ť�� - �ؽ���ť
*/
void P_PageNavigator::rebuildCenterPageBtn(){

	// > �˰�ť
	QList<QToolButton*> btn_list = QList<QToolButton*>();
	btn_list.append(this->m_center_lBtnList);
	btn_list.append(this->m_center_cBtn);
	btn_list.append(this->m_center_rBtnList);
	for (int i = btn_list.count() - 1; i >= 0; i--){
		QToolButton* btn = btn_list.at(i);
		disconnect(btn);
		ui.horizontalLayout_centerBtn->removeWidget(btn);
		delete btn;
	}
	this->m_center_lBtnList.clear();
	this->m_center_cBtn = nullptr;
	this->m_center_rBtnList.clear();


	// > ������ť�����������б�
	int left_count = this->m_centerPageBtn_count / 2;
	for (int i = 0; i < left_count; i++){
		QToolButton* btn = new QToolButton();
		btn->setMinimumWidth(28);
		btn->setMinimumHeight(28);
		btn->setMaximumWidth(30);
		btn->setMaximumHeight(28);
		connect(btn, &QToolButton::clicked, this, &P_PageNavigator::centerBtnClicked);
		ui.horizontalLayout_centerBtn->addWidget(btn);
		this->m_center_lBtnList.push_front(btn);
	}

	// > ������ť���м䣩
	QToolButton* btn = new QToolButton();
	btn->setMinimumWidth(28);
	btn->setMinimumHeight(28);
	btn->setMaximumWidth(30);
	btn->setMaximumHeight(28);
	connect(btn, &QToolButton::clicked, this, &P_PageNavigator::centerBtnClicked);
	ui.horizontalLayout_centerBtn->addWidget(btn);
	this->m_center_cBtn = btn;

	// > ������ť�����������б�
	int right_count = this->m_centerPageBtn_count - left_count - 1;
	for (int i = 0; i < right_count; i++){
		QToolButton* btn = new QToolButton();
		btn->setMinimumWidth(28);
		btn->setMinimumHeight(28);
		btn->setMaximumWidth(30);
		btn->setMaximumHeight(28);
		connect(btn, &QToolButton::clicked, this, &P_PageNavigator::centerBtnClicked);
		ui.horizontalLayout_centerBtn->addWidget(btn);
		this->m_center_rBtnList.push_back(btn);
	}

}
/*-------------------------------------------------
		��ť�� - ˢ��ҳ�밴ť
*/
void P_PageNavigator::refreshAllPageBtn(){

	// > �м�ҳ�밴ť
	if (this->getCurrentPage() == 0 || this->getCurrentPage() == this->getPageCount()-1){
		this->m_center_cBtn->setVisible(false);
	}else{
		this->m_center_cBtn->setVisible(true);
	}
	this->m_center_cBtn->setText(QString::number(this->getCurrentPage() + 1));

	// > ����ҳ�밴ť
	for (int i = 0; i < this->m_center_lBtnList.count(); i++){
		QToolButton* btn = this->m_center_lBtnList.at(i);
		int cur_page = this->getCurrentPage() - 1 - i;
		if (cur_page > 0){
			btn->setVisible(true);
		}else{
			btn->setVisible(false);
		}
		btn->setText(QString::number(cur_page + 1));
	}
	if (this->getCurrentPage() - this->m_center_lBtnList.count() -2 < 0){
		ui.label_left->setVisible(false);
	}else{
		ui.label_left->setVisible(true);
	}

	// > ����ҳ�밴ť
	for (int i = 0; i < this->m_center_rBtnList.count();i++){
		QToolButton* btn = this->m_center_rBtnList.at(i);
		int cur_page = this->getCurrentPage() + 1 + i;
		if (cur_page < this->getPageCount() - 1){
			btn->setVisible(true);
		}else{
			btn->setVisible(false);
		}
		btn->setText(QString::number(cur_page + 1));
	}
	if (this->getCurrentPage() + this->m_center_rBtnList.count() + 2 > this->getPageCount() - 1){
		ui.label_right->setVisible(false);
	}else{
		ui.label_right->setVisible(true);
	}

	// > β����ҳ��
	if (this->m_all_count <= this->m_pagePer_count){		//��ÿҳ��ʾ���������ʾ����С����ֻһ����ť��
		ui.toolButton_end->setVisible(false);
	}else{
		ui.toolButton_end->setVisible(true);
	}
	ui.toolButton_end->setText(QString::number(this->getPageCount()));

	// > ��ת��ҳ��
	QString cur_pageNum = QString::number(this->getCurrentPage() + 1);
	ui.lineEdit_jumpTo->setText(cur_pageNum);

	// > ҳ��ѡ�б��
	this->refreshBtnChecked();
}
/*-------------------------------------------------
		��ť�� - ��ť�����
*/
void P_PageNavigator::centerBtnClicked(){
	QToolButton* cur_btn = qobject_cast<QToolButton*>(sender());

	// > ѡҳ
	this->selectPage(cur_btn->text().toInt() - 1);

	// > ǿ��ˢѡ��״̬
	this->refreshBtnChecked();
}
/*-------------------------------------------------
		��ť�� - ˢ��ҳ�밴���������ֹ�ظ�����ȡ�����������
*/
void P_PageNavigator::refreshBtnChecked(){

	// > ҳ����ʾ
	QString cur_pageNum = QString::number(this->getCurrentPage() + 1);
	QList<QToolButton*> all_btn = QList<QToolButton*>() << ui.toolButton_last << ui.toolButton_next << ui.toolButton_start << ui.toolButton_end;
	all_btn.append(this->m_center_lBtnList);
	all_btn.append(this->m_center_cBtn);
	all_btn.append(this->m_center_rBtnList);

	// > ҳ��ѡ��
	for (int i = 0; i < all_btn.count(); i++){
		QToolButton* btn = all_btn.at(i);
		btn->setChecked(false);
		btn->setCheckable(false);
	}
	for (int i = 0; i < all_btn.count(); i++){
		QToolButton* btn = all_btn.at(i);
		if (btn->isVisible() == false){
			continue;
		}
		if (btn->text() == cur_pageNum){
			btn->setCheckable(true);
			btn->setChecked(true);
		}
	}
}


/*-------------------------------------------------
		ҳ�� - ��ȡ��ǰҳ
*/
int P_PageNavigator::getCurrentPage(){
	return this->m_cur_page;
}
/*-------------------------------------------------
		ҳ�� - ��ȡ��ǰ��
*/
int P_PageNavigator::getCurrentStartIndex(){
	return this->m_cur_page * this->m_pagePer_count;
}
int P_PageNavigator::getCurrentEndIndex(){
	int index = (this->m_cur_page + 1) * this->m_pagePer_count - 1;		//��0-9��10-19��
	if (index > this->m_all_count - 1){ return this->m_all_count - 1; }
	return index;
}
/*-------------------------------------------------
		ҳ�� - ��ȡҳ������
*/
int P_PageNavigator::getPageCount(){
	return qCeil((double)this->m_all_count / this->m_pagePer_count);
}
/*-------------------------------------------------
		ҳ�� - ˢ��ȫ��ҳ��
*/
void P_PageNavigator::refreshPages(){
	this->m_cur_page = -1;
	this->selectStart();

	// > ǿ��ˢѡ��״̬
	ui.toolButton_start->setCheckable(true);
	ui.toolButton_start->setChecked(true);
}
/*-------------------------------------------------
		ѡ�� - ����ѡ��
*/
void  P_PageNavigator::selectPage(int page_index){
	if (page_index < 0){ page_index = 0; }
	if (page_index >= this->getPageCount()){ page_index = this->getPageCount() - 1; }

	// > ��ͬҳ������
	if (this->m_cur_page == page_index){ return; }

	// > ����ҳ��
	this->m_cur_page = page_index;
	this->refreshAllPageBtn();

	// > �����ź�
	emit pageChanged(this->getCurrentPage());
	emit indexChanged(this->getCurrentStartIndex(), this->getCurrentEndIndex());
}
/*-------------------------------------------------
		ѡ�� - ѡ����һ��
*/
void  P_PageNavigator::selectLast(){
	this->selectPage(this->getCurrentPage() - 1);
}
/*-------------------------------------------------
		ѡ�� - ѡ����һ��
*/
void  P_PageNavigator::selectNext(){
	this->selectPage(this->getCurrentPage() + 1);
}
/*-------------------------------------------------
		ѡ�� - ѡ������
*/
void  P_PageNavigator::selectStart(){
	this->selectPage(0);
}
/*-------------------------------------------------
		ѡ�� - ѡ��β��
*/
void  P_PageNavigator::selectEnd(){
	this->selectPage(this->getPageCount() - 1);
}
/*-------------------------------------------------
		ѡ�� - ��ת��ҳ�루action��
*/
void P_PageNavigator::jumpToPage_Action(){

	// > ѡҳ
	this->selectPage(ui.lineEdit_jumpTo->text().toInt()-1);

	// > ǿ��ˢ��һ�£����һҳ���������ҳ��������
	this->refreshAllPageBtn();
}