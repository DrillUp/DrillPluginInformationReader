#pragma once

#include <QObject>
#include <QFileInfo>

/*
-----==========================================================-----
		类：		回收站操作器.h
		版本：		v1.00
		作者：		drill_up
		所属模块：	工具模块
		功能：		读取 文本文件的矩阵内容，提供便捷操作。
					（详细见cpp）
-----==========================================================-----
*/
class P_RecycleBinOperater{

	public:
		P_RecycleBinOperater();
		~P_RecycleBinOperater();
		
	//-----------------------------------
	//----操作
	public:
										//操作 - 丢入回收站
										//		【说明】：如果操作失败则返回false。
		static bool moveToRecycleBin(QString file_path);
		
};

