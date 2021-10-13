#include "stdafx.h"
#include "p_CommandSearcherPart.h"

#include "Source/ProjectModule/storageGlobal/s_IniManager.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		ָ�������� �༭��.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	��Ϣģ������༭��ṹ��
					
-----==========================================================-----
*/
P_CommandSearcherPart::P_CommandSearcherPart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----��ʼ������


	//-----------------------------------
	//----�ؼ���ʼ��
	TTool::_ChangeCombox_itemHeight_(ui.comboBox_commandType, 30);

	// > ��ʷ��ѯ�ؼ�
	this->m_p_historicalSearchRecord = new P_HistoricalSearchRecord(this);
	ui.horizontalLayout_searchType->removeItem(ui.horizontalSpacer);
	ui.horizontalLayout_searchType->addWidget(this->m_p_historicalSearchRecord);
	ui.horizontalLayout_searchType->addItem(ui.horizontalSpacer);

	// > ��ҳ�ؼ�
	this->m_p_PageNavigator = new P_PageNavigator();
	this->m_p_PageNavigator->initNavigator(100, 100, 5);
	ui.verticalLayout_PageNavigator->addWidget(this->m_p_PageNavigator);


	//-----------------------------------
	//----�¼���

	// > ִ������ʱ
	connect(this->m_p_historicalSearchRecord, &P_HistoricalSearchRecord::textClicked, this, &P_CommandSearcherPart::searchTextClicked);

	// > ��ҳ�仯ʱ
	//connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &P_CommandSearcherPart::refreshTableAuto);


}

P_CommandSearcherPart::~P_CommandSearcherPart(){
}


/*-------------------------------------------------
		�ؼ� - �������ַ��������
*/
void P_CommandSearcherPart::searchTextClicked(QString text){
	ui.lineEdit_search->setText(text);
}

/*-------------------------------------------------
		�� - �û��Զ���UI��ȡ
*/
void P_CommandSearcherPart::ui_loadConfig(){

	QString search_str = S_IniManager::getInstance()->getConfig("PIR_CommandSearcher_search");
	this->m_p_historicalSearchRecord->setData(search_str.split("|||"));
}
/*-------------------------------------------------
		�� - �û��Զ���UI�洢
*/
void P_CommandSearcherPart::ui_saveConfig(){

	QStringList search_list = this->m_p_historicalSearchRecord->getData();
	S_IniManager::getInstance()->setConfig("PIR_CommandSearcher_search", search_list.join("|||"));
}