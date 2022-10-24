#ifndef P_CAFunctionCheck_H
#define P_CAFunctionCheck_H

#include <QObject>

/*
-----==========================================================-----
		类：		函数校验器.h
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	生成自定义的Excel表格格式。
					（详细见cpp）
-----==========================================================-----
*/
class P_CAFunctionCheck : public QObject
{
	Q_OBJECT

	public:
		P_CAFunctionCheck(QObject *parent = 0);
		~P_CAFunctionCheck();
		
	//-----------------------------------
	//----生成器
	public slots: 
								//生成器 - 生成 函数文本
		QString generateFunctionCheckData();
								//生成器 - 生成 所有插件缩写
		QString generateFunctionCheckData2();
								//生成器 - 生成 重复定义的变量名
		QString generateFunctionCheckData3();

};

#endif // P_CAFunctionCheck_H
