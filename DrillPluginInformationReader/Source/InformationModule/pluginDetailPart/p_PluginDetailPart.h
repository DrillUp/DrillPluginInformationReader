#ifndef P_PluginDetailPart_H
#define P_PluginDetailPart_H

#include <QtWidgets>
#include "ui_P_PluginDetailPart.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"

/*
-----==========================================================-----
		�ࣺ		�����Ϣ �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginDetailPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginDetailPart(QWidget *parent = 0);
		~P_PluginDetailPart();
		
	//-----------------------------------
	//----�ؼ�
	public:
		QString m_curPluginName;
	public slots: 
										//�ؼ� - ��ʾָ�������ϸ��Ϣ
		void showPluginDetail(QString plugin_name );

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_PluginDetailPart ui;

};

#endif // P_PluginDetailPart_H
