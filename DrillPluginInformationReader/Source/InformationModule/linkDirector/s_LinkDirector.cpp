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
		数据 - 获取全部文件夹名称
*/
QStringList S_LinkDirector::getDataAllDocDirName(){
	QDir dir(this->getDocDir());
	if (!dir.exists()) { return QStringList(); }

	QStringList result_list = QStringList();
	QFileInfoList fileList;
	fileList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

	for (int i = 0; i < fileList.count(); i++){
		QFileInfo cur_file = fileList.at(i);
		QString name = cur_file.fileName();
		if (name == "其它" || name == "其他"){ continue; }
		result_list.append(name);
	}
	return result_list;
}
/*-------------------------------------------------
		路径 - 打开指定路径
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

}



/*-------------------------------------------------
		链接 - 将字符串中的 文档、路径 转为链接
*/
QString S_LinkDirector::signLink_Docs(QString data){

	// > 获取到匹配（匹配所有docx）
	QRegExp rx("[ \"]([^ ]+\\.docx)");
	QStringList match_list = QStringList();
	int pos = 0;
	while ((pos = rx.indexIn(data, pos)) != -1) {
		match_list << rx.cap(1);
		pos += rx.matchedLength();
	}

	// > 文档路径（固定的）
	match_list << this->getDataAllDocDirName();

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
	//<html><head/><body><p>测试的文本，<a href="测试的文本"><span style=" text-decoration: underline; color:#0000ff;">测试的文本</span></a>。</p></body></html>

	// > 包裹章节
	QString result;
	result.append("<p>");
	result.append(data);
	result.append("</p>");

	return result;
}