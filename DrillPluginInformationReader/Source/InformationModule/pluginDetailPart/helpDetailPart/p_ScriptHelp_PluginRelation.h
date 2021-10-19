#ifndef P_ScriptHelp_PluginRelation_H
#define P_ScriptHelp_PluginRelation_H

#include <QtWidgets>
#include "ui_P_ScriptHelp_PluginRelation.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_PluginRelation.h"

/*
-----==========================================================-----
		�ࣺ		�����չ �ؼ���.h
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		
		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ScriptHelp_PluginRelation : public QWidget
{
	Q_OBJECT

	public:
		P_ScriptHelp_PluginRelation(QWidget *parent = 0);
		~P_ScriptHelp_PluginRelation();
		
	//-----------------------------------
	//----�ؼ�
	public:
		QList<QLabel*> m_labelTank;
	public slots: 
										//�ؼ� - ���ȫ���ӿؼ�
		void clearAllChild();
										//�ؼ� - ���ӱ����
		void linkClicked_plugin(QString data);
	protected:
										//�ؼ� - ����Ⱥ��ؼ�
		void addGroupWidget(QString title,QStringList context);

	//-----------------------------------
	//----��
	public:
										//�� - ��������
		void setData(C_ScriptHelp_PluginRelation* data);
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_ScriptHelp_PluginRelation ui;

};

#endif // P_ScriptHelp_PluginRelation_H
