#pragma once
#include <QJsonObject>

#include "S_Const_EffectScope.h"

/*
-----==========================================================-----
		类：		帮助数据-插件性能 常量值.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		常量值在这单例中可以直接获取。
					（详细见.cpp）
-----==========================================================-----
*/
class S_Const_Performance : public S_Const_EffectScope{

	public:
		S_Const_Performance();
		~S_Const_Performance();
		static S_Const_Performance* cur_instance;		//单例
		static S_Const_Performance* getInstance();		//单例，获取自己
		
	//-----------------------------------
	//----性能常量
	protected:
		QList<QList<QString>> m_performanceKeyMatrix;	//性能关键字
	public:
									//获取 - 界面名称（根据性能关键字）
		QString getSceneName_ByPerformanceWord(QString performanceWord);

									//获取 - 性能关键字（全部）
		QStringList getPerformanceWord_All();
									//获取 - 性能关键字（根据界面名称）
		QStringList getPerformanceWord_ByName(QString scene_name);
									//获取 - 程度（根据性能关键字）
									//		【说明】：返回值为 1至4 或 -1。
		int getLevel_ByPerformanceWord(QString performanceWord);
};
