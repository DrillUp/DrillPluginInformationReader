#ifndef W_PluginAttr_HasTool_H
#define W_PluginAttr_HasTool_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttr_HasTool.h"

//#include "Source/InformationModule/pluginDetailPart/helpDetailPart/p_ScriptHelp_HasTool.h"

/*
-----==========================================================-----
		�ࣺ		����˵������ С����֧��.h
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_PluginAttr_HasTool : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttr_HasTool(QWidget *parent = 0);		//���캯��
		~W_PluginAttr_HasTool();							//��������
		
	//-----------------------------------
	//----�ؼ�
	public:
		//P_ScriptHelp_HasTool* m_p_HasTool;
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
		Ui::W_PluginAttr_HasTool ui;
		
};

#endif // W_QExpressionTest_H
