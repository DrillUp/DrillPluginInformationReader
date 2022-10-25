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
								//生成器 - 生成 所有插件缩写
		QString generate_AllAbbreviation();
								//生成器 - 生成 所有插件继承的方法名
		QString generate_AllInheritFunctionName();
								//生成器 - 校验错误的函数继承名
								//		【说明】：继承的函数名与取代的函数名不一致，会被列出。
		QString generate_WrongInheritFunctionName();
								//生成器 - 校验重复定义的函数名
								//		【说明】：只要"var _drill"参数重复出现，那么就列出。
		QString generate_RepeatDefinition();

};

#endif // P_CAFunctionCheck_H
