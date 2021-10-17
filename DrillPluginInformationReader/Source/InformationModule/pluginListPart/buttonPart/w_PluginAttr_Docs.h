#ifndef W_PluginAttr_Docs_H
#define W_PluginAttr_Docs_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttr_Docs.h"

#include "Source/InformationModule/pluginDetailPart/helpDetailPart/p_ScriptHelp_Docs.h"

/*
-----==========================================================-----
		�ࣺ		����˵������ ����ĵ�.h
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_PluginAttr_Docs : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttr_Docs(QWidget *parent = 0);		//���캯��
		~W_PluginAttr_Docs();							//��������
		
	//-----------------------------------
	//----�ؼ�
	public:
		P_ScriptHelp_Docs* m_p_docs;
	public:
									//�ؼ� - ��ʾ��Ϣ - �����ĵ�
		void showInformation_word(QString pluginName);
		
	//-----------------------------------
	//----����
									//���� - ��������
									//���� - ��ȡ����
									//���� - �������� -> ui����
									//���� - ui���� -> ��������
									//���� - �ύ���ݣ�У�飩
	private:
		Ui::W_PluginAttr_Docs ui;
		
};

#endif // W_QExpressionTest_H
