#include "stdafx.h"
#include "s_InformationDataContainer.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
#include "Source/PluginModule/scriptReader/s_ScriptAnnotationReader.h"

/*
-----==========================================================-----
		�ࣺ		������� ����.cpp
		�汾��		v1.02
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		����plugin.js�е�ȫ������������ݡ�
					����װ�������ṹ��ע����ն�ȡ���źš�
		
		ʹ�÷�����
				>��ʼ����
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
----------PluginDataManager ����
*/
S_InformationDataContainer* S_InformationDataContainer::cur_manager = NULL;
S_InformationDataContainer* S_InformationDataContainer::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_InformationDataContainer();
	}
	return cur_manager;
}


/*-------------------------------------------------
		���� - ��ȡȫ���������
*/
QList<C_ScriptAnnotation> S_InformationDataContainer::getAnnotationTank() {
	return this->data_AnnotationTank;
}
/*-------------------------------------------------
		���� - ��ȡ��Ӧ�Ĳ������
*/
C_ScriptAnnotation S_InformationDataContainer::getAnnotation(QString pluginName){
	pluginName = pluginName.replace(".js", "");		//��ȥ����׺��

	for (int i = 0; i < this->data_AnnotationTank.count(); i++){
		C_ScriptAnnotation data = this->data_AnnotationTank.at(i);
		if (data.getName() == pluginName){	
			return data;
		}
	}
	return C_ScriptAnnotation();
}


/*-------------------------------------------------
		��ȡ - ��ȡȫ���������ݣ�plugins�ļ��������в����
*/
void S_InformationDataContainer::loadAllAnnotationData(){
	this->data_AnnotationTank.clear();

	// > ��ȡ·����ȫ�����
	QString dir_path = S_RmmvDataContainer::getInstance()->getRmmvProjectData().getRootPath() + "/js/plugins";
	QDir dir(dir_path);
	QFileInfoList fileList;
	if (!dir.exists()) { return; }
	fileList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::Readable | QDir::Writable | QDir::Hidden | QDir::NoDotAndDotDot, QDir::Name);

	for (int i = 0; i < fileList.count(); i++){
		QFileInfo curfile = fileList.at(i);
		if (curfile.suffix() == "js"){
			C_ScriptAnnotation data = S_ScriptAnnotationReader::getInstance()->readPlugin_simple(curfile.absoluteFilePath());
			this->data_AnnotationTank.append(data);
		}
	} 
}

