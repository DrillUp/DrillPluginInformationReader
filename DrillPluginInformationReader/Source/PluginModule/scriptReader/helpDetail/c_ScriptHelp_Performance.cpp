#include "stdafx.h"
#include "c_ScriptHelp_Performance.h"

#include "s_Const_Performance.h"


/*
-----==========================================================-----
		类：		帮助数据-测试结果 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_PerformanceTestDetail::C_ScriptHelp_PerformanceTestDetail(){
	this->cost = -1;					//消耗值
	this->description = "";				//描述内容
	this->condition_scene = "";			//条件 - 界面
	this->condition_level = 0;			//条件 - 程度
}
C_ScriptHelp_PerformanceTestDetail::~C_ScriptHelp_PerformanceTestDetail(){
}

/*-------------------------------------------------
		数据 - 获取消耗值
*/
double C_ScriptHelp_PerformanceTestDetail::getCostValue(){
	return this->cost;
}
/*-------------------------------------------------
		数据 - 获取消耗显示文本
*/
QString C_ScriptHelp_PerformanceTestDetail::getCostString(){
	if (this->cost <= 0){ return "消耗值错误"; }
	if (this->cost < 5){ return "5ms以下"; }
	return QString::number(this->cost)+"ms";
}
/*-------------------------------------------------
		数据 - 获取描述内容
*/
QString C_ScriptHelp_PerformanceTestDetail::getDescription(){
	return this->description;
}
/*-------------------------------------------------
		数据 - 获取条件 - 界面
*/
QString C_ScriptHelp_PerformanceTestDetail::getCondition_scene(){
	return this->condition_scene;
}
/*-------------------------------------------------
		数据 - 获取条件 - 程度
*/
int C_ScriptHelp_PerformanceTestDetail::getCondition_level(){
	return this->condition_level;
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_PerformanceTestDetail::isNull(){
	return this->cost == -1;
}
/*-------------------------------------------------
		数据 - 读取 测试结果 字符串
*/
void C_ScriptHelp_PerformanceTestDetail::readTestDetail(QString one_row){
	if (one_row.isEmpty()){ return; }

	// > 分离结果值和描述
	one_row = one_row.replace("】", "");
	QStringList str_list = one_row.split("【");
	if (str_list.count() < 2){ return; }

	// > 描述内容
	this->description = str_list.at(0);	

	// > 消耗值
	QString cost_text = str_list.at(1);
	cost_text = cost_text.replace(QRegExp("[^0-9e\\.]+"), "");		//（只留数字）
	this->cost = cost_text.toDouble();

	// > 条件 - 第一次找
	QStringList word_list = S_Const_Performance::getInstance()->getPerformanceWord_All();
	for (int i = 0; i < word_list.count(); i++){
		QString word = word_list.at(i);
		if (this->description.contains(word)){
			this->condition_scene = S_Const_Performance::getInstance()->getSceneName_ByPerformanceWord(word);
			this->condition_level = S_Const_Performance::getInstance()->getLevel_ByPerformanceWord(word);
			break;
		}
	}

	// > 条件 - 没找到，按界面名称继续找
	if (this->condition_level == 0){
		QStringList name_list = S_Const_Performance::getInstance()->getSceneName_All();
		for (int i = 0; i < name_list.count(); i++){
			QString name = name_list.at(i);
			if (this->description.contains(name)){
				this->condition_scene = name;
			}
		}
	}
}

/*
-----==========================================================-----
		类：		帮助数据-测试结果 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_PerformanceTest::C_ScriptHelp_PerformanceTest(){
	this->text_method = QString();										//测试方法
	this->detail_list = QList<C_ScriptHelp_PerformanceTestDetail>();	//测试结果
}
C_ScriptHelp_PerformanceTest::~C_ScriptHelp_PerformanceTest(){
}

/*-------------------------------------------------
		数据 - 获取消耗列表
*/
QList<double> C_ScriptHelp_PerformanceTest::getCostList(){
	QList<double> result_list = QList<double>();
	for (int i = 0; i < this->detail_list.count(); i++){
		C_ScriptHelp_PerformanceTestDetail detail = this->detail_list.at(i);
		result_list.append(detail.getCostValue());
	}
	return result_list;
}
/*-------------------------------------------------
		数据 - 获取最大消耗
*/
double C_ScriptHelp_PerformanceTest::getMaxCost(){
	QList<double> data_list = this->getCostList();
	if (data_list.count() == 0){ return -1; }
	double result = data_list.front();
	for (int i = 1; i < data_list.count(); i++){
		double data = data_list.at(i);
		if (result < data){
			result = data;
		}
	}
	return result;
}
/*-------------------------------------------------
		数据 - 获取最大消耗（根据条件）
*/
double C_ScriptHelp_PerformanceTest::getMaxCost_ByLevel(QString scene_name, int level){
	double result = -1;
	for (int i = 0; i < this->detail_list.count(); i++){
		C_ScriptHelp_PerformanceTestDetail detail = this->detail_list.at(i);
		if (detail.getCondition_level() == level &&
			detail.getCondition_scene() == scene_name){
			if (result == -1){
				result = detail.getCostValue();
			}
			if (result < detail.getCostValue()){
				result = detail.getCostValue();
			}
		}
	}
	return result;
}
/*-------------------------------------------------
		数据 - 获取最小消耗（根据条件）
*/
double C_ScriptHelp_PerformanceTest::getMinCost_ByLevel(QString scene_name, int level){
	double result = -1;
	for (int i = 0; i < this->detail_list.count(); i++){
		C_ScriptHelp_PerformanceTestDetail detail = this->detail_list.at(i);
		if (detail.getCondition_level() == level &&
			detail.getCondition_scene() == scene_name){
			if (result == -1){
				result = detail.getCostValue();
			}
			if (result > detail.getCostValue()){
				result = detail.getCostValue();
			}
		}
	}
	return result;
}
/*-------------------------------------------------
		读取器 - 读取 测试结果 字符串
*/
void C_ScriptHelp_PerformanceTest::readTest(QString test_context){
	test_context = test_context.replace(QRegExp("^测试方法[\\d]*[:： ]+"),"");
	QStringList data_list = test_context.split(QRegExp("测试结果[\\d]*[:： ]+"));
	if (data_list.count() < 2){ return; }
	
	// > 测试方法
	this->text_method = data_list.first().replace(QRegExp("[\n\r\t ]+"), "");
	data_list.removeFirst();
	
	// > 条件列表
	QString data_str = data_list.join("");
	data_str = data_str.replace(QRegExp("特殊测试.*"), "");
	QStringList condition_str_list = data_str.split(QRegExp("[\n\r\t][ ]+"));
	for (int i = 0; i < condition_str_list.count(); i++){
		QString condition_str = condition_str_list.at(i);

		C_ScriptHelp_PerformanceTestDetail detail;
		detail.readTestDetail(condition_str);
		if (detail.isNull()){ continue; }
		this->detail_list.append(detail);
	}
}


/*
-----==========================================================-----
		类：		帮助数据-插件性能 数据类.cpp
		作者：		drill_up
		所属模块：	插件模块
		功能：		帮助信息中的数据。
-----==========================================================-----
*/
C_ScriptHelp_Performance::C_ScriptHelp_Performance(){
	this->working_type = QString();									//工作类型
	this->time_complexity = QString();								//时间复杂度
	this->test_list = QList<C_ScriptHelp_PerformanceTest>();		//测试结果列表
	this->context_note = QStringList();								//内容列表
	this->max_cost = -1;
}
C_ScriptHelp_Performance::~C_ScriptHelp_Performance(){
}
/*-------------------------------------------------
		数据 - 空判断
*/
bool C_ScriptHelp_Performance::isNull(){
	return this->test_list.count() == 0 || this->max_cost == -1;
}
/*-------------------------------------------------
		数据 - 获取最大消耗
*/
double C_ScriptHelp_Performance::getMaxCost(){
	return this->max_cost;
}
/*-------------------------------------------------
		数据 - 获取最大消耗（私有）
*/
double C_ScriptHelp_Performance::getMaxCost_Private(){
	if (this->test_list.count() == 0){ return -1; }
	C_ScriptHelp_PerformanceTest first_test = this->test_list.first();
	double result = first_test.getMaxCost();
	for (int i = 1; i < this->test_list.count(); i++){
		C_ScriptHelp_PerformanceTest test = this->test_list.at(i);
		double data = test.getMaxCost();
		if (result < data){
			result = data;
		}
	}
	return result;
}
/*-------------------------------------------------
		数据 - 获取最大消耗（根据条件）
*/
double C_ScriptHelp_Performance::getMaxCost_ByLevel(QString scene_name, int level){
	if (this->test_list.count() == 0){ return -1; }
	double result = -1;
	for (int i = 0; i < this->test_list.count(); i++){
		C_ScriptHelp_PerformanceTest test = this->test_list.at(i);
		double data = test.getMaxCost_ByLevel(scene_name, level);
		if (data == -1){ continue; }
		if (result == -1){
			result = data;
		}
		if (result < data){
			result = data;
		}
	}
	return result;
}
/*-------------------------------------------------
		数据 - 获取最小消耗（根据条件）
*/
double C_ScriptHelp_Performance::getMinCost_ByLevel(QString scene_name, int level){
	if (this->test_list.count() == 0){ return -1; }
	double result = -1;
	for (int i = 0; i < this->test_list.count(); i++){
		C_ScriptHelp_PerformanceTest test = this->test_list.at(i);
		double data = test.getMinCost_ByLevel(scene_name, level);
		if (data == -1){ continue; }
		if (result == -1){
			result = data;
		}
		if (result > data){
			result = data;
		}
	}
	return result;
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
	int i_test = group_reader.d_indexOf(QRegExp("^(测试方法|测试结果)"), i_time_complexity);
	int i_testEnd = group_reader.d_indexOf(QRegExp("^测试结果"), i_test);
	int i_context_note = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.。]"), i_time_complexity);		//（说明列表）
	for (int k = 0; k < 15; k++){
		if (i_test != -1){

			// > 向下搜索
			QStringList data_list = QStringList();
			int i_nextTest = group_reader.d_indexOf(QRegExp("^(测试方法|测试结果)"), i_testEnd + 1);	//（找到多个章节后，addPage，再在子函数中继续细分）
			int i_nextTestEnd = group_reader.d_indexOf(QRegExp("^测试结果"), i_nextTest);
			if (i_nextTest != -1){
				int page_count = i_nextTest - i_test;
				data_list = group_reader.d_getRows(i_test, page_count);
			}else{
				if (i_context_note == -1){
					data_list = group_reader.d_getRows(i_test);
				}else{
					data_list = group_reader.d_getRows(i_test, i_context_note - 1 - i_test);
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
		this->context_note.clear();
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
						this->context_note.append(data);
					}

					i_page = i_nextPage;
				}else{
					break;
				}
			}
		}
	}

	// > 暂存最大值
	this->max_cost = this->getMaxCost_Private();
}