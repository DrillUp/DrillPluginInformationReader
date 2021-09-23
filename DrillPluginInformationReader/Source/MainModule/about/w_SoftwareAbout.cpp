#include "stdafx.h"
#include "W_SoftwareAbout.h"

#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		�ࣺ		���ڴ���.cpp
		����ģ�飺	������ģ��
		���ܣ�		���ڴ��ڡ�

		ʹ�÷�����
				>�򿪴���
					W_SoftwareAbout d;
					d.exec();

-----==========================================================-----
*/
W_SoftwareAbout::W_SoftwareAbout(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton, &QToolButton::clicked, this, &W_SoftwareAbout::openUserManual);

	//-----------------------------------
	//----ui��ʼ��
	TTool::_chinese_(ui.buttonBox);

	QString version = "v1.00";
	ui.label_title->setText("�����Ϣ��ȡ����" + version + "��");

}

W_SoftwareAbout::~W_SoftwareAbout(){
}


/* --------------------------------------------------------------
		�ؼ� - �û��ֲ�
*/
void W_SoftwareAbout::openUserManual() {
	QString sPath = qApp->applicationDirPath();

	QString docx = sPath + "/help/���ڲ����Ϣ��ȡ��.docx";
	if (QFileInfo(docx).exists()){
		QDesktopServices::openUrl(QUrl("file:/" + docx)); 
	}else{
		QMessageBox::warning(this, "����", "�ĵ�\"���ڲ����Ϣ��ȡ��.docx\"�����ˡ�", QMessageBox::Yes);
	}

}