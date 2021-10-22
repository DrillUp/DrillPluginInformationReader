#include "stdafx.h"
#include "p_ScriptHelp_CommandSearchCell.h"

#include "drillplugininformationreader.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		指令 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块
		说明：		显示控件 指令 信息的结构。
					【注意，由于需要反复查询，那么就一定不要用临时new的控件，必须用现成的控件填内容】
-----==========================================================-----
*/
P_ScriptHelp_CommandSearchCell::P_ScriptHelp_CommandSearchCell(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----事件绑定
	connect(ui.label_pluginName_A, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_B, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_C, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_D, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);
	connect(ui.label_pluginName_E, &QLabel::linkActivated, this, &P_ScriptHelp_CommandSearchCell::linkClicked_plugin);

	//-----------------------------------
	//----控件初始化
	this->clearAllChild();
}

P_ScriptHelp_CommandSearchCell::~P_ScriptHelp_CommandSearchCell(){
}

/*-------------------------------------------------
		控件 - 清空全部内容（不删除控件）
*/
void P_ScriptHelp_CommandSearchCell::clearAllChild(){
	ui.groupBox_A->setVisible(false);
	ui.groupBox_B->setVisible(false);
	ui.groupBox_C->setVisible(false);
	ui.groupBox_D->setVisible(false);
	ui.groupBox_E->setVisible(false);
}
/*-------------------------------------------------
		控件 - 添加显示数据
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
		控件 - 根据名称刷新样式
*/
void P_ScriptHelp_CommandSearchCell::refreshStyle(QGroupBox* groupBox, QString type_name){
	if (type_name == "插件指令"){
		groupBox->setStyleSheet("QGroupBox{ color:#449ed4; border: 1px solid #449ed4; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFBFF, stop:1 #F0F3FE); }");
	}
	if (type_name == "事件注释"){
		groupBox->setStyleSheet("QGroupBox{ color:#44c49e; border: 1px solid #44c49e; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFFFB, stop:1 #F0FEF3); }");
	}
	if (type_name == "地图备注"){
		groupBox->setStyleSheet("QGroupBox{ color:#008000; border: 1px solid #008000; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFFFB, stop:1 #F0FEF3); }");
	}
	if (type_name == "角色注释" || type_name == "敌人注释" || type_name == "状态注释" || type_name == "技能注释"){
		groupBox->setStyleSheet("QGroupBox{ color:#FF7F27; border: 1px solid #FF7F27; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFAF1, stop:1 #FEFEF0); }");
	}
	if (type_name == "物品/武器/护甲注释" || type_name == "移动路线指令"){
		groupBox->setStyleSheet("QGroupBox{ color:#d4449e; border: 1px solid #d4449e; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FFFAFB, stop:1 #FEF0F3); }");
	}
	if (type_name == "插件指令(旧)"  || type_name == "事件注释(旧)" ){
		groupBox->setStyleSheet("QGroupBox{ color:#989898; border: 1px solid #989898; background-color: qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 #FAFBFA, stop:1 #E5E5E5); }");
	}
}
/*-------------------------------------------------
		控件 - 链接被点击
*/
void P_ScriptHelp_CommandSearchCell::linkClicked_plugin(QString data){
	DrillPluginInformationReader::getInstance()->showPluginDetail(data);
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_CommandSearchCell::setData(C_ScriptHelp_Command* data, QString plugin_name, QString plugin_desc, QString search_text, QString search_type){
	this->clearAllChild();
	if (data == nullptr){ return; }
	if (data->isNull()){ return; }
	if (plugin_name.isEmpty()){ return; }

	// > 所属插件 标签文本
	QString plugin_text = "<p>所属插件：<a href=\"";
	plugin_text.append(plugin_name);
	plugin_text.append("\"><span style=\"text-decoration: underline; color:#0000ff; \">");
	plugin_text.append(plugin_name);
	plugin_text.append("</span></a>");
	plugin_text.append(" ");
	plugin_text.append(plugin_desc);
	plugin_text.append("。< / p>");
	
	// > 指令 - 插件指令
	if ((search_type == "全部类型" || search_type == "插件指令") &&
		data->hasCommandKeyWord_PluginCommand(search_text)){
		QStringList command_list = data->getAllCommand_PluginCommand();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("插件指令", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 事件注释
	if ((search_type == "全部类型" || search_type == "事件注释") && 
		data->hasCommandKeyWord_EventComment(search_text)){
		QStringList command_list = data->getAllCommand_EventComment();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("事件注释", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 地图备注
	if ((search_type == "全部类型" || search_type == "地图备注") && 
		data->hasCommandKeyWord_MapNote(search_text)){
		QStringList command_list = data->getAllCommand_MapNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("地图备注", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 角色注释
	if ((search_type == "全部类型" || search_type == "角色注释") && 
		data->hasCommandKeyWord_ActorNote(search_text)){
		QStringList command_list = data->getAllCommand_ActorNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("角色注释", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 敌人注释
	if ((search_type == "全部类型" || search_type == "敌人注释") && 
		data->hasCommandKeyWord_EnemyNote(search_text)){
		QStringList command_list = data->getAllCommand_EnemyNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("敌人注释", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 状态注释
	if ((search_type == "全部类型" || search_type == "状态注释") &&
		data->hasCommandKeyWord_StateNote(search_text)){
		QStringList command_list = data->getAllCommand_StateNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("状态注释", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 物品/武器/护甲注释
	if ((search_type == "全部类型" || search_type == "物品/武器/护甲注释") &&
		data->hasCommandKeyWord_StateNote(search_text)){
		QStringList command_list = data->getAllCommand_ItemNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("物品/武器/护甲注释", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 技能注释
	if ((search_type == "全部类型" || search_type == "技能注释") &&
		data->hasCommandKeyWord_StateNote(search_text)){
		QStringList command_list = data->getAllCommand_SkillNote();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("技能注释", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 移动路线指令
	if ((search_type == "全部类型" || search_type == "移动路线指令") && 
		data->hasCommandKeyWord_MoveRoute(search_text)){
		QStringList command_list = data->getAllCommand_MoveRoute();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("移动路线指令", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 插件指令(旧)
	if (search_type == "全部类型" && 
		data->hasCommandKeyWord_PluginCommandOld(search_text)){
		QStringList command_list = data->getAllCommand_PluginCommandOld();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("插件指令(旧)", plugin_text, this->getStringWithSign(context_text, search_text));
	}
	// > 指令 - 事件注释(旧)
	if (search_type == "全部类型" && 
		data->hasCommandKeyWord_EventCommentOld(search_text)){
		QStringList command_list = data->getAllCommand_EventCommentOld();
		QString context_text = "<p>"; context_text.append(command_list.join("<br>")); context_text.append("</p>");
		this->addOneChildData("事件注释(旧)", plugin_text, this->getStringWithSign(context_text, search_text));
	}
}
/*-------------------------------------------------
		搜索指令 - 将指定字符串标蓝
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
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_CommandSearchCell::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_CommandSearchCell::putUiToData(){
	//（暂无）
}