#include "stdafx.h"
#include "s_Const_Performance.h"

#include "Source/utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		������� ����ֵ.cpp
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		���г���ֵ������ֱ�ӻ�ȡ��
-----==========================================================-----
*/
S_Const_Performance::S_Const_Performance() : S_Const_PluginValue(){

	// > ���ܹؼ���
	this->m_performanceKeyMatrix = QList<QList<QString>>();
	this->m_performanceKeyMatrix << (QStringList() << "��ͼ����" << "20���¼�" << "50���¼�" << "100���¼�" << "200���¼�");
	this->m_performanceKeyMatrix << (QStringList() << "ս������" << "û�е���" << "1������" << "4������" << "8������");
	this->m_performanceKeyMatrix << (QStringList() << "ս������" << "û�н�ɫ" << "1����ɫ" << "4����ɫ" << "8����ɫ");		//��ֻ ���ݽ������ƻ�ȡ �ĺ�����ȡ�����ⲿ�����ݣ�
	this->m_performanceKeyMatrix << (QStringList() << "�˵�����" << "�̶�1" << "�̶�2" << "�̶�3" << "�̶�4");
	this->m_performanceKeyMatrix << (QStringList() << "STG����" << "20���л�" << "50���л�" << "100���л�" << "200���л�");
}
S_Const_Performance::~S_Const_Performance(){
}
/*-------------------------------------------------
		����
*/
S_Const_Performance* S_Const_Performance::cur_instance = NULL;
S_Const_Performance* S_Const_Performance::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new S_Const_Performance();
	}
	return cur_instance;
}

/*-------------------------------------------------
		��ȡ - �������ƣ��������ܹؼ��֣�
*/
QString S_Const_Performance::getSceneName_ByPerformanceWord(QString performanceWord){
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
		��ȡ - ���ܹؼ��֣�ȫ����
*/
QStringList S_Const_Performance::getPerformanceWord_All(){
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
QStringList S_Const_Performance::getPerformanceWord_ByName(QString scene_name){
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
int S_Const_Performance::getLevel_ByPerformanceWord(QString performanceWord){
	if (performanceWord == ""){ return -1; }
	for (int i = 0; i < this->m_performanceKeyMatrix.count(); i++){
		QStringList text_list = this->m_performanceKeyMatrix.at(i);
		int index = text_list.indexOf(performanceWord);	//������ 1��4 ��0�϶��������� ��
		if (index != -1){
			return index;
		}
	}
	return -1;
}