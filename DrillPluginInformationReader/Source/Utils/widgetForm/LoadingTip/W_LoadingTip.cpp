#include "stdafx.h"
#include "W_LoadingTip.h"


/*
-----==========================================================-----
		类：		无按钮加载提示窗口.cpp
		所属模块：	工具模块
		功能：		仅仅提示用户进度情况。
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
		控件 - 修改文本
*/
void W_LoadingTip::changeText(QString text) {
	this->setWindowTitle(text);
	this->m_label->setText(text);
}


