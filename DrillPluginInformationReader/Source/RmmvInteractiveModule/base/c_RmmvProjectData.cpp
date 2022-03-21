#include "stdafx.h"
#include "C_RmmvProjectData.h"

/*
-----==========================================================-----
		�ࣺ		rmmv�������� ʵ����.cpp
		�汾��		v1.02
		����ģ�飺	����ģ��
		���ܣ�		���̻�����Ϣ���ݡ�

		˵����		��Ҳ����ֱ���þ�̬������ȡ���������ݣ�
					C_RmmvProjectData data = C_RmmvProjectData::callRmmvSelectDialog()
-----==========================================================-----
*/
C_RmmvProjectData::C_RmmvProjectData(){
	this->name = "";			//������
	this->version = "";			//���̰汾
	this->path = "";			//���̸�·��
}
C_RmmvProjectData::~C_RmmvProjectData(){
}


/*-------------------------------------------------
		���� - ���������ļ�
*/
void C_RmmvProjectData::initFromFile(QString full_filePath){
	QString dir_path = QFileInfo(full_filePath).absolutePath();		//��ȡ��Ŀ¼

	// > ��ȡ�����ļ�
	QFile project_file(full_filePath);
	if (!project_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "����", "δ�ҵ�Game.rpgproject�ļ���", QMessageBox::Yes);
		return;
	}
	QString version = project_file.readAll();
	project_file.close();

	// > ��ȡindex�ļ�
	QFile index_file(dir_path + "/index.html");
	if (!index_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "����", "δ�ҵ�index.html�ļ���", QMessageBox::Yes);
		return;
	}
	QString index_context = index_file.readAll();
	index_file.close();

	// > ����������
	int i_a = index_context.indexOf("<title>") + 7;
	int i_b = index_context.indexOf("</title>", i_a);
	this->name = index_context.mid(i_a, i_b - i_a);
	this->version = version;
	this->path = dir_path;
}
/*-------------------------------------------------
		���� - ��ȡ��������
*/
QString C_RmmvProjectData::getName(){
	return this->name;
}
/*-------------------------------------------------
		���� - ��ȡ���̰汾
*/
QString C_RmmvProjectData::getVersion(){
	return this->version;
}
/*-------------------------------------------------
		���� - ��ȡ���̸�·��
*/
QString C_RmmvProjectData::getRootPath(){
	return this->path;
}
/*-------------------------------------------------
		���� - �жϹ����Ƿ����
*/
bool C_RmmvProjectData::isProjectExist(){
	if (QFileInfo(this->path).exists() == false){ return false; }
	if (QFileInfo(this->path + "/index.html").exists() == false){ return false; }
	return true;
}


/*-------------------------------------------------
		��ݲ��� - �����ļ�ѡ�� ��ȡ��������
*/
C_RmmvProjectData C_RmmvProjectData::callRmmvSelectDialog(){
	QFileDialog fd;
	fd.setWindowTitle("��rmmv����");
	fd.setAcceptMode(QFileDialog::AcceptOpen);		//�Ի������ͣ���/���棩
	fd.setDirectory(".");							//Ĭ��Ŀ¼
	fd.setNameFilters(QStringList()					//�ļ���ʽ
		<< "rmmv�����ļ�(*.rpgproject)"
		);
	fd.setViewMode(QFileDialog::Detail);

	if (fd.exec() == QDialog::Accepted) {
		if (fd.selectedFiles().empty()) {
			//��û��ѡ���ļ�����������
			return C_RmmvProjectData();
		}
		QString file_path = fd.selectedFiles().at(0);

		C_RmmvProjectData data = C_RmmvProjectData();
		data.initFromFile(file_path);
		return data;
	
	}else {
		//������رջ���ȡ�������������
		return C_RmmvProjectData();
	}
}


/*-------------------------------------------------
		���ж�
*/
bool C_RmmvProjectData::isNull(){
	return this->name == "" || this->path == "";
}
/*-------------------------------------------------
		���������
*/
const bool C_RmmvProjectData::operator== (const C_RmmvProjectData& a)const {
	return this->path == a.path;
}
/*-------------------------------------------------
		ʵ���� -> QJsonObject
*/
QJsonObject C_RmmvProjectData::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("version", this->version);
	obj.insert("path", this->path);
	return obj;
}
/*-------------------------------------------------
		QJsonObject -> ʵ����
*/
void C_RmmvProjectData::setJsonObject(QJsonObject obj){
	this->name = obj.value("name").toString();
	this->version = obj.value("version").toString();
	this->path = obj.value("path").toString();
}
