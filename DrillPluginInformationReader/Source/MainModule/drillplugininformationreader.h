#ifndef DRILLPLUGININFORMATIONREADER_H
#define DRILLPLUGININFORMATIONREADER_H

#include <QtWidgets/QMainWindow>
#include "ui_drillplugininformationreader.h"

#include "Source/InformationModule/p_InformationPart.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
#include "Source/Utils/widgetForm/loadingTip/w_LoadingTip.h"

/*
-----==========================================================-----
		�ࣺ		������.h
		���ߣ�		drill_up
		����ģ�飺	������ģ��
		���ܣ�		��������������ƴ��ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/
class DrillPluginInformationReader : public QMainWindow
{
	Q_OBJECT

	public:
		DrillPluginInformationReader(QWidget *parent = 0);
		~DrillPluginInformationReader();
		static DrillPluginInformationReader* cur_instance;		//����
		static DrillPluginInformationReader* getInstance();		//��������ȡ�Լ�
		void _init();											//��ʼ��
		

	//-----------------------------------
	//----�ؼ�
	public:
		W_LoadingTip* m_tip;
		P_InformationPart* m_P_InformationPart;
	public slots:
								//�ؼ� - ��ʾָ�������ϸ��Ϣ
		void showPluginDetail(QString plugin_name);
								//�ؼ� - ˢ�µ���������
		void refreshNav();
								//�ؼ� - �����ĵ�
		void openUserManual();
								//�ؼ� - ����...
		void openAbout();
		
	//-----------------------------------
	//----����
	private:
		C_RmmvProjectData m_temp_data;
	private slots:
								//���� - ѡ�񹤳�
		void btn_selectProject();
								//���� - ���빤��
		void btn_importProject();


	//-----------------------------------
	//----�¼�
	private:
		bool m_inited;
		QSize m_last_uiSize;
	public:
								//�¼� - �����л���С�¼�
		void resizeEvent(QResizeEvent *event);
								//�¼� - ���ڹر��¼�������رհ�ť��
		void closeEvent(QCloseEvent *event);

		
	//-----------------------------------
	//----����
	public:
								//���� - �û��Զ���UI��ȡ
		void ui_loadConfig();
								//���� - �û��Զ���UI�洢
		void ui_saveConfig();
	private:
		Ui::DrillPluginInformationReaderClass ui;
};

#endif // DRILLPLUGININFORMATIONREADER_H
