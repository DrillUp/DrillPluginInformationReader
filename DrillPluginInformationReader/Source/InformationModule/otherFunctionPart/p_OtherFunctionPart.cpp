#include "stdafx.h"
#include "p_OtherFunctionPart.h"

#include "excelDataGenerator/p_ExcelDataGenerator.h"
#include "Source/MainModule/versionLog/w_SoftwareVersionLog.h"
#include "Source/InformationModule/otherFunctionPart/pluginBatchDelete/w_PluginBatchDeletePart.h"
#include "Source/InformationModule/otherFunctionPart/pluginBatchUpdate/w_PluginBatchUpdatePart.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		其它功能 编辑块.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	其它功能的编辑块结构。
					
-----==========================================================-----
*/
P_OtherFunctionPart::P_OtherFunctionPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----初始化参数


	//-----------------------------------
	//----控件初始化
	//ui.groupBox_2->setVisible(false);	//（隐藏待填坑）

	//-----------------------------------
	//----事件绑定
	connect(ui.toolButton_showDesignTip, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_DesignTipGenerator);
	connect(ui.toolButton_showDeletePart, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_PluginBatchDelete);
	connect(ui.toolButton_showUpdatePart, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_PluginBatchUpdate);
	connect(ui.toolButton_showVersionLog, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_VersionLog);

	connect(ui.toolButton_excelPluginList, &QPushButton::clicked, this, &P_OtherFunctionPart::btn_ExcelPluginList);

}

P_OtherFunctionPart::~P_OtherFunctionPart(){
}


/*-------------------------------------------------
		控件 - 选择 灵感生成器
*/
void P_OtherFunctionPart::btn_DesignTipGenerator(){
	emit selected_DesignTipGenerator();
}
/*-------------------------------------------------
		控件 - 选择 清理未使用的插件
*/
void P_OtherFunctionPart::btn_PluginBatchDelete(){
	W_PluginBatchDeletePart d(this);
	d.exec();
}
/*-------------------------------------------------
		控件 - 选择 插件更新器
*/
void P_OtherFunctionPart::btn_PluginBatchUpdate(){
	W_PluginBatchUpdatePart d(this);
	d.exec();
}
/*-------------------------------------------------
		控件 - 选择 版本日志
*/
void P_OtherFunctionPart::btn_VersionLog(){
	W_SoftwareVersionLog d(this);
	d.exec();
}
/*-------------------------------------------------
		控件 - 生成 插件清单
*/
void P_OtherFunctionPart::btn_ExcelPluginList(){

	QMessageBox::about(nullptr, "提示", "此生成需要打开你电脑中的Excel软件，然后一个个写入数据，你需要耐心等待此过程，写入完毕后，会自动关掉Excel软件。");

	QString file_path;
	QFileDialog fd;
	fd.setWindowTitle("保存数据文件");
	fd.setAcceptMode(QFileDialog::AcceptSave);				//对话框类型（打开/保存）（保存会有文件覆盖提示）
	fd.setDirectory(".");									//默认目录
	fd.setNameFilters(QStringList() << "表格文件(*.xlsx)");	//文件格式
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
		块 - 本地数据 -> ui数据
*/
void P_OtherFunctionPart::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_OtherFunctionPart::putUiToData(){
	//（暂无）
}