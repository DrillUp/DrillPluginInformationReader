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

