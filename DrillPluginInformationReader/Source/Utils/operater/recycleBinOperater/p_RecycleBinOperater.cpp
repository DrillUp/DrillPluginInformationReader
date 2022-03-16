#include "stdafx.h"
#include "p_RecycleBinOperater.h"

/*
-----==========================================================-----
		类：		回收站操作器.cpp
		版本：		v1.00
		作者：		drill_up
		所属模块：	工具模块
		功能：		读取 文本文件的矩阵内容，提供便捷操作。

		使用方法：
				> 初始化
					P_MatrixReader reader = new P_MatrixReader();
					reader.initSetSkipRow(0);							//跳过行
					reader.initSetSkipComment(QStringList()<<"#");		//去掉注释行
					reader.initSetSeparator(QRegExp("[, \t]+"));		//定义分隔符（默认空格和\t）
					this->m_matrix = reader.readMatrixByFile(QFileInfo(path));			//执行初始化
					if (this->m_matrix == nullptr){ return; }

-----==========================================================-----
*/
P_RecycleBinOperater::P_RecycleBinOperater(){
}
P_RecycleBinOperater::~P_RecycleBinOperater() {
}


/*-------------------------------------------------
		操作 - 丢入回收站
*/
bool P_RecycleBinOperater::moveToRecycleBin(QString file_path){
	QFileInfo fileinfo(file_path);
	if (fileinfo.exists() == false){
		return false;
	}
	WCHAR from[MAX_PATH];
	memset(from, 0, sizeof(from));
	int l = fileinfo.absoluteFilePath().toWCharArray(from);
	if (l < 0){ return false; }
	if (l >= MAX_PATH){ return false; }
	from[l] = '\0';
	SHFILEOPSTRUCT fileop;
	memset(&fileop, 0, sizeof(fileop));
	fileop.wFunc = FO_DELETE;
	fileop.pFrom = from;
	fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
	int rv = SHFileOperation(&fileop);
	if (0 != rv){
		qDebug() << rv << QString::number(rv).toInt(0, 8);
		return false;
	}
	return true;
}
