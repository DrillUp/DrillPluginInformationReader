#ifndef P_PluginDetailPart_H
#define P_PluginDetailPart_H

#include <QtWidgets>
#include "ui_P_PluginDetailPart.h"

#include "helpDetailPart/p_ScriptHelp_EffectScope.h"
#include "helpDetailPart/p_ScriptHelp_PluginRelation.h"
#include "helpDetailPart/p_ScriptHelp_Subsection.h"
#include "helpDetailPart/p_ScriptHelp_Src.h"
#include "helpDetailPart/p_ScriptHelp_Command.h"
#include "helpDetailPart/p_ScriptHelp_Knowledge.h"
#include "helpDetailPart/p_ScriptHelp_Performance.h"
#include "Source/RmmvInteractiveModule/InformationData/S_InformationDataContainer.h"

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
		QString m_curOrgContext;
		P_ScriptHelp_EffectScope* m_p_ScriptHelp_EffectScope;
		P_ScriptHelp_PluginRelation* m_p_ScriptHelp_PluginRelation;
		P_ScriptHelp_Subsection* m_p_ScriptHelp_Subsection;
		P_ScriptHelp_Src* m_p_ScriptHelp_Src;
		P_ScriptHelp_Command* m_p_ScriptHelp_Command;
		P_ScriptHelp_Knowledge* m_p_ScriptHelp_Knowledge;
		P_ScriptHelp_Performance* m_p_ScriptHelp_Performance;
	public slots: 
										//控件 - 显示指定插件详细信息
		void showPluginDetail(QString plugin_name );
										//控件 - 编辑插件
		void btn_editPlugin();
										//控件 - 展开原文
		void btn_expandOrg();
	signals:
										//控件 - 选择 展开原文
		void selected_PluginDetailOrgContextPart();
										//控件 - 原文变化
		void orgContextChanged(QString context);

	//-----------------------------------
	//----块
	public:
										//块 - 用户自定义UI读取
		void ui_loadConfig();
										//块 - 用户自定义UI存储
		void ui_saveConfig();
	private:
		Ui::P_PluginDetailPart ui;

};

#endif // P_PluginDetailPart_H
