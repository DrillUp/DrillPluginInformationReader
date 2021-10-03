#ifndef P_PluginDetailPart_H
#define P_PluginDetailPart_H

#include <QtWidgets>
#include "ui_P_PluginDetailPart.h"

#include "helpDetailPart/p_ScriptHelp_EffectScope.h"
#include "helpDetailPart/p_ScriptHelp_Subsection.h"
#include "helpDetailPart/p_ScriptHelp_Src.h"
#include "helpDetailPart/p_ScriptHelp_Command.h"
#include "helpDetailPart/p_ScriptHelp_Performance.h"
#include "helpDetailPart/p_ScriptHelp_PluginRelation.h"
#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"

/*
-----==========================================================-----
		�ࣺ		�����Ϣ �༭��.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_PluginDetailPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginDetailPart(QWidget *parent = 0);
		~P_PluginDetailPart();
		
	//-----------------------------------
	//----�ؼ�
	public:
		QString m_curPluginName;
		P_ScriptHelp_EffectScope* m_p_ScriptHelp_EffectScope;
		P_ScriptHelp_Subsection* m_p_ScriptHelp_Subsection;
		P_ScriptHelp_Src* m_p_ScriptHelp_Src;
		P_ScriptHelp_Command* m_p_ScriptHelp_Command;
		P_ScriptHelp_Performance* m_p_ScriptHelp_Performance;
		P_ScriptHelp_PluginRelation* m_p_ScriptHelp_PluginRelation;
	public slots: 
										//�ؼ� - ��ʾָ�������ϸ��Ϣ
		void showPluginDetail(QString plugin_name );

	//-----------------------------------
	//----��
	public:
										//�� - �������� -> ui����
		void putDataToUi();
										//�� - ui���� -> ��������
		void putUiToData();
	private:
		Ui::P_PluginDetailPart ui;

};

#endif // P_PluginDetailPart_H
