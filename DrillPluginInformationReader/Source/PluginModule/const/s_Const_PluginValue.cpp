#include "stdafx.h"
#include "s_Const_PluginValue.h"

/*
-----==========================================================-----
		�ࣺ		��� ����ֵ.cpp
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���г���ֵ������ֱ�ӻ�ȡ��

		�̳��ࣺ	s_Const_Performance ���ܳ���
-----==========================================================-----
*/
S_Const_PluginValue::S_Const_PluginValue(){

	// > ��������
	this->m_sceneNameList = QStringList() << "��ͼ����" << "ս������" << "�˵�����" << "STG����";

	// > ����ؼ���
	this->m_sceneKeyMatrix = QList<QList<QString>>();
	this->m_sceneKeyMatrix << (QStringList() << "��ͼ����" << "����" << "�¼�" << "���" );
	this->m_sceneKeyMatrix << (QStringList() << "ս������" << "��λ" << "����" << "��ɫ");
	this->m_sceneKeyMatrix << (QStringList() << "�˵�����" << "�ؼ�" );
	this->m_sceneKeyMatrix << (QStringList() << "STG����" << "����" << "�л�" << "�Ի�");

}
S_Const_PluginValue::~S_Const_PluginValue(){
}
/*-------------------------------------------------
		����
*/
S_Const_PluginValue* S_Const_PluginValue::cur_instance = NULL;
S_Const_PluginValue* S_Const_PluginValue::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new S_Const_PluginValue();
	}
	return cur_instance;
}

/*-------------------------------------------------
		��ȡ - ��ͼ����
*/
QString S_Const_PluginValue::getSceneName_Map(){
	return "��ͼ����";
}
/*-------------------------------------------------
		��ȡ - ս������
*/
QString S_Const_PluginValue::getSceneName_Battle(){
	return "ս������";
}
/*-------------------------------------------------
		��ȡ - �˵�����
*/
QString S_Const_PluginValue::getSceneName_Menu(){
	return "�˵�����";
}
/*-------------------------------------------------
		��ȡ - ��������
*/
QStringList S_Const_PluginValue::getSceneName_Other(){
	return QStringList() << "STG����";
}

/*-------------------------------------------------
		��ȡ - �������ƣ�ȫ����
*/
QStringList S_Const_PluginValue::getSceneName_All(){
	return this->m_sceneNameList;
}
/*-------------------------------------------------
		��ȡ - �������ƣ����ݽ���ؼ��֣�
*/
QString S_Const_PluginValue::getSceneName_BySceneKey(QString sceneKey){
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
		��ȡ - ����ؼ��֣�ȫ����
*/
QStringList S_Const_PluginValue::getSceneKey_All(){
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
QStringList S_Const_PluginValue::getSceneKey_ByName(QString scene_name){
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
