#include "stdafx.h"
#include "S_InformationDataContainer.h"

#include "Source/RmmvUtilsProjectModule/ProjectData/S_RmmvProjectDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/S_ScriptAnnotationReader.h"

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
					S_InformationDataContainer::getInstance()->resetPluginDataFromText( data_context );
					S_InformationDataContainer::getInstance()->getPluginData();
				
-----==========================================================-----
*/
S_InformationDataContainer::S_InformationDataContainer(){
	this->data_AnnotationTank = QList<C_ScriptAnnotation>();
}
S_InformationDataContainer::~S_InformationDataContainer() {
}

/* --------------------------------------------------------------
----------PluginDataManager 单例
*/
S_InformationDataContainer* S_InformationDataContainer::cur_manager = NULL;
S_InformationDataContainer* S_InformationDataContainer::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_InformationDataContainer();
	}
	return cur_manager;
}


/*-------------------------------------------------
		数据 - 获取全部插件数据
*/
QList<C_ScriptAnnotation> S_InformationDataContainer::getAnnotationTank() {
	return this->data_AnnotationTank;
}
/*-------------------------------------------------
		数据 - 获取对应的插件数据
*/
C_ScriptAnnotation S_InformationDataContainer::getAnnotation(QString pluginName){
	pluginName = pluginName.replace(".js", "");		//（去掉后缀）

	for (int i = 0; i < this->data_AnnotationTank.count(); i++){
		C_ScriptAnnotation data = this->data_AnnotationTank.at(i);
		if (data.getName() == pluginName){	
			return data;
		}
	}
	return C_ScriptAnnotation();
}
/*-------------------------------------------------
		数据 - 获取对应的插件数据
*/
C_ScriptHelpDetail* S_InformationDataContainer::getHelpDetail(QString pluginName){
	return this->getAnnotation(pluginName).getScriptHelpDetail();
}

/*-------------------------------------------------
		数据 - 删除插件数据
*/
void S_InformationDataContainer::removeAnnotation(QStringList pluginName_list){
	for (int i = this->data_AnnotationTank.count()-1; i >= 0; i--){
		C_ScriptAnnotation data = this->data_AnnotationTank.at(i);
		if (pluginName_list.contains( data.getName() )){
			this->data_AnnotationTank.removeAt(i);
		}
	}
}


/*-------------------------------------------------
		读取 - 读取全部完整数据（plugins文件夹下所有插件）
*/
void S_InformationDataContainer::loadAllAnnotationData(){
	this->data_AnnotationTank.clear();

	// > 获取路径下全部插件
	QDir dir = S_RmmvProjectDataContainer::getInstance()->getRmmvDir_Plugins();
	if (!dir.exists()) { return; }
	QFileInfoList fileList;
	fileList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::Readable | QDir::Writable | QDir::Hidden | QDir::NoDotAndDotDot, QDir::Name);

	for (int i = 0; i < fileList.count(); i++){
		QFileInfo curfile = fileList.at(i);
		if (curfile.suffix() == "js"){
			C_ScriptAnnotation data = S_ScriptAnnotationReader::getInstance()->readPlugin_simple(curfile.absoluteFilePath());
			this->data_AnnotationTank.append(data);
		}
	} 
}

