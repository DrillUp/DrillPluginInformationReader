#include "stdafx.h"
#include "p_ScriptHelp_EffectScope.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������ �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		�����ܣ�	��ʾ�ؼ���Ϣ�Ľṹ��
-----==========================================================-----
*/
P_ScriptHelp_EffectScope::P_ScriptHelp_EffectScope(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�ؼ���ʼ��
	this->setData(nullptr);		//����ʼû���κ����ݣ�

	//-----------------------------------
	//----�¼���
	//���ޣ�

}

P_ScriptHelp_EffectScope::~P_ScriptHelp_EffectScope(){
}


/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_EffectScope::setData(C_ScriptHelp_EffectScope* data){
	if (data == nullptr){
		ui.stackedWidget->setCurrentIndex(0);
		return;
	}

	// > ���ֽ���
	if (data->isEnableSenceBattle()){
		ui.toolButton_battle->setEnabled(true);
		ui.toolButton_battle->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Selected.png"));
	}else{
		ui.toolButton_battle->setEnabled(false);
		ui.toolButton_battle->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Error.png"));
	}
	if (data->isEnableSenceMap()){
		ui.toolButton_map->setEnabled(true);
		ui.toolButton_map->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Selected.png"));
	}else{
		ui.toolButton_map->setEnabled(false);
		ui.toolButton_map->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Error.png"));
	}
	if (data->isEnableSenceMenu()){
		ui.toolButton_menu->setEnabled(true);
		ui.toolButton_menu->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Selected.png"));
	}else{
		ui.toolButton_menu->setEnabled(false);
		ui.toolButton_menu->setIcon(QIcon(":/DrillPluginInformationReader/Resources/icons/view/Icon_Error.png"));
	}

	// > ��������
	//QStringList other_list = data->getOtherSence();
	//for (int i = 0; i < other_list.count(); i++){
	//	other_list.at(i);
	//}

	// > ����������
	if (data->comments == ""){
		ui.label_context->setText("û��������������");
	}else{
		ui.label_context->setText(data->comments);
	}

	ui.stackedWidget->setCurrentIndex(1);
}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_EffectScope::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_EffectScope::putUiToData(){
	//�����ޣ�
}