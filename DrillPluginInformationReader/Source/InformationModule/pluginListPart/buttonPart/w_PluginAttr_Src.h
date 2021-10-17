#ifndef W_PluginAttr_Src_H
#define W_PluginAttr_Src_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttr_Src.h"

#include "Source/InformationModule/pluginDetailPart/helpDetailPart/p_ScriptHelp_Src.h"

/*
-----==========================================================-----
		�ࣺ		����˵������ ��Դ·��.h
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_PluginAttr_Src : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttr_Src(QWidget *parent = 0);		//���캯��
		~W_PluginAttr_Src();							//��������
		
	//-----------------------------------
	//----�ؼ�
	public:
		P_ScriptHelp_Src* m_p_src;
	public:
									//�ؼ� - ��ʾ��Ϣ - ��Դ·��
		void showInformation_src(QString pluginName);
		
	//-----------------------------------
	//----����
									//���� - ��������
									//���� - ��ȡ����
									//���� - �������� -> ui����
									//���� - ui���� -> ��������
									//���� - �ύ���ݣ�У�飩
	private:
		Ui::W_PluginAttr_Src ui;
		
};

#endif // W_QExpressionTest_H
