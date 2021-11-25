#include "stdafx.h"
#include "p_HistoricalSearchRecord.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��ʷ������¼.cpp
		�汾��		v1.01
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		��ʾ ��ʷ������¼ �õĿؼ���

		ʹ�÷�����
				> ��ӿ�
					
-----==========================================================-----
*/
P_HistoricalSearchRecord::P_HistoricalSearchRecord(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�ؼ���ʼ��
	this->m_lengthLimit = 4;
	this->m_textList = QStringList();
	this->m_layerList = QList<QWidget*>() << ui.widget;
	
	//-----------------------------------
	//----�¼���

	this->rebuildUI();
}

P_HistoricalSearchRecord::~P_HistoricalSearchRecord(){
}


/*-------------------------------------------------
		�������� - ����¼�¼
*/
void P_HistoricalSearchRecord::addText(QString text){
	if (text.isEmpty()){ return; }
	
	// > �ظ�������ǰ��
	if (this->m_textList.contains(text)){
		this->m_textList.removeOne(text);
		this->m_textList.push_front(text);
	
	// > ���ظ����½�
	}else{
		this->m_textList.push_front(text);
	}

	// > ������������ȥһ��
	if (this->m_textList.count() > this->m_lengthLimit){
		this->m_textList.removeLast();
	}

	this->rebuildUI();
}
/*-------------------------------------------------
		�������� - ȥ����¼
*/
void P_HistoricalSearchRecord::removeText(QString text){
	this->m_textList.removeOne(text);
	this->rebuildUI();
}


/*-------------------------------------------------
		�ؼ� - �ؽ���ť��
*/
void P_HistoricalSearchRecord::rebuildUI(){
	this->takeAllLayer();

	// > ��ť�� �½�
	QList<QWidget*> btn_list = QList<QWidget*>();

	// > ��Ӱ�ť
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

	// > ɾ�������İ�ť
	for (int i = this->m_layerList.count() - 1; i >= 0; i--){
		QWidget* w = this->m_layerList.at(i);
		if (btn_list.contains(w) == false){
			w->deleteLater();
		}
	}

	// > �滻��ǰ��ť��
	this->m_layerList = btn_list;

	if (this->m_textList.count() > 0){
		ui.label_search->setText("��ʷ��ѯ��");
	}else{
		ui.label_search->setText("��ʷ��ѯ����");
	}

}
/*-------------------------------------------------
		�ؼ� - ȡ��ȫ����ť��
*/
void P_HistoricalSearchRecord::takeAllLayer(){
	for (int i = 0; i < this->m_layerList.count(); i++){
		QWidget* widget = this->m_layerList.at(i);
		widget->setParent(nullptr);
		ui.widget_container->layout()->removeWidget(widget);
	}
}
/*-------------------------------------------------
		�ؼ� - ���ݿؼ����ȡ������
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
		�ؼ� - ������ť��
*/
QWidget* P_HistoricalSearchRecord::createLayer(QString text){

	// > ��ť��
	QWidget* widget = new QWidget();
	QHBoxLayout* layout = new QHBoxLayout(widget);
	layout->setMargin(0);
	layout->setSpacing(0);
	widget->setLayout(layout);
	widget->setStatusTip(text);

	// > ������ť
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

	// > ȡ����ť
	QToolButton* cancel_btn = new QToolButton(widget);
	cancel_btn->setText("��");
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
		�ؼ� - ָ�� �ı���ť �����
*/
void P_HistoricalSearchRecord::searchBtn_action(){
	QToolButton* cur_btn = qobject_cast<QToolButton*>(sender());
	this->addText(cur_btn->statusTip());
	emit textClicked(cur_btn->statusTip());
}
/*-------------------------------------------------
		�ؼ� - ָ�� ȡ����ť �����
*/
void P_HistoricalSearchRecord::cancelBtn_action(){
	QToolButton* cur_btn = qobject_cast<QToolButton*>(sender());
	this->removeText(cur_btn->statusTip());
}


/*-------------------------------------------------
		�� - �������ݣ��޸ģ�
*/
void P_HistoricalSearchRecord::setData(QStringList data){
	TTool::_QStringList_clearEmptyRows_(&data);
	this->m_textList = data;
	this->rebuildUI();
}
/*-------------------------------------------------
		�� - ȡ������
*/
QStringList P_HistoricalSearchRecord::getData(){
	return this->m_textList;
}