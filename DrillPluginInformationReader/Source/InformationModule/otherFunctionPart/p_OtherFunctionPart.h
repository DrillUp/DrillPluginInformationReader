#ifndef P_OtherFunctionPart_H
#define P_OtherFunctionPart_H

#include <QtWidgets>
#include "ui_P_OtherFunctionPart.h"

/*
-----==========================================================-----
		�ࣺ		�������� �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�������ܵı༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_OtherFunctionPart : public QWidget
{
	Q_OBJECT

	public:
		P_OtherFunctionPart(QWidget *parent = 0);
		~P_OtherFunctionPart();
		
	//-----------------------------------
	//----�ؼ�
	public slots:
										//�ؼ� - ѡ�� ���������
		void btn_DesignTipGenerator();
										//�ؼ� - ѡ�� ���������������δʹ�õĲ����
		void btn_PluginBatchDelete();
										//�ؼ� - ѡ�� ���������
		void btn_PluginBatchUpdate();
										//�ؼ� - ѡ�� �汾��־
		void btn_VersionLog();
										//�ؼ� - ���� ����嵥
		void btn_ExcelPluginList();
										//�ؼ� - ���� ���ʾ��λ�ñ�
		void btn_ExcelMapPosList();
	signals: 
										//�ؼ� - ѡ�� ���������
		void selected_DesignTipGenerator();

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_OtherFunctionPart ui;

};

#endif // P_OtherFunctionPart_H
