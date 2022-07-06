#include "stdafx.h"
#include "s_LinkDirector.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
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
	this->m_dirNameInited = false;
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
		���� - �ļ������Ƴ�ʼ��
*/
void S_LinkDirector::initDirName(){
	if (this->m_dirNameInited == true){ return; }
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return; }
	this->m_dirNameInited = true;

	// > һ���ļ���
	this->m_dirNameTank.clear();
	this->m_docNameTank.clear();
	QFileInfoList childDir_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
	for (int i = 0; i < childDir_list.count(); i++){
		QFileInfo child_dir = childDir_list.at(i);
		QString childDir_name = child_dir.fileName();
		if (childDir_name == "����" || childDir_name == "����"){ continue; }

		// > �����ļ����е��ļ�
		QStringList docName_list;
		QFileInfoList fileInfo_list = QDir(child_dir.filePath()).entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
		for (int j = 0; j < fileInfo_list.count(); j++){
			QFileInfo fileInfo = fileInfo_list.at(j);
			QString file_name = fileInfo.fileName();
			docName_list.append(file_name);
		}

		this->m_dirNameTank.append(childDir_name);
		this->m_docNameTank.append(docName_list);
	}
}
/*-------------------------------------------------
		���� - ��ȡ�ļ�������
*/
QStringList S_LinkDirector::getDirName_All(){
	this->initDirName();
	return m_dirNameTank;
}
/*-------------------------------------------------
		���� - ��ȡ�ļ������ƣ�����docx����
*/
QString S_LinkDirector::getDirName_ByDoc(QString tar_docName){
	this->initDirName();
	for (int i = 0; i < this->m_docNameTank.count(); i++){
		QStringList docName_list = this->m_docNameTank.at(i);
		for (int j = 0; j < docName_list.count(); j++){
			QString cur_docName = docName_list.at(j);
			QString cur_name = cur_docName.replace(QRegExp("[��][^��]*[��]"), "");	//�������š����������ı���
			QString tar_name = tar_docName.replace(QRegExp("[��][^��]*[��]"), "");
			if (cur_name == tar_name){	//��ƥ����˵���ڴ��ļ����£�
				return this->m_dirNameTank.at(i);
			}
		}
	}
	return "";
}
/*-------------------------------------------------
		���� - ��ȡ�ĵ�·���������ĵ����ƣ�
*/
QString S_LinkDirector::getFullPath_ByDoc(QString tar_docName){
	this->initDirName();
	for (int i = 0; i < this->m_docNameTank.count(); i++){
		QStringList docName_list = this->m_docNameTank.at(i);
		for (int j = 0; j < docName_list.count(); j++){
			QString cur_docName = docName_list.at(j);
			QString cur_name = QString(cur_docName).replace(QRegExp("[��][^��]*[��]"), "");	//�������š����������ı���
			QString tar_name = tar_docName.replace(QRegExp("[��][^��]*[��]"), "");
			if (cur_name == tar_name){
				QDir dir(this->getDocDir());
				return dir.absoluteFilePath(this->m_dirNameTank.at(i) + "/" + cur_docName);
			}
		}
	}
	return "";
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
		���� - Ѱ�Ҳ������
*/
QStringList S_LinkDirector::findPluginNameList(QString data){
	QStringList result_list = QStringList();

	QList<C_ScriptAnnotation> annotation_list = S_InformationDataContainer::getInstance()->getAnnotationTank();
	for (int i = 0; i < annotation_list.count(); i++){
		C_ScriptAnnotation annotation = annotation_list.at(i);
		if (data.contains( annotation.getName()+" " )){	//�����ָ��������Ҫ�пո�
			result_list.append(annotation.getName());
		}
	}
	return result_list;
}

/*-------------------------------------------------
		·�� - ��ָ���ĵ�·��
*/
void S_LinkDirector::openLink_Doc(QString text){
	QString path = this->getFullPath_ByDoc(text);
	QFileInfo cur_file(path);
	if (cur_file.exists()){
		QDesktopServices::openUrl(QUrl("file:/" + cur_file.absoluteFilePath()));
		return;
	}

	// > �Ҳ����ļ�
	QMessageBox::warning(nullptr, "��ʾ", "����ĵ���û���ļ���\n" + path + "");
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
		���� - ���ַ����е� "<" �滻Ϊ"\\<"
*/
QString S_LinkDirector::signLtGtTag(QString data){
	return data.replace("<", "&lt;").replace(">", "&gt;");
}
void S_LinkDirector::signLtGtTag(QStringList* data){
	for (int i = 0; i < data->count(); i++){
		data->replace(i, this->signLtGtTag(data->at(i)));
	}
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
	match_list << this->getDirName_All();

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
		���� - ���ַ����е� ������� תΪ"<a>"����
*/
QString S_LinkDirector::signATag_Plugin(QString data){
	QStringList match_list = this->findPluginNameList(data);

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

	return data;
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