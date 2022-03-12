#include "stdafx.h"
#include "p_DesignTip_Cell.h"

#include "drillplugininformationreader.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		���������-���� �ؼ���.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		˵����		��ʾ�ؼ� ���������-���� ��Ϣ�Ľṹ��
-----==========================================================-----
*/
P_DesignTip_Cell::P_DesignTip_Cell(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----�¼���
	connect(ui.label_pluginName_A, &QLabel::linkActivated, this, &P_DesignTip_Cell::linkClicked_plugin);

	//-----------------------------------
	//----�ؼ���ʼ��
}

P_DesignTip_Cell::~P_DesignTip_Cell(){
}

/*-------------------------------------------------
		�ؼ� - ���ӱ����
*/
void P_DesignTip_Cell::linkClicked_plugin(QString data){
	DrillPluginInformationReader::getInstance()->showPluginDetail(data);
}

/*-------------------------------------------------
		�� - ��������
*/
void P_DesignTip_Cell::setData(C_DesignTip_Cell data){

	// > ������� ��ǩ�ı�
	QString plugin_text = "<p>���������<a href=\"";
	plugin_text.append(data.plugin_name);
	plugin_text.append("\"><span style=\"text-decoration: underline; color:#0000ff; \">");
	plugin_text.append(data.plugin_name);
	plugin_text.append("</span></a>");
	plugin_text.append(" ");
	plugin_text.append(data.plugin_desc);
	plugin_text.append("��< / p>");
	ui.label_pluginName_A->setText(plugin_text);

	// > ����
	ui.label_context_A->setText(data.context);
}

/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_DesignTip_Cell::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_DesignTip_Cell::putUiToData(){
	//�����ޣ�
}