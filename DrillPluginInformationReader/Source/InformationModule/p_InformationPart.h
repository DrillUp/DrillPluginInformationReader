#ifndef P_InformationPart_H
#define P_InformationPart_H

#include <QtWidgets>
#include "ui_P_InformationPart.h"
#include "Source/Utils/widgetForm/foldableTabWindow/p_FoldableTabRelater.h"

/*
-----==========================================================-----
		�ࣺ		��Ϣģ�� ���༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginListPart;
class P_PluginDetailPart;
class P_CommandSearcherPart;
class P_OtherFunctionPart;
class P_DesignTipGeneratorPart;
class P_InformationPart : public QWidget
{
	Q_OBJECT

	public:
		P_InformationPart(QWidget *parent = 0);
		~P_InformationPart();
		
	//-----------------------------------
	//----��ؼ�
	public:
		P_FoldableTabRelater* m_p_FoldableTabRelater;	//���۵�ѡ�
		
		P_PluginListPart* m_p_pluginListPart;
		P_PluginDetailPart* m_p_pluginDetailPart;
		P_CommandSearcherPart* m_p_commandSearcherPart;
		P_OtherFunctionPart* m_p_otherFunctionPart;
	public slots:
										//�ؼ� - ��ʾָ�������ϸ��Ϣ
		void showPluginDetail(QString plugin_name );
		
	//-----------------------------------
	//----�����ؼ�
	public:
		P_DesignTipGeneratorPart* m_p_DesignTipGenerator;
	public slots:
										//�ؼ� - ѡ�� ���������
		void selectPart_DesignTipGenerator();
										//�ؼ� - ���� ���������
		void createPart_DesignTipGenerator();

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_InformationPart ui;

};

#endif // P_InformationPart_H
