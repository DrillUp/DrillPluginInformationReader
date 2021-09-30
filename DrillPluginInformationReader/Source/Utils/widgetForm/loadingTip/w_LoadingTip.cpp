#include "stdafx.h"
#include "w_LoadingTip.h"


/*
-----==========================================================-----
		�ࣺ		�ް�ť������ʾ����.cpp
		����ģ�飺	����ģ��
		���ܣ�		������ʾ�û����������
-----==========================================================-----
*/
W_LoadingTip::W_LoadingTip(QString text, QWidget *parent)
	: QDialog(parent)
{
	this->resize(300, 50);
	this->m_label = new QLabel(this);
	this->m_label->setObjectName(QStringLiteral("label"));
	this->m_layout = new QVBoxLayout(this);
	this->m_layout->setObjectName(QStringLiteral("gridLayout"));
	this->m_layout->addWidget(this->m_label);

	this->changeText(text);
}

W_LoadingTip::~W_LoadingTip(){
}


/*-------------------------------------------------
		�ؼ� - �޸��ı�
*/
void W_LoadingTip::changeText(QString text) {
	this->setWindowTitle(text);
	this->m_label->setText(text);
}


