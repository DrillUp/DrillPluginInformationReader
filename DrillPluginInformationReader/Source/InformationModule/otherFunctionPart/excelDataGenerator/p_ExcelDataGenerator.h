#ifndef P_ExcelDataGenerator_H
#define P_ExcelDataGenerator_H

#include <QObject>

/*
-----==========================================================-----
		类：		Excel表格生成器.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	生成自定义的Excel表格格式。
					（详细见cpp）
-----==========================================================-----
*/
class P_ExcelDataGenerator : public QObject
{
	Q_OBJECT

	public:
		P_ExcelDataGenerator(QObject *parent = 0);
		~P_ExcelDataGenerator();
		
	//-----------------------------------
	//----生成器
	public slots: 
								//生成器 - 生成插件清单
		void generatePluginDataList(QString save_path);

};

#endif // P_ExcelDataGenerator_H
