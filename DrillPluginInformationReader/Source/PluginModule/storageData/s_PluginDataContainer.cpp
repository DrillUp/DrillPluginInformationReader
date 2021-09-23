#include "stdafx.h"
#include "s_PluginDataContainer.h"


/*
-----==========================================================-----
		类：		插件数据 容器.cpp
		版本：		v1.02
		作者：		drill_up
		所属模块：	插件模块
		功能：		管理plugin.js中的全部插件配置数据。
					【封装的容器结构，注意接收读取的信号】
		
		使用方法：
				>初始化：
					S_PluginDataContainer::getInstance()->resetPluginDataFromText( data_context );
					S_PluginDataContainer::getInstance()->getPluginData();
				
-----==========================================================-----
*/
S_PluginDataContainer::S_PluginDataContainer(){
	this->data_PluginDataTank = QList<C_PluginData*>();
}
S_PluginDataContainer::~S_PluginDataContainer() {
}

/* --------------------------------------------------------------
----------PluginDataManager 单例
*/
S_PluginDataContainer* S_PluginDataContainer::cur_manager = NULL;
S_PluginDataContainer* S_PluginDataContainer::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_PluginDataContainer();
	}
	return cur_manager;
}


/*-------------------------------------------------
		数据 - 获取全部插件数据
*/
QList<C_PluginData*> S_PluginDataContainer::getPluginDataTank() {
	return this->data_PluginDataTank;
}
/*-------------------------------------------------
		数据 - 获取对应的插件数据
*/
C_PluginData* S_PluginDataContainer::getPluginData(QString pluginName){
	pluginName = pluginName.replace(".js", "");		//（去掉后缀）

	for (int i = 0; i < this->data_PluginDataTank.count(); i++){
		C_PluginData* data = this->data_PluginDataTank.at(i);
		if (data->name == pluginName){	
			return data;
		}
	}
	return nullptr;
}
/*-------------------------------------------------
		操作 - 添加
*/
void S_PluginDataContainer::op_add(C_PluginData* data){
	if (this->data_PluginDataTank.contains(data) == true){ return; }
	this->data_PluginDataTank.append(data);
}
/*-------------------------------------------------
		操作 - 替换
*/
void S_PluginDataContainer::op_modify(C_PluginData* data){
	int index = this->data_PluginDataTank.indexOf(data);	//（数据类根据 data->name 来进行搜寻）
	if (index == -1){ return; }
	this->data_PluginDataTank.replace(index, data);
}
/*-------------------------------------------------
		操作 - 去除
*/
void S_PluginDataContainer::op_remove(C_PluginData* data){
	this->data_PluginDataTank.removeOne(data);
}



/*-------------------------------------------------
		读取 - 读取数据（流程）
*/
void S_PluginDataContainer::loadPluginData(QString data_context){
	QList<C_PluginData*> data_list = this->readPluginData(data_context);
	this->data_PluginDataTank = data_list;
	emit pluginDataReloaded();
}
/*-------------------------------------------------
		读取 - 读取数据（流程，不发信号）
*/
void S_PluginDataContainer::loadPluginDataNoSignal(QString data_context){
	QList<C_PluginData*> data_list = this->readPluginData(data_context);
	this->data_PluginDataTank = data_list;
}
/*-------------------------------------------------
		读取 - 读取数据（私有方法）
*/
QList<C_PluginData*> S_PluginDataContainer::readPluginData(QString data_context){
	QList<C_PluginData*> data_list = QList<C_PluginData*>();

	// > 截取数据文本
	int start = data_context.indexOf("[");
	int end = data_context.lastIndexOf("]");
	data_context = data_context.mid(start, end - start + 1);

	// > json转换
	QJsonDocument jsonDocument = QJsonDocument::fromJson(data_context.toUtf8());
	if (jsonDocument.isNull()){
		QMessageBox::warning(nullptr, "错误", "读取文件失败。", QMessageBox::Yes);
		return QList<C_PluginData*>();
	}

	// > 读取赋值
	QJsonArray arr_all = jsonDocument.array();
	for (int i = 0; i < arr_all.count(); i++) {
		QJsonObject obj_plugin = arr_all.at(i).toObject();
		C_PluginData* c_p = new C_PluginData();
		c_p->name = obj_plugin.value("name").toString();
		c_p->status = obj_plugin.value("status").toBool();
		c_p->description = obj_plugin.value("description").toString();
		c_p->parameters = obj_plugin.value("parameters").toObject();
		data_list.push_back(c_p);

		//qDebug() << c_p->parameters;
	}
	return data_list;
}


/*-------------------------------------------------
		写入 - 写入数据
*/
QString S_PluginDataContainer::writePluginData(){
	QString result = "";
	result = result + "// Generated by RPG Maker With Drill Editor.\n";
	result = result + "// Do not edit this file directly.\n";
	result = result + "var $plugins =\n";
	result = result + "[\n";

	for (int i = 0; i < this->data_PluginDataTank.count(); i++){
		C_PluginData* c_p = this->data_PluginDataTank.at(i);
		result = result + QJsonDocument(c_p->getJsonObject()).toJson(QJsonDocument::Compact);
		if (i < this->data_PluginDataTank.count() - 1){
			result = result + ",";
		}
		result = result + "\n";
	}

	result = result + "];\n";
	return result;
}
