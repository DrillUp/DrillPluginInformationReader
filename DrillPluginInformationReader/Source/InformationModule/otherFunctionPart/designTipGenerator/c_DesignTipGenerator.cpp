#include "stdafx.h"
#include "c_DesignTipGenerator.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Subsection.h"

/*
-----==========================================================-----
		类：		灵感生成器-插件灵感集合 数据类.cpp
		所属模块：	插件模块
		功能：		灵感生成器中用到的数据。

		说明：		此数据类单独存储，从 已读取的所有插件帮助信息 中进行取材。
-----==========================================================-----
*/
C_DesignTipGenerator::C_DesignTipGenerator(){
	this->tip_list = QList<C_DesignTip_Cell>();
}
C_DesignTipGenerator::~C_DesignTipGenerator(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_DesignTipGenerator::isNull(){
	return this->tip_list.count() == 0;
}
/*-------------------------------------------------
		数据 - 获取单条
*/
C_DesignTip_Cell C_DesignTipGenerator::getCellByIndex(int index){
	if (index >= this->tip_list.count() ){ return C_DesignTip_Cell(); }
	return this->tip_list.at(index);
}
/*-------------------------------------------------
		数据 - 获取数量
*/
int C_DesignTipGenerator::count(){
	return this->tip_list.count();
}
/*-------------------------------------------------
		数据 - 判断是否已含某内容（防止多个插件的设计内容重复）
*/
bool C_DesignTipGenerator::hasContext(QString context){
	if (context.isEmpty()){ return true; }	//（空内容直接判定为已含）
	for (int i = 0; i < this->tip_list.count(); i++){
		C_DesignTip_Cell design_tip = this->tip_list.at(i);
		if (design_tip.context == context){
			return true;
		}
	}
	return false;
}
/*-------------------------------------------------
		数据 - 集合初始化
*/
void C_DesignTipGenerator::initData(){
	
	// > 清空当前容器
	this->tip_list.clear();

	// > 插件数据遍历
	QList<C_ScriptAnnotation> s_data_tank = S_InformationDataContainer::getInstance()->getAnnotationTank();
	for (int i = 0; i < s_data_tank.count(); i++){
		C_ScriptAnnotation s_data = s_data_tank.at(i);

		// > 帮助数据
		C_ScriptHelpDetail* detail = s_data.getScriptHelpDetail();
		if (detail == nullptr){ continue; }

		// > 帮助数据 - 分段说明
		C_ScriptHelp_Subsection* sub = detail->getSubsection();
		if (sub == nullptr){ continue; }
		if (sub->hasDesignTip()){

			C_ScriptHelp_SubsectionPage page = sub->getPage_DesignTip();

			// > 创建设计目录
			for (int j = 0; j < page.context.count(); j++){
				QString context = page.context.at(j);
				if (this->hasContext(context)){		//（重复内容跳过）
					continue;
				}
				C_DesignTip_Cell design_tip = C_DesignTip_Cell();
				design_tip.plugin_name = s_data.getName();
				design_tip.plugin_desc = s_data.getPlugindesc();
				design_tip.context = context;
				this->tip_list.append(design_tip);
			}
		}
	}

	qDebug() << this->tip_list.count();
}