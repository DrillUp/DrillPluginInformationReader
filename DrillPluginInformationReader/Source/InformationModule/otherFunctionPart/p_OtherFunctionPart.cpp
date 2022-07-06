#include "stdafx.h"
#include "p_OtherFunctionPart.h"

#include "excelDataGenerator/p_ExcelDataGenerator.h"
#include "Source/MainModule/versionLog/w_SoftwareVersionLog.h"
#include "Source/InformationModule/otherFunctionPart/pluginBatchDelete/w_PluginBatchDeletePart.h"
#include "Source/InformationModule/otherFunctionPart/pluginBatchUpdate/w_PluginBatchUpdatePart.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		�������� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������ܵı༭��ṹ��
					
-----==========================================================-----
*/
P_OtherFunctionPart::P_OtherFunctionPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	//ui.groupBox_2->setVisible(false);	//�����ش���ӣ�

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_showDesignTip, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_DesignTipGenerator);
	connect(ui.toolButton_showDeletePart, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_PluginBatchDelete);
	connect(ui.toolButton_showUpdatePart, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_PluginBatchUpdate);
	connect(ui.toolButton_showVersionLog, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_VersionLog);

	connect(ui.toolButton_excelPluginList, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_ExcelPluginList);

}

P_OtherFunctionPart::~P_OtherFunctionPart(){
}


/*-------------------------------------------------
		�ؼ� - ѡ�� ���������
*/
void P_OtherFunctionPart::btn_DesignTipGenerator(){
	emit selected_DesignTipGenerator();
}
/*-------------------------------------------------
		�ؼ� - ѡ�� ����δʹ�õĲ��
*/
void P_OtherFunctionPart::btn_PluginBatchDelete(){
	W_PluginBatchDeletePart d(this);
	d.exec();
}
/*-------------------------------------------------
		�ؼ� - ѡ�� ���������
*/
void P_OtherFunctionPart::btn_PluginBatchUpdate(){
	W_PluginBatchUpdatePart d(this);
	d.exec();
}
/*-------------------------------------------------
		�ؼ� - ѡ�� �汾��־
*/
void P_OtherFunctionPart::btn_VersionLog(){
	W_SoftwareVersionLog d(this);
	d.exec();
}
/*-------------------------------------------------
		�ؼ� - ���� ����嵥
*/
void P_OtherFunctionPart::btn_ExcelPluginList(){

	QMessageBox::about(nullptr, "��ʾ", "��������Ҫ��������е�Excel�����Ȼ��һ����д�����ݣ�����Ҫ���ĵȴ��˹��̣�д����Ϻ󣬻��Զ��ص�Excel�����");

	QString file_path;
	QFileDialog fd;
	fd.setWindowTitle("���������ļ�");
	fd.setAcceptMode(QFileDialog::AcceptSave);				//�Ի������ͣ���/���棩����������ļ�������ʾ��
	fd.setDirectory(".");									//Ĭ��Ŀ¼
	fd.setNameFilters(QStringList() << "����ļ�(*.xlsx)");	//�ļ���ʽ
	if (fd.exec() == QDialog::Accepted) {
		if (fd.selectedFiles().empty()) {
			return;
		}
		file_path = fd.selectedFiles().at(0);
	}else {
		return;
	}

	P_ExcelDataGenerator p_ExcelDataGenerator;
	p_ExcelDataGenerator.generatePluginDataList(file_path);

	QFileInfo file_info(file_path);
	if (file_info.exists()){
		QDesktopServices::openUrl(QUrl("file:/" + file_info.absolutePath()));
	}
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_OtherFunctionPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_OtherFunctionPart::putUiToData(){
	//�����ޣ�
}