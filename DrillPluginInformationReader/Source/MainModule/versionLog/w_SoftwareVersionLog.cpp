#include "stdafx.h"
#include "W_SoftwareVersionLog.h"

#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		�汾��־����.cpp
		����ģ�飺	������ģ��
		���ܣ�		�汾��־���ڡ�

		ʹ�÷�����
				>�򿪴���
					W_SoftwareVersionLog d;
					d.exec();

-----==========================================================-----
*/
W_SoftwareVersionLog::W_SoftwareVersionLog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���
	//���ޣ�

	//-----------------------------------
	//----ui��ʼ��
	TTool::_chinese_(ui.buttonBox);

	ui.label_title->setText(QString("�����Ϣ�鿴����") + DRILL_VERSION + "��");

}

W_SoftwareVersionLog::~W_SoftwareVersionLog(){
}

