#pragma once
#include <QList>

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		类：		帮助数据-测试结果 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_PerformanceTest{

	public:
		C_ScriptHelp_PerformanceTest();
		~C_ScriptHelp_PerformanceTest();
		
	//-----------------------------------
	//----数据
	public:
		QString text_method;				//测试方法
		QStringList condition_list;			//条件列表
		QStringList cost_list;				//消耗列表
	public:
								//数据 - 获取消耗列表
		QList<double> getCostList();
								//数据 - 获取最大消耗
		double getMaxCost();
		
	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 测试结果 字符串
		void readTest(QString test_context);
};
/*
-----==========================================================-----
		类：		帮助数据-插件性能 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_Performance{

	public:
		C_ScriptHelp_Performance();
		~C_ScriptHelp_Performance();

	//-----------------------------------
	//----数据
	public:
		QString working_type;								//工作类型
		QString time_complexity;							//时间复杂度
		QList<C_ScriptHelp_PerformanceTest> test_list;		//测试结果列表
		QStringList context_note;							//内容列表
	public:
								//数据 - 获取最大消耗
		double getMaxCost();
								//数据 - 是否高消耗
		bool isHighCost();
								//数据 - 是否中消耗
		bool isMiddleCost();
								//数据 - 是否低消耗
		bool isLowCost();

	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 插件性能 字符串
		void readPerformance(QString performance_context);

};
