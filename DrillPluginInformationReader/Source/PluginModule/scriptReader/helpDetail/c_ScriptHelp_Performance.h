#pragma once
#include <QList>

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"


/*
-----==========================================================-----
		类：		帮助数据-测试结果 数据类.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_PerformanceTestDetail{

	public:
		C_ScriptHelp_PerformanceTestDetail();
		~C_ScriptHelp_PerformanceTestDetail();
		
	//-----------------------------------
	//----数据
	protected:
		double cost;					//消耗值
		QString description;			//描述内容
		QString condition_scene;		//条件 - 界面
		int condition_level;			//条件 - 程度（0:不分程度的界面整体测试；1-4:1为最弱程度,4为最强程度）
	public:
								//数据 - 获取消耗值
		double getCostValue();
								//数据 - 获取消耗显示文本
		QString getCostString();
								//数据 - 获取描述内容
		QString getDescription();
								//数据 - 获取条件 - 界面
		QString getCondition_scene();
								//数据 - 获取条件 - 程度
		int getCondition_level();
								//数据 - 空判断
		bool isNull();
		
	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 测试结果 字符串
		void readTestDetail(QString one_row);
};

/*
-----==========================================================-----
		类：		帮助数据-测试项 数据类.h
		作者：		drill_up
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
		QString text_method;									//测试方法（可为空）
		QList<C_ScriptHelp_PerformanceTestDetail> detail_list;	//测试结果
	public:
								//数据 - 获取消耗列表
		QList<double> getCostList();
								//数据 - 获取最大消耗
		double getMaxCost();
								//数据 - 获取最大消耗（根据条件）
								//		【说明】：如果没有值，则返回-1。
		double getMaxCost_ByLevel(QString scene_name, int level);
								//数据 - 获取最小消耗（根据条件）
								//		【说明】：如果没有值，则返回-1。
		double getMinCost_ByLevel(QString scene_name, int level);
		
	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 测试结果 字符串
		void readTest(QString test_context);
};
/*
-----==========================================================-----
		类：		帮助数据-插件性能 数据类.h
		作者：		drill_up
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
		double max_cost;									//最大消耗（暂存变量）
	public:
								//数据 - 空判断
		bool isNull();

								//数据 - 获取最大消耗
		double getMaxCost();
								//数据 - 获取最大消耗（根据条件）
								//		【说明】：如果没有值，则返回-1。
		double getMaxCost_ByLevel(QString scene_name, int level);
								//数据 - 获取最小消耗（根据条件）
								//		【说明】：如果没有值，则返回-1。
		double getMinCost_ByLevel(QString scene_name, int level);

								//数据 - 是否高消耗
		bool isHighCost();
								//数据 - 是否中消耗
		bool isMiddleCost();
								//数据 - 是否低消耗
		bool isLowCost();
	private:
								//数据 - 获取最大消耗（私有）
		double getMaxCost_Private();

	//-----------------------------------
	//----读取器
	public:
								//读取器 - 读取 插件性能 字符串
		void readPerformance(QString performance_context);

};
