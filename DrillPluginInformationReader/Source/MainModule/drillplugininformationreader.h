#ifndef DRILLPLUGININFORMATIONREADER_H
#define DRILLPLUGININFORMATIONREADER_H

#include <QtWidgets/QMainWindow>
#include "ui_drillplugininformationreader.h"
#include "Source/InformationModule/p_InformationPart.h"

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
		P_InformationPart* m_P_InformationPart;
	public slots:
								//�ؼ� - �����ĵ�
		void openUserManual();
								//�ؼ� - ����...
		void openAbout();

		
	//-----------------------------------
	//----����
	private:
		Ui::DrillPluginInformationReaderClass ui;
};

#endif // DRILLPLUGININFORMATIONREADER_H
