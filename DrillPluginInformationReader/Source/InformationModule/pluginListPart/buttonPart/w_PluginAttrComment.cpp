#include "stdafx.h"
#include "W_PluginAttrComment.h"

#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		����˵������.cpp
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�

		ʹ�÷�����
				>�򿪴���
					W_PluginAttrComment d;
					d.exec();

-----==========================================================-----
*/
W_PluginAttrComment::W_PluginAttrComment(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���

	//-----------------------------------
	//----ui��ʼ��
	TTool::_chinese_(ui.buttonBox);

}

W_PluginAttrComment::~W_PluginAttrComment(){
}


/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - �����ĵ�
*/
void W_PluginAttrComment::showInformation_word(QString pluginName){
	ui.stackedWidget->setCurrentIndex(0);
	this->setWindowTitle(pluginName + "����");
}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ��Դ·��
*/
void W_PluginAttrComment::showInformation_src(QString pluginName){
	ui.stackedWidget->setCurrentIndex(1);
	this->setWindowTitle(pluginName + "����");

}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ������
*/
void W_PluginAttrComment::showInformation_highConsumption(QString pluginName){
	ui.stackedWidget->setCurrentIndex(2);
	this->setWindowTitle(pluginName + "����");

}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - С����֧��
*/
void W_PluginAttrComment::showInformation_hasTool(QString pluginName){
	ui.stackedWidget->setCurrentIndex(3);
	this->setWindowTitle(pluginName + "����");

}
/*-------------------------------------------------
		�ؼ� - ��ʾ��Ϣ - ���
*/
void W_PluginAttrComment::showInformation_foreignKey(QString pluginName){
	ui.stackedWidget->setCurrentIndex(4);
	this->setWindowTitle(pluginName + "����");

}

