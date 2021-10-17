#ifndef P_PluginAttr_ButtonPart_H
#define P_PluginAttr_ButtonPart_H

#include <QtWidgets>
#include "ui_P_PluginAttr_ButtonPart.h"

#include "w_PluginAttr_Docs.h"
#include "w_PluginAttr_Src.h"
#include "w_PluginAttr_HighConsumption.h"
#include "w_PluginAttr_HasTool.h"
#include "w_PluginAttr_ForeignKey.h"

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
		P_PluginAttr_ButtonPart(QWidget *parent = 0);
		~P_PluginAttr_ButtonPart();

	//-----------------------------------
	//----�ؼ�
	protected:
		QString m_pluginName;
		W_PluginAttr_Docs* m_w_PluginAttr_Docs;							//���ƵĴ���
		W_PluginAttr_Src* m_w_PluginAttr_Src;							//���ƵĴ���
		W_PluginAttr_HighConsumption* m_w_PluginAttr_HighConsumption;	//���ƵĴ���
		W_PluginAttr_HasTool* m_w_PluginAttr_HasTool;					//���ƵĴ���
		W_PluginAttr_ForeignKey* m_w_PluginAttr_ForeignKey;				//���ƵĴ���
	public slots:
										//�ؼ� - ���õ�ǰ�����
		void setPluginName(QString pluginName);
										//�ؼ� - ��ȡ��ǰ�����
		QString getPluginName();
										//�ؼ� - ����������ʾ��ť
		void refreshBtnVisible();
										//�ؼ� - ��������
		void setWindowDocs(W_PluginAttr_Docs* w);
		void setWindowSrc(W_PluginAttr_Src* w);
		void setWindowHighConsumption(W_PluginAttr_HighConsumption* w);
		void setWindowHasTool(W_PluginAttr_HasTool* w);
		void setWindowForeignKey(W_PluginAttr_ForeignKey* w);
										//�ؼ� - ��ʾ��һ����
		void showWindowAlone(QDialog* w);
										//�ؼ� - ��ť
		void btn_docs();
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
