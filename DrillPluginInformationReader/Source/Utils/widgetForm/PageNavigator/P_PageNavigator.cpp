#include "stdafx.h"
#include "P_PageNavigator.h"

#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		类：		分页控件组.cpp
		版本：		v1.01
		作者：		drill_up
		所属模块：	工具模块
		功能：		使得标签带有多个按钮，这些按钮相当于勾选框。

		使用方法：
				> 初始化
					this->m_p_PageNavigator = new P_PageNavigator();
					this->m_p_PageNavigator->initNavigator(all_count, pagePer_count, 5);
					ui.horizontalLayout_page->addWidget(this->m_p_PageNavigator);
					//（事件绑定）
					connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &W_PageNavigatorTest::indexChanged);
					this->m_p_PageNavigator->refreshPages();

				> 页码获取
					int page_index = this->m_p_PageNavigator.getCurrentPage();	//（从0开始计数）


		说明：		注意初始化中的refreshPages，页码发生变化并绑定之后，才会发出信号。
-----==========================================================-----
*/
P_PageNavigator::P_PageNavigator(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----参数初始化
	this->m_cur_page = -1;
	this->m_all_count = 0;
	this->m_pagePer_count = 100;
	this->m_centerPageBtn_count = 5;
	this->m_center_lBtnList.clear();
	this->m_center_cBtn = nullptr;
	this->m_center_rBtnList.clear();

	//-----------------------------------
	//----ui初始化
	ui.lineEdit_jumpTo->setValidator(new QIntValidator());

	//-----------------------------------
	//----事件绑定
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
		显示项 - 初始化
*/
void P_PageNavigator::initNavigator(int all_count, int pagePer_count, int centerPageBtn_count){
	if (centerPageBtn_count < 3){ centerPageBtn_count = 3; }
	this->m_all_count = all_count;
	this->m_pagePer_count = pagePer_count;
	this->m_centerPageBtn_count = centerPageBtn_count;
	this->rebuildCenterPageBtn();
	this->refreshAllPageBtn();

	// > 强选初始化
	this->selectStart();
}
/*-------------------------------------------------
		显示项 - 修改项数量
*/
void P_PageNavigator::setAllCount(int all_count){
	if (this->m_all_count == all_count){ return; }
	this->m_all_count = all_count;
	this->rebuildCenterPageBtn();
	this->refreshAllPageBtn();

	// > 强选初始化
	this->selectStart();
}


/*-------------------------------------------------
		按钮组 - 重建按钮
*/
void P_PageNavigator::rebuildCenterPageBtn(){

	// > 退按钮
	QList<QToolButton*> btn_list;
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


	// > 建立按钮（左翼，倒序列表）
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

	// > 建立按钮（中间）
	QToolButton* btn = new QToolButton();
	btn->setMinimumWidth(28);
	btn->setMinimumHeight(28);
	btn->setMaximumWidth(30);
	btn->setMaximumHeight(28);
	connect(btn, &QToolButton::clicked, this, &P_PageNavigator::centerBtnClicked);
	ui.horizontalLayout_centerBtn->addWidget(btn);
	this->m_center_cBtn = btn;

	// > 建立按钮（右翼，正序列表）
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
		按钮组 - 刷新页码按钮
*/
void P_PageNavigator::refreshAllPageBtn(){

	// > 中间页码按钮
	if (this->getCurrentPage() == 0 || this->getCurrentPage() == this->getPageCount()-1){
		this->m_center_cBtn->setVisible(false);
	}else{
		this->m_center_cBtn->setVisible(true);
	}
	this->m_center_cBtn->setText(QString::number(this->getCurrentPage() + 1));

	// > 左翼页码按钮
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

	// > 右翼页码按钮
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

	// > 尾数的页码
	if (this->m_all_count <= this->m_pagePer_count){		//（每页显示量比最大显示量还小，则只一个按钮）
		ui.toolButton_end->setVisible(false);
	}else{
		ui.toolButton_end->setVisible(true);
	}
	ui.toolButton_end->setText(QString::number(this->getPageCount()));

	// > 跳转的页码
	QString cur_pageNum = QString::number(this->getCurrentPage() + 1);
	ui.lineEdit_jumpTo->setText(cur_pageNum);

	// > 页码选中标记
	this->refreshBtnChecked();
}
/*-------------------------------------------------
		按钮组 - 按钮被点击
*/
void P_PageNavigator::centerBtnClicked(){
	QToolButton* cur_btn = qobject_cast<QToolButton*>(sender());

	// > 选页
	this->selectPage(cur_btn->text().toInt() - 1);

	// > 强制刷选中状态
	this->refreshBtnChecked();
}
/*-------------------------------------------------
		按钮组 - 刷新页码按下情况（防止重复按下取消按的情况）
*/
void P_PageNavigator::refreshBtnChecked(){

	// > 页码显示
	QString cur_pageNum = QString::number(this->getCurrentPage() + 1);
	QList<QToolButton*> all_btn = QList<QToolButton*>() << ui.toolButton_last << ui.toolButton_next << ui.toolButton_start << ui.toolButton_end;
	all_btn.append(this->m_center_lBtnList);
	all_btn.append(this->m_center_cBtn);
	all_btn.append(this->m_center_rBtnList);

	// > 页码选中
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
		页码 - 获取当前页
*/
int P_PageNavigator::getCurrentPage(){
	return this->m_cur_page;
}
/*-------------------------------------------------
		页码 - 获取当前项
*/
int P_PageNavigator::getCurrentStartIndex(){
	return this->m_cur_page * this->m_pagePer_count;
}
int P_PageNavigator::getCurrentEndIndex(){
	int index = (this->m_cur_page + 1) * this->m_pagePer_count - 1;		//（0-9，10-19）
	if (index > this->m_all_count - 1){ return this->m_all_count - 1; }
	return index;
}
/*-------------------------------------------------
		页码 - 获取页码数量
*/
int P_PageNavigator::getPageCount(){
	return qCeil((double)this->m_all_count / this->m_pagePer_count);
}
/*-------------------------------------------------
		页码 - 刷新全部页码
*/
void P_PageNavigator::refreshPages(){
	this->m_cur_page = -1;
	this->selectStart();

	// > 强制刷选中状态
	ui.toolButton_start->setCheckable(true);
	ui.toolButton_start->setChecked(true);
}
/*-------------------------------------------------
		选中 - 设置选中
*/
void  P_PageNavigator::selectPage(int page_index){
	if (page_index < 0){ page_index = 0; }
	if (page_index >= this->getPageCount()){ page_index = this->getPageCount() - 1; }

	// > 相同页码跳过
	if (this->m_cur_page == page_index){ return; }

	// > 设置页码
	this->m_cur_page = page_index;
	this->refreshAllPageBtn();

	// > 发送信号
	emit pageChanged(this->getCurrentPage());
	emit indexChanged(this->getCurrentStartIndex(), this->getCurrentEndIndex());
}
/*-------------------------------------------------
		选中 - 选中上一项
*/
void  P_PageNavigator::selectLast(){
	this->selectPage(this->getCurrentPage() - 1);
}
/*-------------------------------------------------
		选中 - 选中下一项
*/
void  P_PageNavigator::selectNext(){
	this->selectPage(this->getCurrentPage() + 1);
}
/*-------------------------------------------------
		选中 - 选中首项
*/
void  P_PageNavigator::selectStart(){
	this->selectPage(0);
}
/*-------------------------------------------------
		选中 - 选中尾项
*/
void  P_PageNavigator::selectEnd(){
	this->selectPage(this->getPageCount() - 1);
}
/*-------------------------------------------------
		选中 - 跳转到页码（action）
*/
void P_PageNavigator::jumpToPage_Action(){

	// > 选页
	this->selectPage(ui.lineEdit_jumpTo->text().toInt()-1);

	// > 强制刷新一下（最后一页再输入最大页的修正）
	this->refreshAllPageBtn();
}