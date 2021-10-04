#ifndef P_PluginAttr_ButtonPart_H
#define P_PluginAttr_ButtonPart_H

#include <QtWidgets>
#include "ui_P_PluginAttr_ButtonPart.h"

#include "w_PluginAttrComment.h"

/*
-----==========================================================-----
		�ࣺ		������� ��ť��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	���������ʾ�õİ�ť�顣
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginAttr_ButtonPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginAttr_ButtonPart(W_PluginAttrComment* w,QWidget *parent = 0);
		~P_PluginAttr_ButtonPart();

	//-----------------------------------
	//----�ؼ�
	protected:
		QString m_pluginName;
		W_PluginAttrComment* m_w_PluginAttrComment;	//���ƵĴ���
	public slots:
										//�ؼ� - ���õ�ǰ�����
		void setPluginName(QString pluginName);
										//�ؼ� - ��ȡ��ǰ�����
		QString getPluginName();
										//�ؼ� - ����������ʾ��ť
		void refreshBtnVisible();
										//�ؼ� - ��ť
		void btn_word();
		void btn_src();
		void btn_highConsumption();
		void btn_hasTool();
		void btn_foreignKey();
										//�ؼ� - ȫ������
		void hideAll();
		
	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_PluginAttr_ButtonPart ui;

};

#endif // P_PluginAttr_ButtonPart_H
