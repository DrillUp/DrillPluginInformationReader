#include "stdafx.h"
#include "p_CommandSearcherPart.h"

#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
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

	// > ָ��ؼ���
	for (int i = 0; i < 30; i++){
		P_ScriptHelp_CommandSearchCell* cell = new P_ScriptHelp_CommandSearchCell();
		if (i% 2 == 0){
			ui.verticalLayout_left->addWidget(cell);
		}else{
			ui.verticalLayout_right->addWidget(cell);
		}
		this->m_cellPartList.append(cell);
	}

	// > ��ʷ��ѯ�ؼ�
	this->m_p_historicalSearchRecord = new P_HistoricalSearchRecord(this);
	ui.horizontalLayout_searchType->removeItem(ui.horizontalSpacer);
	ui.horizontalLayout_searchType->addWidget(this->m_p_historicalSearchRecord);
	ui.horizontalLayout_searchType->addItem(ui.horizontalSpacer);

	// > ��ҳ�ؼ�
	this->m_p_PageNavigator = new P_PageNavigator();
	this->m_p_PageNavigator->initNavigator(30, 30, 5);
	ui.verticalLayout_PageNavigator->addWidget(this->m_p_PageNavigator);


	//-----------------------------------
	//----�¼���

	// > ִ������ʱ
	connect(ui.pushButton_search, &QPushButton::clicked, this, &P_CommandSearcherPart::btn_search);
	connect(this->m_p_historicalSearchRecord, &P_HistoricalSearchRecord::textClicked, this, &P_CommandSearcherPart::searchTextClicked);

	// > ��ҳ�仯ʱ
	connect(this->m_p_PageNavigator, &P_PageNavigator::indexChanged, this, &P_CommandSearcherPart::refreshCellAuto);

}

P_CommandSearcherPart::~P_CommandSearcherPart(){
}


/*-------------------------------------------------
		����ָ�� - ����
*/
void P_CommandSearcherPart::btn_search(){

	this->m_searchText = ui.lineEdit_search->text();
	this->m_allSearchedData = S_InformationDataContainer::getInstance()->getAnnotationTank();
	this->m_p_historicalSearchRecord->addText(m_searchText);

	// > ȫ�����
	QList<C_ScriptAnnotation> data_list = QList<C_ScriptAnnotation>();
	if (this->m_searchText == ""){
		data_list = this->m_allSearchedData;
	}else{
		for (int i = 0; i < this->m_allSearchedData.count(); i++){
			C_ScriptAnnotation data = this->m_allSearchedData.at(i);

			// > ɸѡ����
			if (data.getScriptHelpDetail()->hasCommandKeyWord(m_searchText)){
				data_list.append(data);
			}
		}
	}
	this->m_allSearchedData = data_list;	//���޸����ݷ�Χ��
	this->refreshCellAuto(0, 29);
}

/*-------------------------------------------------
		����ָ�� - ˢ�¿ؼ�
*/
void P_CommandSearcherPart::refreshCellAuto(int start_index, int end_index){
	if (start_index < 0){ start_index = 0; }
	if (end_index <= 0){ return; }

	// > ��ʾ�Ĳ��
	if (end_index >= this->m_allSearchedData.count()){ end_index = this->m_allSearchedData.count() - 1; }
	for (int i = start_index; i <= end_index; i++){
		C_ScriptAnnotation data = this->m_allSearchedData.at(i);
		
		int index = i - start_index;
		P_ScriptHelp_CommandSearchCell* cell_part = this->getButtonPartByIndex(index);
		if (cell_part != nullptr){
			cell_part->setData(data.getScriptHelpDetail()->getCommand(),data.getName()); 
		};
	}

	// > ʣ������
	for (int i = end_index; i < this->m_cellPartList.count(); i++){
		P_ScriptHelp_CommandSearchCell* cell_part = this->getButtonPartByIndex(i);
		if (cell_part != nullptr){
			cell_part->setData(nullptr, "");
		};
	}
}
/*-------------------------------------------------
		����ָ�� - ��ָ���ַ�������
*/
QLabel* P_CommandSearcherPart::getLabelWithSign(QString text, QString searching_text){
	if (text.contains(searching_text) == false){
		return new QLabel(text);
	}
	QStringList data_list = text.split(searching_text);
	QString result_text = "<p>";
	for (int i = 0; i < data_list.count(); i++){
		result_text.append(data_list.at(i));
		if (i < data_list.count()-1){
			result_text.append("<span style=\"background-color:#5fc2ff;\">");
			result_text.append(searching_text);
			result_text.append("</span>");
		}
	}
	result_text.append("<\\p>");
	return new QLabel(result_text);
}

/*-------------------------------------------------
		���� - ��ȡ��ť��
*/
P_ScriptHelp_CommandSearchCell* P_CommandSearcherPart::getButtonPartByIndex(int index){
	if (index < 0){ return nullptr; }
	if (index >= this->m_cellPartList.count()){ return nullptr; }
	return this->m_cellPartList.at(index);
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