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
	//----�¼���
	connect(ui.label_pluginName_A, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_B, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_C, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_D, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_E, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);

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
	ui.groupBox_A->setVisible(false);
	ui.groupBox_B->setVisible(false);
	ui.groupBox_C->setVisible(false);
	ui.groupBox_D->setVisible(false);
	ui.groupBox_E->setVisible(false);
}
/*-------------------------------------------------
		�ؼ� - �����ʾ����
*/
void P_ScriptHelp_CommandSearchCell::addOneChildData(QString type_name, QString plugin_tagText, QString context_tagText){
	if (ui.groupBox_A->isVisible() == false){
		ui.groupBox_A->setTitle(type_name);
		this->refreshStyle(ui.groupBox_A, type_name);
		ui.label_pluginName_A->setText(plugin_tagText);
		ui.label_context_A->setText(context_tagText);
		ui.groupBox_A->setVisible(true);
	}
	else if (ui.groupBox_B->isVisible() == false){
		ui.groupBox_B->setTitle(type_name);
		this->refreshStyle(ui.groupBox_B, type_name);
		ui.label_pluginName_B->setText(plugin_tagText);
		ui.label_context_B->setText(context_tagText);
		ui.groupBox_B->setVisible(true);
	}
	else if (ui.groupBox_C->isVisible() == false){
		ui.groupBox_C->setTitle(type_name);
		this->refreshStyle(ui.groupBox_C, type_name);
		ui.label_pluginName_C->setText(plugin_tagText);
		ui.label_context_C->setText(context_tagText);
		ui.groupBox_C->setVisible(true);
	}
	else if (ui.groupBox_D->isVisible() == false){
		ui.groupBox_D->setTitle(type_name);
		this->refreshStyle(ui.groupBox_D, type_name);
		ui.label_pluginName_D->setText(plugin_tagText);
		ui.label_context_D->setText(context_tagText);
		ui.groupBox_D->setVisible(true);
	}
	else if (ui.groupBox_E->isVisible() == false){
		ui.groupBox_E->setTitle(type_name);
		this->refreshStyle(ui.groupBox_E, type_name);
		ui.label_pluginName_E->setText(plugin_tagText);
		ui.label_context_E->setText(context_tagText);
		ui.groupBox_E->setVisible(true);
	}
}
/*-------------------------------------------------
		�ؼ� - ��������ˢ����ʽ
*/
void P_ScriptHelp_CommandSearchCell::refreshStyle(QGroupBox* groupBox, QString type_name){
	if (type_name == "���ָ��"){
		groupBox->setStyleSheet("QGroupBox{ color:#449ed4; border: 1px solid #449ed4; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFBFF, stop:1 #F0F3FE); }");
	}
	if (type_name == "�¼�ע��"){
		groupBox->setStyleSheet("QGroupBox{ color:#44c49e; border: 1px solid #44c49e; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFFFB, stop:1 #F0FEF3); }");
	}
	if (type_name == "��ͼ��ע"){
		groupBox->setStyleSheet("QGroupBox{ color:#008000; border: 1px solid #008000; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFFFB, stop:1 #F0FEF3); }");
	}
	if (type_name == "��ɫע��" || type_name == "����ע��" || type_name == "״̬ע��" || type_name == "����ע��"){
		groupBox->setStyleSheet("QGroupBox{ color:#FF7F27; border: 1px solid #FF7F27; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFAF1, stop:1 #FEFEF0); }");
	}
	if (type_name == "��Ʒ/����/����ע��" || type_name == "�ƶ�·��ָ��"){
		groupBox->setStyleSheet("QGroupBox{ color:#d4449e; border: 1px solid #d4449e; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FFFAFB, stop:1 #FEF0F3); }");
	}
	if (type_name == "���ָ��(��)"  || type_name == "�¼�ע��(��)" ){
		groupBox->setStyleSheet("QGroupBox{ color:#989898; border: 1px solid #989898; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFBFA, stop:1 #E5E5E5); }");
	}
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
void P_ScriptHelp_CommandSearchCell::setData(C_ScriptHelp_Command* data, QString plugin_name, QString plugin_desc, QString search_text, QString search_type){
	this->clearAllChild();
	if (data == nullptr){ return; }
	if (data->isNull()){ return; }
	if (plugin_name.isEmpty()){ return; }

	// > ������� ��ǩ�ı�
	QString plugin_text = "<p>���������<a href=\"";
	plugin_text.append(plugin_name);
	plugin_text.append("\"><span style=\"text-decoration: underline; color:#0000ff; \">");
	plugin_text.append(plugin_name);
	plugin_text.append("</span></a>");
	plugin_text.append(" ");
	plugin_text.append(plugin_desc);
	plugin_text.append("��< / p>");
	
	// > ָ�� - ���ָ��
	if ((search_type == "ȫ������" || search_type == "���ָ��") &&
		data->hasCommandKeyWord_PluginCommand(search_text)){
		QStringList command_list = data->getAllCommand_PluginCommand();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("���ָ��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - �¼�ע��
	if ((search_type == "ȫ������" || search_type == "�¼�ע��") && 
		data->hasCommandKeyWord_EventComment(search_text)){
		QStringList command_list = data->getAllCommand_EventComment();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("�¼�ע��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - ��ͼ��ע
	if ((search_type == "ȫ������" || search_type == "��ͼ��ע") && 
		data->hasCommandKeyWord_MapNote(search_text)){
		QStringList command_list = data->getAllCommand_MapNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("��ͼ��ע", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - ��ɫע��
	if ((search_type == "ȫ������" || search_type == "��ɫע��") && 
		data->hasCommandKeyWord_ActorNote(search_text)){
		QStringList command_list = data->getAllCommand_ActorNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("��ɫע��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - ����ע��
	if ((search_type == "ȫ������" || search_type == "����ע��") && 
		data->hasCommandKeyWord_EnemyNote(search_text)){
		QStringList command_list = data->getAllCommand_EnemyNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("����ע��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - ״̬ע��
	if ((search_type == "ȫ������" || search_type == "״̬ע��") &&
		data->hasCommandKeyWord_StateNote(search_text)){
		QStringList command_list = data->getAllCommand_StateNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("״̬ע��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - ��Ʒ/����/����ע��
	if ((search_type == "ȫ������" || search_type == "��Ʒ/����/����ע��") &&
		data->hasCommandKeyWord_StateNote(search_text)){
		QStringList command_list = data->getAllCommand_ItemNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("��Ʒ/����/����ע��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - ����ע��
	if ((search_type == "ȫ������" || search_type == "����ע��") &&
		data->hasCommandKeyWord_StateNote(search_text)){
		QStringList command_list = data->getAllCommand_SkillNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("����ע��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - �ƶ�·��ָ��
	if ((search_type == "ȫ������" || search_type == "�ƶ�·��ָ��") && 
		data->hasCommandKeyWord_MoveRoute(search_text)){
		QStringList command_list = data->getAllCommand_MoveRoute();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("�ƶ�·��ָ��", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - ���ָ��(��)
	if (search_type == "ȫ������" && 
		data->hasCommandKeyWord_PluginCommandOld(search_text)){
		QStringList command_list = data->getAllCommand_PluginCommandOld();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("���ָ��(��)", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > ָ�� - �¼�ע��(��)
	if (search_type == "ȫ������" && 
		data->hasCommandKeyWord_EventCommentOld(search_text)){
		QStringList command_list = data->getAllCommand_EventCommentOld();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("�¼�ע��(��)", plugin_text, this->getStringWithSign(context_text, search_text));
	}
}
/*-------------------------------------------------
		����ָ�� - ��ָ���ַ�������
*/
QString P_ScriptHelp_CommandSearchCell::getStringWithSign(QString text, QString searching_text){
	if (searching_text.isEmpty()){
		return text;
	}
	if (text.contains(searching_text) == false){
		return "";
	}
	QStringList data_list = text.split(searching_text);
	QString result_text;
	for (int i = 0; i < data_list.count(); i++){
		result_text.append(data_list.at(i));
		if (i < data_list.count()-1){
			result_text.append("<span style=\"background-color:#5fc2ff;\">");
			result_text.append(searching_text);
			result_text.append("</span>");
		}
	}
	return result_text;
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