#include "stdafx.h"
#include "p_ScriptHelp_CommandSearchCell.h"

#include "drillplugininformationreader.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		ָ�� �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		˵����		��ʾ�ؼ� ָ�� ��Ϣ�Ľṹ��
					��ע�⣬������Ҫ������ѯ����ô��һ����Ҫ����ʱnew�Ŀؼ����������ֳɵĿؼ������ݡ�
-----==========================================================-----
*/
P_ScriptHelp_CommandSearchCell::P_ScriptHelp_CommandSearchCell(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�ؼ���ʼ��
	this->clearAllChild();
}

P_ScriptHelp_CommandSearchCell::~P_ScriptHelp_CommandSearchCell(){
}

/*-------------------------------------------------
		�ؼ� - ���ȫ�����ݣ���ɾ���ؼ���
*/
void P_ScriptHelp_CommandSearchCell::clearAllChild(){

	// > �Ͽ�����
	

}
/*-------------------------------------------------
		�ؼ� - ���ӱ����
*/
void P_ScriptHelp_CommandSearchCell::linkClicked_plugin(QString data){
	DrillPluginInformationReader::getInstance()->showPluginDetail(data);
}

/*-------------------------------------------------
		�� - ��������
*/
void P_ScriptHelp_CommandSearchCell::setData(C_ScriptHelp_Command* data, QString plugin_name){
	this->clearAllChild();
	if (data == nullptr){ return; }
	if (data->isNull()){ return; }
	if (plugin_name.isEmpty()){ return; }


}
/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_ScriptHelp_CommandSearchCell::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_ScriptHelp_CommandSearchCell::putUiToData(){
	//�����ޣ�
}