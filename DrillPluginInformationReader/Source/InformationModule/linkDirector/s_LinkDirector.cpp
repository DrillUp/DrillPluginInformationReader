#include "stdafx.h"
#include "s_LinkDirector.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"

/*
-----==========================================================-----
		�ࣺ		�����ļ�������.cpp
		����ģ�飺	���ģ��
		���ܣ�		��ȡjs�ļ��ڵ��������� @��ע�� ���ݡ�

		ʹ�÷�����
				>��ʼ����
				
-----==========================================================-----
*/

S_LinkDirector::S_LinkDirector(){
	this->m_docDir = "";
}
S_LinkDirector::~S_LinkDirector() {
}

/* --------------------------------------------------------------
----------PluginFrameManager ����
*/
S_LinkDirector* S_LinkDirector::cur_manager = NULL;
S_LinkDirector* S_LinkDirector::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_LinkDirector();
	}
	return cur_manager;
}


/*-------------------------------------------------
		���� - ��ȡ����·��
*/
QString S_LinkDirector::getProjectDir(){
	return S_RmmvDataContainer::getInstance()->getRmmvProjectData().getRootPath();
}
/*-------------------------------------------------
		���� - ��ȡ�ĵ�·��
*/
QString S_LinkDirector::getDocDir(){

	// > �Զ����ĵ�·��
	if (this->m_docDir != ""){
		return this->m_docDir;
	}

	// > ʾ����·��
	QString root_path = S_RmmvDataContainer::getInstance()->getRmmvProjectData().getRootPath();
	QFileInfo fileinfo(root_path);
	QString p_path = fileinfo.absolutePath();
	QFileInfo doc_info(p_path + "/�����ϸ�ֲ�");
	if (doc_info.exists()){
		return doc_info.absoluteFilePath();
	}

	return "";
}



/*-------------------------------------------------
		���� - ��ȡ�ɵ�����ļ�������
*/
QStringList S_LinkDirector::getAllClickableDirName(){
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return QStringList(); }

	QStringList result_list = QStringList();
	QFileInfoList c_dir_list;
	c_dir_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

	for (int i = 0; i < c_dir_list.count(); i++){
		QFileInfo cur_dir = c_dir_list.at(i);
		QString name = cur_dir.fileName();
		if (name == "����" || name == "����"){ continue; }
		result_list.append(name);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - Ѱ���ĵ�����
*/
QStringList S_LinkDirector::findDocsNameList(QString data){
	//���ú����� C_ScriptHelpDetail�� �е�һģһ������Ϊ�˶Ͽ����߹�ϵ���ú����ֿ�д��

	// > ��ȡ��ƥ�䣨����ǰ���� �ո����� �����ԣ�
	QRegExp rx("[ \"��]([^ \"��]+\\.(docx|xlsx))");
	QStringList match_list = QStringList();
	int pos = 0;
	while ((pos = rx.indexIn(data, pos)) != -1) {
		match_list << rx.cap(1);
		pos += rx.matchedLength();
	}
	return match_list;
}

/*-------------------------------------------------
		·�� - ��ָ���ĵ�·��
*/
void S_LinkDirector::openLink_Doc(QString text){
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return ; }
	
	// > ���ļ���
	QFileInfo dir_info(dir.absoluteFilePath(text));
	if (dir_info.exists()){
		QDesktopServices::openUrl(QUrl("file:/" + dir_info.absoluteFilePath()));
		return;
	}

	// > ���ļ�
	QFileInfoList c_dir_list;
	c_dir_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
	for (int i = 0; i < c_dir_list.count(); i++){
		QFileInfo cur_dir = c_dir_list.at(i);
		QFileInfo cur_file(cur_dir.absoluteFilePath() + "/" + text);
		if (cur_file.exists()){
			QDesktopServices::openUrl(QUrl("file:/" + cur_file.absoluteFilePath()));
			return;
		}
	}

	// > �Ҳ����ļ�
	QMessageBox::warning(nullptr, "��ʾ", "����ĵ���û���ļ���" + text + "");
}
/*-------------------------------------------------
		·�� - ��ָ��ͼƬ·��
*/
void S_LinkDirector::openLink_Src(QString text){
	QDir dir(this->getProjectDir());
	if (!dir.exists()) { return; }

	// > ���ļ���
	QFileInfo dir_info(dir.absolutePath() + "/" + text);
	if (dir_info.exists()){
		QDesktopServices::openUrl(QUrl("file:/" + dir_info.absoluteFilePath()));
		return;
	}

	// > �Ҳ����ļ�
	QMessageBox::warning(nullptr, "��ʾ", "������û����Դ�ļ��У�" + text );
}
/*-------------------------------------------------
		·�� - �򿪲���嵥
*/
void S_LinkDirector::openLink_specific_pluginListing(){
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return; }

	// > ���ļ�
	QFileInfoList c_dir_list;
	c_dir_list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
	for (int i = 0; i < c_dir_list.count(); i++){
		QFileInfo cur_file = c_dir_list.at(i);
		if (cur_file.fileName().contains("����嵥")){
			QDesktopServices::openUrl(QUrl("file:/" + cur_file.absoluteFilePath()));
			return;
		}
	}

	// > �Ҳ����ļ�
	QMessageBox::warning(nullptr, "��ʾ", "������û��\"����嵥.xlsx\"");
}



/*-------------------------------------------------
		���� - ���ַ����е� "\n" �滻Ϊ"<br>"
*/
QString S_LinkDirector::signBrTag(QString data){
	return data.replace("\n","<br>");
}
/*-------------------------------------------------
		���� - ʹ��"<p>"�����ַ���
*/
QString S_LinkDirector::signPTag(QString data){
	QString result;
	result.append("<p>");
	result.append(data);
	result.append("</p>");
	return result;
}
/*-------------------------------------------------
		���� - ���ַ����е� �ĵ���·�� תΪ"<a>"����
*/
QString S_LinkDirector::signATag_Docs(QString data){
	QStringList match_list = this->findDocsNameList(data);

	// > �ĵ�·�����̶��ģ�
	match_list << this->getAllClickableDirName();

	// > ʹ�����Ӱ���
	for (int j = 0; j < match_list.count(); j++){
		QString str = match_list.at(j);
		QString tar_str;
		tar_str.append("<a href=\"");
		tar_str.append(str);
		tar_str.append("\"><span style = \"text-decoration: underline; color:#0000ff;\">");
		tar_str.append(str);
		tar_str.append("</span></a>");
		data = data.replace(str, tar_str);
	}
	//<p>���Ե��ı���<a href="���Ե��ı�"><span style=" text-decoration: underline; color:#0000ff;">���Ե��ı�</span></a>��</p>

	return data;
}
/*-------------------------------------------------
		���� - �� ��Դ·�� ����"<a>"����
*/
QString S_LinkDirector::signATag_Src(QString src_path){

	QString result;
	result.append("<a href=\"");
	result.append(src_path);
	result.append("\"><span style = \"text-decoration: underline; color:#0000ff;\">");
	result.append(src_path);
	result.append("</span></a>");

	return result;
}
/*-------------------------------------------------
		���� - ���ַ����е� "����嵥.xlsx" תΪ"<a>"����
*/
QString S_LinkDirector::signATag_specific_pluginListing(QString data){

	QString tar_str;
	tar_str.append("<a href=\"");
	tar_str.append("����嵥.xlsx");
	tar_str.append("\"><span style = \"text-decoration: underline; color:#0000ff;\">");
	tar_str.append("����嵥.xlsx");
	tar_str.append("</span></a>");
	data = data.replace(QRegExp("����嵥[.]{0,6}\\.xlsx") , tar_str);

	return data;
}