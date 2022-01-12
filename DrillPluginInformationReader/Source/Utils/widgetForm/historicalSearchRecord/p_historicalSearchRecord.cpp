#include "stdafx.h"
#include "p_HistoricalSearchRecord.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		历史搜索记录.cpp
		版本：		v1.01
		作者：		drill_up
		所属模块：	工具模块
		功能：		显示 历史搜索记录 用的控件。

		使用方法：
				> 添加块
					
-----==========================================================-----
*/
P_HistoricalSearchRecord::P_HistoricalSearchRecord(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----控件初始化
	this->m_lengthLimit = 4;
	this->m_textList = QStringList();
	this->m_layerList = QList<QWidget*>() << ui.widget;
	
	//-----------------------------------
	//----事件绑定

	this->rebuildUI();
}

P_HistoricalSearchRecord::~P_HistoricalSearchRecord(){
}


/*-------------------------------------------------
		缓冲数据 - 添加新记录
*/
void P_HistoricalSearchRecord::addText(QString text){
	if (text.isEmpty()){ return; }
	
	// > 重复的数据前置
	if (this->m_textList.contains(text)){
		this->m_textList.removeOne(text);
		this->m_textList.push_front(text);
	
	// > 不重复的新建
	}else{
		this->m_textList.push_front(text);
	}

	// > 超出长度则退去一个
	if (this->m_textList.count() > this->m_lengthLimit){
		this->m_textList.removeLast();
	}

	this->rebuildUI();
}
/*-------------------------------------------------
		缓冲数据 - 去除记录
*/
void P_HistoricalSearchRecord::removeText(QString text){
	this->m_textList.removeOne(text);
	this->rebuildUI();
}


/*-------------------------------------------------
		控件 - 重建按钮块
*/
void P_HistoricalSearchRecord::rebuildUI(){
	this->takeAllLayer();

	// > 按钮组 新建
	QList<QWidget*> btn_list = QList<QWidget*>();

	// > 添加按钮
	for (int i = 0; i < this->m_textList.count(); i++){
		QString text = this->m_textList.at(i);
		QWidget* w = this->getLayerByText(text);
		if (w == nullptr){
			QWidget* new_layer = this->createLayer(text);
			btn_list.append(new_layer);
			ui.widget_container->layout()->addWidget(new_layer);
		}else{
			btn_list.append(w);
			ui.widget_container->layout()->addWidget(w);
		}
	}

	// > 删除不含的按钮
	for (int i = this->m_layerList.count() - 1; i >= 0; i--){
		QWidget* w = this->m_layerList.at(i);
		if (btn_list.contains(w) == false){
			w->deleteLater();
		}
	}

	// > 替换当前按钮组
	this->m_layerList = btn_list;

	if (this->m_textList.count() > 0){
		ui.label_search->setText("历史查询：");
	}else{
		ui.label_search->setText("历史查询：无");
	}

}
/*-------------------------------------------------
		控件 - 取下全部按钮块
*/
void P_HistoricalSearchRecord::takeAllLayer(){
	for (int i = 0; i < this->m_layerList.count(); i++){
		QWidget* widget = this->m_layerList.at(i);
		widget->setParent(nullptr);
		ui.widget_container->layout()->removeWidget(widget);
	}
}
/*-------------------------------------------------
		控件 - 根据控件块获取到对象
*/
QWidget* P_HistoricalSearchRecord::getLayerByText(QString text){
	for (int i = 0; i < this->m_layerList.count(); i++){
		QWidget* widget = this->m_layerList.at(i);
		if (widget->statusTip() == text){
			return widget;
		}
	}
	return nullptr;
}
/*-------------------------------------------------
		控件 - 创建按钮块
*/
QWidget* P_HistoricalSearchRecord::createLayer(QString text){

	// > 按钮块
	QWidget* widget = new QWidget();
	QHBoxLayout* layout = new QHBoxLayout(widget);
	layout->setMargin(0);
	layout->setSpacing(0);
	widget->setLayout(layout);
	widget->setStatusTip(text);

	// > 搜索按钮
	QToolButton* search_btn = new QToolButton(widget);
	search_btn->setText(text);
	search_btn->setStatusTip(text);
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(search_btn->sizePolicy().hasHeightForWidth());
	search_btn->setSizePolicy(sizePolicy);
	layout->addWidget(search_btn);
	connect(search_btn, &QToolButton::clicked, this, &P_HistoricalSearchRecord::searchBtn_action);

	// > 取消按钮
	QToolButton* cancel_btn = new QToolButton(widget);
	cancel_btn->setText("×");
	cancel_btn->setStatusTip(text);
	cancel_btn->setMaximumWidth(20);
	QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy2.setHorizontalStretch(0);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(cancel_btn->sizePolicy().hasHeightForWidth());
	cancel_btn->setSizePolicy(sizePolicy2);
	layout->addWidget(cancel_btn);
	connect(cancel_btn, &QToolButton::clicked, this, &P_HistoricalSearchRecord::cancelBtn_action);

	layout->setStretch(0, 1);
	layout->setStretch(1, 0);
	return widget;
}
/*-------------------------------------------------
		控件 - 指定 文本按钮 被点击
*/
void P_HistoricalSearchRecord::searchBtn_action(){
	QToolButton* cur_btn = qobject_cast<QToolButton*>(sender());
	this->addText(cur_btn->statusTip());
	emit textClicked(cur_btn->statusTip());
}
/*-------------------------------------------------
		控件 - 指定 取消按钮 被点击
*/
void P_HistoricalSearchRecord::cancelBtn_action(){
	QToolButton* cur_btn = qobject_cast<QToolButton*>(sender());
	this->removeText(cur_btn->statusTip());
}


/*-------------------------------------------------
		块 - 设置数据（修改）
*/
void P_HistoricalSearchRecord::setData(QStringList data){
	TTool::_QStringList_clearEmptyRows_(&data);
	this->m_textList = data;
	this->rebuildUI();
}
/*-------------------------------------------------
		块 - 取出数据
*/
QStringList P_HistoricalSearchRecord::getData(){
	return this->m_textList;
}