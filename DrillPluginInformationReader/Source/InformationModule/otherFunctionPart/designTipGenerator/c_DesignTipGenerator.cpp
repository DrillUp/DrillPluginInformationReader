#include "stdafx.h"
#include "c_DesignTipGenerator.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Subsection.h"

/*
-----==========================================================-----
		�ࣺ		���������-�����м��� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������������õ������ݡ�

		˵����		�������൥���洢���� �Ѷ�ȡ�����в��������Ϣ �н���ȡ�ġ�
-----==========================================================-----
*/
C_DesignTipGenerator::C_DesignTipGenerator(){
	this->tip_list = QList<C_DesignTip_Cell>();
}
C_DesignTipGenerator::~C_DesignTipGenerator(){
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_DesignTipGenerator::isNull(){
	return this->tip_list.count() == 0;
}
/*-------------------------------------------------
		���� - ��ȡ����
*/
C_DesignTip_Cell C_DesignTipGenerator::getCellByIndex(int index){
	if (index >= this->tip_list.count() ){ return C_DesignTip_Cell(); }
	return this->tip_list.at(index);
}
/*-------------------------------------------------
		���� - ��ȡ����
*/
int C_DesignTipGenerator::count(){
	return this->tip_list.count();
}
/*-------------------------------------------------
		���� - �ж��Ƿ��Ѻ�ĳ���ݣ���ֹ����������������ظ���
*/
bool C_DesignTipGenerator::hasContext(QString context){
	if (context.isEmpty()){ return true; }	//��������ֱ���ж�Ϊ�Ѻ���
	for (int i = 0; i < this->tip_list.count(); i++){
		C_DesignTip_Cell design_tip = this->tip_list.at(i);
		if (design_tip.context == context){
			return true;
		}
	}
	return false;
}
/*-------------------------------------------------
		���� - ���ϳ�ʼ��
*/
void C_DesignTipGenerator::initData(){
	
	// > ��յ�ǰ����
	this->tip_list.clear();

	// > ������ݱ���
	QList<C_ScriptAnnotation> s_data_tank = S_InformationDataContainer::getInstance()->getAnnotationTank();
	for (int i = 0; i < s_data_tank.count(); i++){
		C_ScriptAnnotation s_data = s_data_tank.at(i);

		// > ��������
		C_ScriptHelpDetail* detail = s_data.getScriptHelpDetail();
		if (detail == nullptr){ continue; }

		// > �������� - �ֶ�˵��
		C_ScriptHelp_Subsection* sub = detail->getSubsection();
		if (sub == nullptr){ continue; }
		if (sub->hasDesignTip()){

			C_ScriptHelp_SubsectionPage page = sub->getPage_DesignTip();

			// > �������Ŀ¼
			for (int j = 0; j < page.context.count(); j++){
				QString context = page.context.at(j);
				if (this->hasContext(context)){		//���ظ�����������
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