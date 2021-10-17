#include "stdafx.h"
#include "p_PluginAttr_ButtonPart.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������� ��ť��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		˵����		���������ʾ�õİ�ť�顣
-----==========================================================-----
*/
P_PluginAttr_ButtonPart::P_PluginAttr_ButtonPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������
	this->m_w_PluginAttr_Docs = nullptr;
	this->m_w_PluginAttr_Src = nullptr;
	this->m_w_PluginAttr_HighConsumption = nullptr;
	this->m_w_PluginAttr_HasTool = nullptr;
	this->m_w_PluginAttr_ForeignKey = nullptr;

	//-----------------------------------
	//----��ʼ��ui
	ui.toolButton_src->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_src.png"));
	ui.toolButton_word->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_word.png"));
	ui.toolButton_highConsumption->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_highConsumption.png"));
	ui.toolButton_hasTool->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_hasTool.png"));
	ui.toolButton_foreignKey->setIcon(QIcon(QRC_IconSrcPath + "/menu/attr_foreignKey.png"));

	//-----------------------------------
	//----�¼���
	connect(ui.toolButton_word, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_docs);
	connect(ui.toolButton_src, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_src);
	connect(ui.toolButton_highConsumption, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_highConsumption);
	connect(ui.toolButton_hasTool, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_hasTool);
	connect(ui.toolButton_foreignKey, &QToolButton::clicked, this, &P_PluginAttr_ButtonPart::btn_foreignKey);

}

P_PluginAttr_ButtonPart::~P_PluginAttr_ButtonPart(){
}


/*-------------------------------------------------
		�ؼ� - ����ȫ��
*/
void P_PluginAttr_ButtonPart::hideAll(){
	ui.toolButton_src->hide();
	ui.toolButton_word->hide();
	ui.toolButton_highConsumption->hide();
	ui.toolButton_hasTool->hide();
	ui.toolButton_foreignKey->hide();
}

/*-------------------------------------------------
		�ؼ� - ���õ�ǰ�����
*/
void P_PluginAttr_ButtonPart::setPluginName(QString pluginName){
	this->m_pluginName = pluginName;
	this->refreshBtnVisible();
}
/*-------------------------------------------------
		�ؼ� - ��ȡ��ǰ�����
*/
QString P_PluginAttr_ButtonPart::getPluginName(){
	return this->m_pluginName;
}
/*-------------------------------------------------
		�ؼ� - ����������ʾ��ť
*/
void P_PluginAttr_ButtonPart::refreshBtnVisible(){
	this->hideAll();
	C_ScriptHelpDetail* detail = S_InformationDataContainer::getInstance()->getHelpDetail(this->m_pluginName);
	if (detail == nullptr){ return; }

	// > ��Դ·��
	ui.toolButton_src->setVisible(detail->getSrc() != nullptr);

	// > ����ĵ�����������һ��ʼ�ʹ����ˣ�
	ui.toolButton_word->setVisible(detail->getDocs()->hasAnyDocx());

	// > ������
	C_ScriptHelp_Performance* performance = detail->getPerformance();
	if (performance != nullptr &&
		performance->isHighCost()){
		ui.toolButton_highConsumption->setVisible(true);
	}
	
	// > С����֧��
	//...

	// > ���
	//...

}
/*-------------------------------------------------
		�ؼ� - ��Դ��ť
*/
void P_PluginAttr_ButtonPart::setWindowDocs(W_PluginAttr_Docs* w){
	this->m_w_PluginAttr_Docs = w;
}
void P_PluginAttr_ButtonPart::setWindowSrc(W_PluginAttr_Src* w){
	this->m_w_PluginAttr_Src = w;
}
void P_PluginAttr_ButtonPart::setWindowHighConsumption(W_PluginAttr_HighConsumption* w){
	this->m_w_PluginAttr_HighConsumption = w;
}
void P_PluginAttr_ButtonPart::setWindowHasTool(W_PluginAttr_HasTool* w){
	this->m_w_PluginAttr_HasTool = w;
}
void P_PluginAttr_ButtonPart::setWindowForeignKey(W_PluginAttr_ForeignKey* w){
	this->m_w_PluginAttr_ForeignKey = w;
}

/*-------------------------------------------------
		�ؼ� - ��Դ��ť
*/
void P_PluginAttr_ButtonPart::btn_docs(){
	if (this->m_w_PluginAttr_Docs == nullptr){ return; }
	this->m_w_PluginAttr_Docs->showInformation_word(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_Docs);
}
void P_PluginAttr_ButtonPart::btn_src(){
	if (this->m_w_PluginAttr_Src == nullptr){ return; }
	this->m_w_PluginAttr_Src->showInformation_src(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_Src);
}
void P_PluginAttr_ButtonPart::btn_highConsumption(){
	if (this->m_w_PluginAttr_HighConsumption == nullptr){ return; }
	//this->m_w_PluginAttr_HighConsumption->showInformation_highConsumption(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_HighConsumption);
}
void P_PluginAttr_ButtonPart::btn_hasTool(){
	if (this->m_w_PluginAttr_HasTool == nullptr){ return; }
	//this->m_w_PluginAttr_HasTool->showInformation_hasTool(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_HasTool);
}
void P_PluginAttr_ButtonPart::btn_foreignKey(){
	if (this->m_w_PluginAttr_ForeignKey == nullptr){ return; }
	//this->m_w_PluginAttr_ForeignKey->showInformation_foreignKey(this->m_pluginName);
	this->showWindowAlone(this->m_w_PluginAttr_ForeignKey);
}
/*-------------------------------------------------
		�ؼ� - ��ʾ��һ����
*/
void P_PluginAttr_ButtonPart::showWindowAlone(QDialog* w){
	if (this->m_w_PluginAttr_Docs == nullptr){ return; }
	if (this->m_w_PluginAttr_Src == nullptr){ return; }
	if (this->m_w_PluginAttr_HighConsumption == nullptr){ return; }
	if (this->m_w_PluginAttr_HasTool == nullptr){ return; }
	if (this->m_w_PluginAttr_ForeignKey == nullptr){ return; }
	
	if (this->m_w_PluginAttr_Docs == w){
		this->m_w_PluginAttr_Docs->show();
	}else{
		this->m_w_PluginAttr_Docs->close();
	}
	if (this->m_w_PluginAttr_Src == w){
		this->m_w_PluginAttr_Src->show();
	}else{
		this->m_w_PluginAttr_Src->close();
	}
	if (this->m_w_PluginAttr_HighConsumption == w){
		this->m_w_PluginAttr_HighConsumption->show();
	}else{
		this->m_w_PluginAttr_HighConsumption->close();
	}
	if (this->m_w_PluginAttr_HasTool == w){
		this->m_w_PluginAttr_HasTool->show();
	}else{
		this->m_w_PluginAttr_HasTool->close();
	}
	if (this->m_w_PluginAttr_ForeignKey == w ){
		this->m_w_PluginAttr_ForeignKey->show();
	}else{
		this->m_w_PluginAttr_ForeignKey->close();
	}
}


/*-------------------------------------------------
		�� - �������� -> ui����
*/
void P_PluginAttr_ButtonPart::putDataToUi(){
	//�����ޣ�
}
/*-------------------------------------------------
		�� - ui���� -> ��������
*/
void P_PluginAttr_ButtonPart::putUiToData(){
	//�����ޣ�
}