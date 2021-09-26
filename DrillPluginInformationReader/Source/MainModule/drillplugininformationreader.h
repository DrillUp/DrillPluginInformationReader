#ifndef DRILLPLUGININFORMATIONREADER_H
#define DRILLPLUGININFORMATIONREADER_H

#include <QtWidgets/QMainWindow>
#include "ui_drillplugininformationreader.h"
#include "Source/InformationModule/p_InformationPart.h"
#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"

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
								//控件 - 刷新导航栏内容
		void refreshNav();
								//控件 - 帮助文档
		void openUserManual();
								//控件 - 关于...
		void openAbout();
		
	//-----------------------------------
	//----工程
	private:
		C_RmmvProjectData m_temp_data;
	private slots:
								//工程 - 选择工程
		void btn_selectProject();
								//工程 - 导入工程
		void btn_importProject();
								//工程 - 选择rmmv工程
		C_RmmvProjectData callRmmvSelect();


	//-----------------------------------
	//----事件
	private:
		QSize m_last_uiSize;
	public:
								//事件 - 窗口切换大小事件
		void resizeEvent(QResizeEvent *event);
								//事件 - 窗口关闭事件（点击关闭按钮）
		void closeEvent(QCloseEvent *event);

		
	//-----------------------------------
	//----窗口
	public:
								//窗口 - 用户自定义UI读取
		void ui_loadConfig();
								//窗口 - 用户自定义UI存储
		void ui_saveConfig();
	private:
		Ui::DrillPluginInformationReaderClass ui;
};

#endif // DRILLPLUGININFORMATIONREADER_H
