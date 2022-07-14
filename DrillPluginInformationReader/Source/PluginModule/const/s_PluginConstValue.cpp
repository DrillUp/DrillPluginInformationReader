#include "stdafx.h"
#include "s_PluginConstValue.h"

#include "Source/utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��� ����ֵ.cpp
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���г���ֵ������ֱ�ӻ�ȡ��
-----==========================================================-----
*/
S_PluginConstValue::S_PluginConstValue(){

	// > ��������
	this->m_sceneNameList = QStringList() << "��ͼ����" << "ս������" << "�˵�����" << "STG����";

	// > ����ؼ���
	this->m_sceneKeyMatrix = QList<QList<QString>>();
	this->m_sceneKeyMatrix << (QStringList() << "��ͼ����" << "����" << "�¼�" << "���" );
	this->m_sceneKeyMatrix << (QStringList() << "ս������" << "��λ" << "����" << "��ɫ");
	this->m_sceneKeyMatrix << (QStringList() << "�˵�����" << "�ؼ�" );
	this->m_sceneKeyMatrix << (QStringList() << "STG����" << "����" << "�л�" << "�Ի�");

	// > ���ܹؼ���
	this->m_performanceKeyMatrix = QList<QList<QString>>();
	this->m_performanceKeyMatrix << (QStringList() << "��ͼ����" << "20���¼�" << "50���¼�" << "100���¼�" << "200���¼�");
	this->m_performanceKeyMatrix << (QStringList() << "ս������" << "û�е���" << "1������" << "4������" << "8������");
	this->m_performanceKeyMatrix << (QStringList() << "ս������" << "û�н�ɫ" << "1����ɫ" << "4����ɫ" << "8����ɫ");		//��ֻ ���ݽ������ƻ�ȡ �ĺ�����ȡ�����ⲿ�����ݣ�
	this->m_performanceKeyMatrix << (QStringList() << "�˵�����" << "�̶�1" << "�̶�2" << "�̶�3" << "�̶�4");
	this->m_performanceKeyMatrix << (QStringList() << "STG����" << "20���л�" << "50���л�" << "100���л�" << "200���л�");
}
S_PluginConstValue::~S_PluginConstValue(){
}
/*-------------------------------------------------
		����
*/
S_PluginConstValue* S_PluginConstValue::cur_instance = NULL;
S_PluginConstValue* S_PluginConstValue::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new S_PluginConstValue();
	}
	return cur_instance;
}

/*-------------------------------------------------
		��ȡ - ��ͼ����
*/
QString S_PluginConstValue::getSceneName_Map(){
	return "��ͼ����";
}
/*-------------------------------------------------
		��ȡ - ս������
*/
QString S_PluginConstValue::getSceneName_Battle(){
	return "ս������";
}
/*-------------------------------------------------
		��ȡ - �˵�����
*/
QString S_PluginConstValue::getSceneName_Menu(){
	return "�˵�����";
}
/*-------------------------------------------------
		��ȡ - ��������
*/
QStringList S_PluginConstValue::getSceneName_Other(){
	return QStringList() << "STG����";
}

/*-------------------------------------------------
		��ȡ - �������ƣ�ȫ����
*/
QStringList S_PluginConstValue::getSceneName_All(){
	return this->m_sceneNameList;
}
/*-------------------------------------------------
		��ȡ - �������ƣ����ݽ���ؼ��֣�
*/
QString S_PluginConstValue::getSceneName_BySceneKey(QString sceneKey){
	if (sceneKey == ""){ return ""; }
	for (int i = 0; i < this->m_sceneKeyMatrix.count(); i++){
		QStringList text_list = this->m_sceneKeyMatrix.at(i);
		if (text_list.contains(sceneKey)){
			return text_list.first();
		}
	}
	return "";
}
/*-------------------------------------------------
		��ȡ - �������ƣ��������ܹؼ��֣�
*/
QString S_PluginConstValue::getSceneName_ByPerformanceWord(QString performanceWord){
	if (performanceWord == ""){ return ""; }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		if (text_list.contains( performanceWord ) ){
			return text_list.first();
		}
	}
	return "";
}


/*-------------------------------------------------
		��ȡ - ����ؼ��֣�ȫ����
*/
QStringList S_PluginConstValue::getSceneKey_All(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->m_sceneKeyMatrix.count(); i++){
		QStringList data = this->m_sceneKeyMatrix.at(i);
		data.removeFirst();
		result_list.append(data);
	}
	return result_list;
}
/*-------------------------------------------------
		��ȡ - ����ؼ��֣����ݽ������ƣ�
*/
QStringList S_PluginConstValue::getSceneKey_ByName(QString scene_name){
	if (scene_name == ""){ return QStringList(); }
	for (int i = 0; i < this->m_sceneKeyMatrix.count(); i++){
		QStringList text_list = this->m_sceneKeyMatrix.at(i);
		if (text_list.first() == scene_name){
			text_list.removeFirst();
			return text_list;
		}
	}
	return QStringList();
}

/*-------------------------------------------------
		��ȡ - ���ܹؼ��֣�ȫ����
*/
QStringList S_PluginConstValue::getPerformanceWord_All(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList data = this->m_performanceKeyMatrix.at(i);
		data.removeFirst();
		result_list.append(data);
	}
	return result_list;
}
/*-------------------------------------------------
		��ȡ - ���ܹؼ��֣����ݽ������ƣ�
*/
QStringList S_PluginConstValue::getPerformanceWord_ByName(QString scene_name){
	if (scene_name == ""){ return QStringList(); }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		if (text_list.first() == scene_name){
			text_list.removeFirst();
			return text_list;
		}
	}
	return QStringList();
}
/*-------------------------------------------------
		��ȡ - �̶ȣ��������ܹؼ��֣�
*/
int S_PluginConstValue::getLevel_ByPerformanceWord(QString performanceWord){
	if (performanceWord == ""){ return -1; }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		int index = text_list.indexOf(performanceWord);
		if (index != -1){
			return index;
		}
	}
	return -1;
}