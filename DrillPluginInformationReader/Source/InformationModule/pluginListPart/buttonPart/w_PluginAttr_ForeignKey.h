#ifndef W_PluginAttr_ForeignKey_H
#define W_PluginAttr_ForeignKey_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttr_ForeignKey.h"

//#include "Source/InformationModule/pluginDetailPart/helpDetailPart/p_ScriptHelp_ForeignKey.h"

/*
-----==========================================================-----
		�ࣺ		����˵������ ���.h
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_PluginAttr_ForeignKey : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttr_ForeignKey(QWidget *parent = 0);		//���캯��
		~W_PluginAttr_ForeignKey();							//��������
		
	//-----------------------------------
	//----�ؼ�
	public:
		//P_ScriptHelp_ForeignKey* m_p_ForeignKey;
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
		Ui::W_PluginAttr_ForeignKey ui;
		
};

#endif // W_QExpressionTest_H
