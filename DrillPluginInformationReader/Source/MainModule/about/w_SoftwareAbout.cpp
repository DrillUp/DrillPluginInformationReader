#include "stdafx.h"
#include "W_SoftwareAbout.h"

#include "../versionLog/w_SoftwareVersionLog.h"
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
	connect(ui.toolButton_2, &QToolButton::clicked, this, &W_SoftwareAbout::openVersionLog);

	//-----------------------------------
	//----ui��ʼ��
	TTool::_chinese_(ui.buttonBox);

	ui.label_title->setText(QString("�����Ϣ�鿴����") + DRILL_VERSION + "��");

}

W_SoftwareAbout::~W_SoftwareAbout(){
}


/* --------------------------------------------------------------
		�ؼ� - �û��ֲ�
*/
void W_SoftwareAbout::openUserManual() {
	QString sPath = qApp->applicationDirPath();

	QString docx = sPath + "/help/���ڲ����Ϣ�鿴��.docx";
	if (QFileInfo(docx).exists()){
		QDesktopServices::openUrl(QUrl("file:/" + docx)); 
	}else{
		QMessageBox::warning(this, "����", "�ĵ�\"���ڲ����Ϣ�鿴��.docx\"�����ˡ�", QMessageBox::Yes);
	}

}
/* --------------------------------------------------------------
		�ؼ� - ������־
*/
void W_SoftwareAbout::openVersionLog(){
	W_SoftwareVersionLog d(this);
	d.exec();
}