#ifndef W_PluginAttr_HighConsumption_H
#define W_PluginAttr_HighConsumption_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttr_HighConsumption.h"

//#include "Source/InformationModule/pluginDetailPart/helpDetailPart/p_ScriptHelp_HighConsumption.h"

/*
-----==========================================================-----
		�ࣺ		����˵������ ������.h
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_PluginAttr_HighConsumption : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttr_HighConsumption(QWidget *parent = 0);		//���캯��
		~W_PluginAttr_HighConsumption();							//��������
		
	//-----------------------------------
	//----�ؼ�
	public:
		//P_ScriptHelp_HighConsumption* m_p_HighConsumption;
	public:
									//�ؼ� - ��ʾ��Ϣ - �����ĵ�
		//void showInformation_word(QString pluginName);
		
	//-----------------------------------
	//----����
									//���� - ��������
									//���� - ��ȡ����
									//���� - �������� -> ui����
									//���� - ui���� -> ��������
									//���� - �ύ���ݣ�У�飩
	private:
		Ui::W_PluginAttr_HighConsumption ui;
		
};

#endif // W_QExpressionTest_H