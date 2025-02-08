#include "stdafx.h"
#include "s_LinkDirector.h"

#include "Source/RmmvInteractiveModule/InformationData/S_InformationDataContainer.h"
#include "Source/RmmvUtilsProjectModule/ProjectData/S_RmmvProjectDataContainer.h"

/*
-----==========================================================-----
		类：		链接文件引导器.cpp
		所属模块：	插件模块
		功能：		读取js文件内的所有数据 @的注解 内容。

		使用方法：
				>初始化：
				
-----==========================================================-----
*/

S_LinkDirector::S_LinkDirector(){
	this->m_docDir = "";
	this->m_dirNameInited = false;
}
S_LinkDirector::~S_LinkDirector() {
}

/* --------------------------------------------------------------
----------PluginFrameManager 单例
*/
S_LinkDirector* S_LinkDirector::cur_manager = NULL;
S_LinkDirector* S_LinkDirector::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_LinkDirector();
	}
	return cur_manager;
}


/*-------------------------------------------------
		数据 - 获取工程路径
*/
QString S_LinkDirector::getProjectDir(){
	return S_RmmvProjectDataContainer::getInstance()->getData().getRootPath();
}
/*-------------------------------------------------
		数据 - 获取文档路径
*/
QString S_LinkDirector::getDocDir(){

	// > 自定义文档路径
	if (this->m_docDir != ""){
		return this->m_docDir;
	}

	// > 示例的路径
	QString root_path = S_RmmvProjectDataContainer::getInstance()->getData().getRootPath();
	QFileInfo fileinfo(root_path);
	QString p_path = fileinfo.absolutePath();	//（上一级文件夹）
	QFileInfo doc_info(p_path + "/插件详细手册");
	if (doc_info.exists()){
		return doc_info.absoluteFilePath();
	}

	return "";
}



/*-------------------------------------------------
		数据 - 文件夹名称初始化
*/
void S_LinkDirector::initDirName(){
	if (this->m_dirNameInited == true){ return; }
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return; }
	this->m_dirNameInited = true;

	// > 一级文件夹
	this->m_dirNameTank.clear();
	this->m_docNameTank.clear();
	QFileInfoList childDir_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
	for (int i = 0; i < childDir_list.count(); i++){
		QFileInfo child_dir = childDir_list.at(i);
		QString childDir_name = child_dir.fileName();
		if (childDir_name == "其它" || childDir_name == "其他"){ continue; }

		// > 二级文件夹中的文件
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
		数据 - 获取文件夹名称
*/
QStringList S_LinkDirector::getDirName_All(){
	this->initDirName();
	return m_dirNameTank;
}
/*-------------------------------------------------
		数据 - 获取文件夹名称（根据docx名）
*/
QString S_LinkDirector::getDirName_ByDoc(QString tar_docName){
	this->initDirName();
	for (int i = 0; i < this->m_docNameTank.count(); i++){
		QStringList docName_list = this->m_docNameTank.at(i);
		for (int j = 0; j < docName_list.count(); j++){
			QString cur_docName = docName_list.at(j);
			QString cur_name = cur_docName.replace(QRegExp("[『][^『]*[』]"), "");	//忽略括号『』包裹的文本。
			QString tar_name = tar_docName.replace(QRegExp("[『][^『]*[』]"), "");
			if (cur_name == tar_name){	//（匹配则说明在此文件夹下）
				return this->m_dirNameTank.at(i);
			}
		}
	}
	return "";
}
/*-------------------------------------------------
		数据 - 获取文档路径（根据文档名称）
*/
QString S_LinkDirector::getFullPath_ByDoc(QString tar_docName){
	this->initDirName();
	for (int i = 0; i < this->m_docNameTank.count(); i++){
		QStringList docName_list = this->m_docNameTank.at(i);
		for (int j = 0; j < docName_list.count(); j++){
			QString cur_docName = docName_list.at(j);
			QString cur_name = QString(cur_docName).replace(QRegExp("[『][^『]*[』]"), "");	//忽略括号『』包裹的文本。
			QString tar_name = tar_docName.replace(QRegExp("[『][^『]*[』]"), "");
			if (cur_name == tar_name){
				QDir dir(this->getDocDir());
				return dir.absoluteFilePath(this->m_dirNameTank.at(i) + "/" + cur_docName);
			}
		}
	}
	return "";
}
/*-------------------------------------------------
		数据 - 寻找文档名称
*/
QStringList S_LinkDirector::findDocsNameList(QString data){
	//（该函数与 C_ScriptHelpDetail类 中的一模一样，但为了断开二者关系，该函数分开写）

	// > 获取到匹配（名称前面有 空格、引号 都可以）
	QRegExp rx("[ \"“]([^ \"“]+\\.(docx|xlsx))");
	QStringList match_list = QStringList();
	int pos = 0;
	while ((pos = rx.indexIn(data, pos)) != -1) {
		match_list << rx.cap(1);
		pos += rx.matchedLength();
	}
	return match_list;
}
/*-------------------------------------------------
		数据 - 寻找插件名称
*/
QStringList S_LinkDirector::findPluginNameList(QString data){
	QStringList result_list = QStringList();

	QList<C_ScriptAnnotation> annotation_list = S_InformationDataContainer::getInstance()->getAnnotationTank();
	for (int i = 0; i < annotation_list.count(); i++){
		C_ScriptAnnotation annotation = annotation_list.at(i);
		if (data.contains( annotation.getName()+" " )){	//（插件指令后面必须要有空格）
			result_list.append(annotation.getName());
		}
	}
	return result_list;
}

/*-------------------------------------------------
		路径 - 打开指定文档路径
*/
void S_LinkDirector::openLink_Doc(QString text){
	QString path = this->getFullPath_ByDoc(text);
	QFileInfo cur_file(path);
	if (cur_file.exists()){
		QDesktopServices::openUrl(QUrl("file:/" + cur_file.absoluteFilePath()));
		return;
	}

	// > 找不到文件
	QMessageBox::warning(nullptr, "提示", "插件文档中没有文件：\n" + path + "");
}
/*-------------------------------------------------
		路径 - 打开指定图片路径
*/
void S_LinkDirector::openLink_Src(QString text){
	QDir dir(this->getProjectDir());
	if (!dir.exists()) { return; }

	// > 打开文件夹
	QFileInfo dir_info(dir.absolutePath() + "/" + text);
	if (dir_info.exists()){
		QDesktopServices::openUrl(QUrl("file:/" + dir_info.absoluteFilePath()));
		return;
	}

	// > 找不到文件
	QMessageBox::warning(nullptr, "提示", "工程中没有资源文件夹：" + text );
}
/*-------------------------------------------------
		路径 - 打开插件清单
*/
void S_LinkDirector::openLink_specific_pluginListing(){
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return; }

	// > 打开文件
	QFileInfoList c_dir_list;
	c_dir_list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
	for (int i = 0; i < c_dir_list.count(); i++){
		QFileInfo cur_file = c_dir_list.at(i);
		if (cur_file.fileName().contains("插件清单")){
			QDesktopServices::openUrl(QUrl("file:/" + cur_file.absoluteFilePath()));
			return;
		}
	}

	// > 找不到文件
	QMessageBox::warning(nullptr, "提示", "工程中没有\"插件清单.xlsx\"");
}



/*-------------------------------------------------
		链接 - 将字符串中的 "<" 替换为"\\<"
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
		链接 - 将字符串中的 "\n" 替换为"<br>"
*/
QString S_LinkDirector::signBrTag(QString data){
	return data.replace("\n","<br>");
}
/*-------------------------------------------------
		链接 - 使用"<p>"包裹字符串
*/
QString S_LinkDirector::signPTag(QString data){
	QString result;
	result.append("<p>");
	result.append(data);
	result.append("</p>");
	return result;
}
/*-------------------------------------------------
		链接 - 将字符串中的 文档、路径 转为"<a>"链接
*/
QString S_LinkDirector::signATag_Docs(QString data){
	QStringList match_list = this->findDocsNameList(data);

	// > 文档路径（固定的）
	match_list << this->getDirName_All();

	// > 使用链接包裹
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
	//<p>测试的文本，<a href="测试的文本"><span style=" text-decoration: underline; color:#0000ff;">测试的文本</span></a>。</p>

	return data;
}
/*-------------------------------------------------
		链接 - 将 资源路径 包裹"<a>"链接
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
		链接 - 将字符串中的 插件名称 转为"<a>"链接
*/
QString S_LinkDirector::signATag_Plugin(QString data){
	QStringList match_list = this->findPluginNameList(data);

	// > 使用链接包裹
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
		链接 - 将字符串中的 "插件清单.xlsx" 转为"<a>"链接
*/
QString S_LinkDirector::signATag_specific_pluginListing(QString data){

	QString tar_str;
	tar_str.append("<a href=\"");
	tar_str.append("插件清单.xlsx");
	tar_str.append("\"><span style = \"text-decoration: underline; color:#0000ff;\">");
	tar_str.append("插件清单.xlsx");
	tar_str.append("</span></a>");
	data = data.replace(QRegExp("插件清单[.]{0,6}\\.xlsx") , tar_str);

	return data;
}