#include "stdafx.h"
#include "s_LinkDirector.h"

#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"

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
	return S_RmmvDataContainer::getInstance()->getRmmvProjectData().getRootPath();
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
	QString root_path = S_RmmvDataContainer::getInstance()->getRmmvProjectData().getRootPath();
	QFileInfo fileinfo(root_path);
	QString p_path = fileinfo.absolutePath();
	QFileInfo doc_info(p_path + "/插件详细手册");
	if (doc_info.exists()){
		return doc_info.absoluteFilePath();
	}

	return "";
}



/*-------------------------------------------------
		数据 - 获取可点击的文件夹名称
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
		if (name == "其它" || name == "其他"){ continue; }
		result_list.append(name);
	}
	return result_list;
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
		路径 - 打开指定文档路径
*/
void S_LinkDirector::openLink_Doc(QString text){
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return ; }
	
	// > 打开文件夹
	QFileInfo dir_info(dir.absoluteFilePath(text));
	if (dir_info.exists()){
		QDesktopServices::openUrl(QUrl("file:/" + dir_info.absoluteFilePath()));
		return;
	}

	// > 打开文件
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

	// > 找不到文件
	QMessageBox::warning(nullptr, "提示", "插件文档中没有文件：" + text + "");
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
	match_list << this->getAllClickableDirName();

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