#include "stdafx.h"
#include "c_ScriptHelp_Performance.h"

#include "s_Const_Performance.h"


/*
-----==========================================================-----
		�ࣺ		��������-���Խ�� ������.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_PerformanceTestDetail::C_ScriptHelp_PerformanceTestDetail(){
	this->cost = -1;					//����ֵ
	this->description = "";				//��������
	this->condition_scene = "";			//���� - ����
	this->condition_level = 0;			//���� - �̶�
}
C_ScriptHelp_PerformanceTestDetail::~C_ScriptHelp_PerformanceTestDetail(){
}

/*-------------------------------------------------
		���� - ��ȡ����ֵ
*/
double C_ScriptHelp_PerformanceTestDetail::getCostValue(){
	return this->cost;
}
/*-------------------------------------------------
		���� - ��ȡ������ʾ�ı�
*/
QString C_ScriptHelp_PerformanceTestDetail::getCostString(){
	if (this->cost <= 0){ return "����ֵ����"; }
	if (this->cost < 5){ return "5ms����"; }
	return QString::number(this->cost)+"ms";
}
/*-------------------------------------------------
		���� - ��ȡ��������
*/
QString C_ScriptHelp_PerformanceTestDetail::getDescription(){
	return this->description;
}
/*-------------------------------------------------
		���� - ��ȡ���� - ����
*/
QString C_ScriptHelp_PerformanceTestDetail::getCondition_scene(){
	return this->condition_scene;
}
/*-------------------------------------------------
		���� - ��ȡ���� - �̶�
*/
int C_ScriptHelp_PerformanceTestDetail::getCondition_level(){
	return this->condition_level;
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_ScriptHelp_PerformanceTestDetail::isNull(){
	return this->cost == -1;
}
/*-------------------------------------------------
		���� - ��ȡ ���Խ�� �ַ���
*/
void C_ScriptHelp_PerformanceTestDetail::readTestDetail(QString one_row){
	if (one_row.isEmpty()){ return; }

	// > ������ֵ������
	one_row = one_row.replace("��", "");
	QStringList str_list = one_row.split("��");
	if (str_list.count() < 2){ return; }

	// > ��������
	this->description = str_list.at(0);	

	// > ����ֵ
	QString cost_text = str_list.at(1);
	cost_text = cost_text.replace(QRegExp("[^0-9e\\.]+"), "");		//��ֻ�����֣�
	this->cost = cost_text.toDouble();

	// > ���� - ��һ����
	QStringList word_list = S_Const_Performance::getInstance()->getPerformanceWord_All();
	for (int i = 0; i < word_list.count(); i++){
		QString word = word_list.at(i);
		if (this->description.contains(word)){
			this->condition_scene = S_Const_Performance::getInstance()->getSceneName_ByPerformanceWord(word);
			this->condition_level = S_Const_Performance::getInstance()->getLevel_ByPerformanceWord(word);
			break;
		}
	}

	// > ���� - û�ҵ������������Ƽ�����
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
		�ࣺ		��������-���Խ�� ������.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_PerformanceTest::C_ScriptHelp_PerformanceTest(){
	this->text_method = QString();										//���Է���
	this->detail_list = QList<C_ScriptHelp_PerformanceTestDetail>();	//���Խ��
}
C_ScriptHelp_PerformanceTest::~C_ScriptHelp_PerformanceTest(){
}

/*-------------------------------------------------
		���� - ��ȡ�����б�
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
		���� - ��ȡ�������
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
		���� - ��ȡ������ģ�����������
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
		���� - ��ȡ��С���ģ�����������
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
		��ȡ�� - ��ȡ ���Խ�� �ַ���
*/
void C_ScriptHelp_PerformanceTest::readTest(QString test_context){
	test_context = test_context.replace(QRegExp("^���Է���[\\d]*[:�� ]+"),"");
	QStringList data_list = test_context.split(QRegExp("���Խ��[\\d]*[:�� ]+"));
	if (data_list.count() < 2){ return; }
	
	// > ���Է���
	this->text_method = data_list.first().replace(QRegExp("[\n\r\t ]+"), "");
	data_list.removeFirst();
	
	// > �����б�
	QString data_str = data_list.join("");
	data_str = data_str.replace(QRegExp("�������.*"), "");
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
		�ࣺ		��������-������� ������.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Performance::C_ScriptHelp_Performance(){
	this->working_type = QString();									//��������
	this->time_complexity = QString();								//ʱ�临�Ӷ�
	this->test_list = QList<C_ScriptHelp_PerformanceTest>();		//���Խ���б�
	this->context_note = QStringList();								//�����б�
	this->max_cost = -1;
}
C_ScriptHelp_Performance::~C_ScriptHelp_Performance(){
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_ScriptHelp_Performance::isNull(){
	return this->test_list.count() == 0 || this->max_cost == -1;
}
/*-------------------------------------------------
		���� - ��ȡ�������
*/
double C_ScriptHelp_Performance::getMaxCost(){
	return this->max_cost;
}
/*-------------------------------------------------
		���� - ��ȡ������ģ�˽�У�
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
		���� - ��ȡ������ģ�����������
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
		���� - ��ȡ��С���ģ�����������
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
		���� - �Ƿ������
*/
bool C_ScriptHelp_Performance::isHighCost(){
	return this->getMaxCost() >= 120;
}
/*-------------------------------------------------
		���� - �Ƿ�������
*/
bool C_ScriptHelp_Performance::isMiddleCost(){
	return this->getMaxCost() >= 80;
}
/*-------------------------------------------------
		���� - �Ƿ������
*/
bool C_ScriptHelp_Performance::isLowCost(){
	return this->getMaxCost() >= 40;
}

/*-------------------------------------------------
		��ȡ�� - ��ȡ ������� �ַ���
*/
void C_ScriptHelp_Performance::readPerformance(QString performance_context){
	if (performance_context == ""){ return; }
	P_TxtFastReader group_reader = P_TxtFastReader(performance_context);

	// > ��������
	int i_working_type = group_reader.d_indexOf("��������");
	if (i_working_type != -1){
		QString data = group_reader.d_getRows(i_working_type, 1).first();
		QStringList data_list = data.split(QRegExp("[:�� ]+"));
		data_list.removeFirst();
		if (data_list.count() >= 1){
			this->working_type = data_list.first();
		}
	}

	// > ʱ�临�Ӷ�
	int i_time_complexity = group_reader.d_indexOf("ʱ�临�Ӷ�");
	if (i_time_complexity != -1){
		QString data = group_reader.d_getRows(i_time_complexity, 1).first();
		QStringList data_list = data.split(QRegExp("[:�� ]+"));
		data_list.removeFirst();
		if (data_list.count() >= 1){
			this->time_complexity = data_list.join(" ");
		}
	}

	// > �����б�
	this->test_list = QList<C_ScriptHelp_PerformanceTest>();
	int i_test = group_reader.d_indexOf(QRegExp("^(���Է���|���Խ��)"), i_time_complexity);
	int i_testEnd = group_reader.d_indexOf(QRegExp("^���Խ��"), i_test);
	int i_context_note = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"), i_time_complexity);		//��˵���б�
	for (int k = 0; k < 15; k++){
		if (i_test != -1){

			// > ��������
			QStringList data_list = QStringList();
			int i_nextTest = group_reader.d_indexOf(QRegExp("^(���Է���|���Խ��)"), i_testEnd + 1);	//���ҵ�����½ں�addPage�������Ӻ����м���ϸ�֣�
			int i_nextTestEnd = group_reader.d_indexOf(QRegExp("^���Խ��"), i_nextTest);
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

			// > ��ӵ��б�
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

	// > ˵���б�
	if (i_context_note > 0){
		QStringList contextComment = group_reader.d_getRows(i_context_note);
		this->context_note.clear();
		if (contextComment.count() > 0){

			P_TxtFastReader commentReader = P_TxtFastReader(contextComment.join("\n"));
			int i_page = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."));	//���ҵ����ֵ��У�
			for (int k = 0; k < 15; k++){
				if (i_page != -1){

					// > ��������
					QStringList data_list = QStringList();
					int i_nextPage = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."), i_page + 1);	//���ҵ�����½ں�addPage�������Ӻ����м���ϸ�֣�
					if (i_nextPage != -1){
						int page_count = i_nextPage - i_page;
						data_list = commentReader.d_getRows(i_page, page_count);
					}
					else{
						data_list = commentReader.d_getRows(i_page);
					}

					// > ��ӵ��б�
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

	// > �ݴ����ֵ
	this->max_cost = this->getMaxCost_Private();
}