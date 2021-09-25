#ifndef DRILLPLUGININFORMATIONREADER_H
#define DRILLPLUGININFORMATIONREADER_H

#include <QtWidgets/QMainWindow>
#include "ui_drillplugininformationreader.h"
#include "Source/InformationModule/p_InformationPart.h"

/*
-----==========================================================-----
		类：		主窗体.h
		作者：		drill_up
		所属模块：	主窗体模块
		功能：		程序进入后的主控制窗口。
					（详细见cpp）
-----==========================================================-----
*/
class DrillPluginInformationReader : public QMainWindow
{
	Q_OBJECT

	public:
		DrillPluginInformationReader(QWidget *parent = 0);
		~DrillPluginInformationReader();
		static DrillPluginInformationReader* cur_instance;		//单例
		static DrillPluginInformationReader* getInstance();		//单例，获取自己
		void _init();											//初始化
		

	//-----------------------------------
	//----控件
	public:
		P_InformationPart* m_P_InformationPart;
	public slots:
								//控件 - 帮助文档
		void openUserManual();
								//控件 - 关于...
		void openAbout();

		
	//-----------------------------------
	//----窗口
	private:
		Ui::DrillPluginInformationReaderClass ui;
};

#endif // DRILLPLUGININFORMATIONREADER_H
