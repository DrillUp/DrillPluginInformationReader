#include "stdafx.h"
#include "c_ScriptHelp_Performance.h"


/*
-----==========================================================-----
		类：		帮助数据-测试结果 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_PerformanceTest::C_ScriptHelp_PerformanceTest(){
	this->text_method = QString();				//测试方法
	this->condition_list = QStringList();		//条件列表
	this->cost_list = QStringList();			//消耗列表
}
C_ScriptHelp_PerformanceTest::~C_ScriptHelp_PerformanceTest(){
}

/*-------------------------------------------------
		数据 - 获取消耗列表
*/
QList<double> C_ScriptHelp_PerformanceTest::getCostList(){
	QList<double> result_list = QList<double>();
	for (int i = 0; i < this->cost_list.count(); i++){
		QString cost = this->cost_list.at(i);
		cost = cost.replace(QRegExp("[^0-9e\\.]+"), "");		//（只留数字）
		result_list.append(cost.toDouble());
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取最大消耗
*/
double C_ScriptHelp_PerformanceTest::getMaxCost(){
	QList<double> data_list = this->getCostList();
	if (data_list.count() == 0){ return 0; }
	double value = data_list.front();
	for (int i = 1; i < data_list.count(); i++){
		double data = data_list.at(i);
		if (value < data){
			value = data;
		}
	}
	return value;
}
/*-------------------------------------------------
		读取器 - 读取 测试结果 字符串
*/
void C_ScriptHelp_PerformanceTest::readTest(QString test_context){
	test_context = test_context.replace(QRegExp("^测试方法[:： ]+"),"");
	QStringList data_list = test_context.split(QRegExp("测试结果[:： ]+"));
	if (data_list.count() < 2){ return; }
	
	// > 测试方法
	this->text_method = data_list.at(0);
	
	// > 条件列表
	QStringList condition_str_list = data_list.at(1).split(QRegExp("[\n\r\t][ ]+"));
	for (int i = 0; i < condition_str_list.count(); i++){
		QString condition_str = condition_str_list.at(i);
		if (condition_str.isEmpty()){ continue; }

		condition_str = condition_str.replace("】", "");
		QStringList str_list = condition_str.split("【");
		if (str_list.count() < 2){ continue; }
		this->condition_list.append(str_list.at(0));	//（分离结果和说明文字）
		this->cost_list.append(str_list.at(1));
	}
}


/*
-----==========================================================-----
		类：		帮助数据-插件性能 数据类.cpp
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Performance::C_ScriptHelp_Performance(){
	this->working_type = QString();									//工作类型
	this->time_complexity = QString();								//时间复杂度
	this->test_list = QList<C_ScriptHelp_PerformanceTest>();		//测试结果列表
	this->context_note = QStringList();								//内容列表
}
C_ScriptHelp_Performance::~C_ScriptHelp_Performance(){
}
/*-------------------------------------------------
		数据 - 获取测试结果列表
*/
QList<C_ScriptHelp_PerformanceTest> C_ScriptHelp_Performance::getTestList(){
	return this->test_list;
}
/*-------------------------------------------------
		数据 - 获取最大消耗
*/
double C_ScriptHelp_Performance::getMaxCost(){
	if (this->test_list.count() == 0){ return 0; }

	C_ScriptHelp_PerformanceTest first_test = this->test_list.first();
	double value = first_test.getMaxCost();
	for (int i = 1; i < this->test_list.count(); i++){
		C_ScriptHelp_PerformanceTest test = this->test_list.at(i);
		double data = test.getMaxCost();
		if (value < data){
			value = data;
		}
	}
	return value;
}
/*-------------------------------------------------
		数据 - 是否高消耗
*/
bool C_ScriptHelp_Performance::isHighCost(){
	return this->getMaxCost() >= 120;
}
/*-------------------------------------------------
		数据 - 是否中消耗
*/
bool C_ScriptHelp_Performance::isMiddleCost(){
	return this->getMaxCost() >= 80;
}
/*-------------------------------------------------
		数据 - 是否低消耗
*/
bool C_ScriptHelp_Performance::isLowCost(){
	return this->getMaxCost() >= 40;
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_Performance::isNull(){
	return this->test_list.count() == 0;
}

/*-------------------------------------------------
		读取器 - 读取 插件性能 字符串
*/
void C_ScriptHelp_Performance::readPerformance(QString performance_context){
	if (performance_context == ""){ return; }
	P_TxtFastReader group_reader = P_TxtFastReader(performance_context);

	// > 工作类型
	int i_working_type = group_reader.d_indexOf("工作类型");
	if (i_working_type != -1){
		QString data = group_reader.d_getRows(i_working_type, 1).first();
		QStringList data_list = data.split(QRegExp("[:： ]+"));
		data_list.removeFirst();
		if (data_list.count() >= 1){
			this->working_type = data_list.first();
		}
	}

	// > 时间复杂度
	int i_time_complexity = group_reader.d_indexOf("时间复杂度");
	if (i_time_complexity != -1){
		QString data = group_reader.d_getRows(i_time_complexity, 1).first();
		QStringList data_list = data.split(QRegExp("[:： ]+"));
		data_list.removeFirst();
		if (data_list.count() >= 1){
			this->time_complexity = data_list.join(" ");
		}
	}

	// > 测试列表
	this->test_list = QList<C_ScriptHelp_PerformanceTest>();
	int i_test = group_reader.d_indexOf(QRegExp("^(测试方法|测试结果)"));
	int i_testEnd = group_reader.d_indexOf(QRegExp("^测试结果"), i_test);
	int i_context_note = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.。]"));		//（说明列表）
	for (int k = 0; k < 15; k++){
		if (i_test != -1){

			// > 向下搜索
			QStringList data_list = QStringList();
			int i_nextTest = group_reader.d_indexOf(QRegExp("^(测试方法|测试结果)"), i_testEnd + 1);	//（找到多个章节后，addPage，再在子函数中继续细分）
			int i_nextTestEnd = group_reader.d_indexOf(QRegExp("^测试结果"), i_test);
			if (i_nextTest != -1){
				int page_count = i_nextTest - i_test;
				data_list = group_reader.d_getRows(i_test, page_count);
			}else{
				if (i_context_note == -1){
					data_list = group_reader.d_getRows(i_test);
				}else{
					data_list = group_reader.d_getRows(i_context_note-1 - i_test );
				}
			}

			// > 添加到列表
			if (data_list.count() > 0){
				QString data = data_list.join("\n");
				C_ScriptHelp_PerformanceTest test = C_ScriptHelp_PerformanceTest();
				test.readTest(data);
				this->test_list.append(test);
			}

			i_test = i_nextTest;
			i_testEnd = i_nextTestEnd;
		}
		else{
			break;
		}
	}

	// > 说明列表
	if (i_context_note > 0){
		QStringList contextComment = group_reader.d_getRows(i_context_note);
		if (contextComment.count() > 0){

			P_TxtFastReader commentReader = P_TxtFastReader(contextComment.join("\n"));
			int i_page = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."));	//（找到数字的行）
			for (int k = 0; k < 15; k++){
				if (i_page != -1){

					// > 向下搜索
					QStringList data_list = QStringList();
					int i_nextPage = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."), i_page + 1);	//（找到多个章节后，addPage，再在子函数中继续细分）
					if (i_nextPage != -1){
						int page_count = i_nextPage - i_page;
						data_list = commentReader.d_getRows(i_page, page_count);
					}
					else{
						data_list = commentReader.d_getRows(i_page);
					}

					// > 添加到列表
					if (data_list.count() > 0){
						QString data = data_list.join("\n");
						contextComment.append(data);
					}

					i_page = i_nextPage;
				}
				else{
					break;
				}
			}
		}
		this->context_note = contextComment;
	}
}