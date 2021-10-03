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
		类：		插件信息 编辑块.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	信息模块的主编辑块结构。
					（详细见cpp）
-----==========================================================-----
*/
class P_PluginDetailPart : public QWidget
{
	Q_OBJECT

	public:
		P_PluginDetailPart(QWidget *parent = 0);
		~P_PluginDetailPart();
		
	//-----------------------------------
	//----控件
	public:
		QString m_curPluginName;
		P_ScriptHelp_EffectScope* m_p_ScriptHelp_EffectScope;
		P_ScriptHelp_Subsection* m_p_ScriptHelp_Subsection;
		P_ScriptHelp_Src* m_p_ScriptHelp_Src;
		P_ScriptHelp_Command* m_p_ScriptHelp_Command;
		P_ScriptHelp_Performance* m_p_ScriptHelp_Performance;
		P_ScriptHelp_PluginRelation* m_p_ScriptHelp_PluginRelation;
	public slots: 
										//控件 - 显示指定插件详细信息
		void showPluginDetail(QString plugin_name );

	//-----------------------------------
	//----块
	public:
										//块 - 本地数据 -> ui数据
		void putDataToUi();
										//块 - ui数据 -> 本地数据
		void putUiToData();
	private:
		Ui::P_PluginDetailPart ui;

};

#endif // P_PluginDetailPart_H
