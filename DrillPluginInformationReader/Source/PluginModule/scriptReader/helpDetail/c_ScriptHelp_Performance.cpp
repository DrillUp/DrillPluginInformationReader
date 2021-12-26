#include "stdafx.h"
#include "c_ScriptHelp_Performance.h"


/*
-----==========================================================-----
		�ࣺ		��������-���Խ�� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_PerformanceTest::C_ScriptHelp_PerformanceTest(){
	this->text_method = QString();				//���Է���
	this->condition_list = QStringList();		//�����б�
	this->cost_list = QStringList();			//�����б�
}
C_ScriptHelp_PerformanceTest::~C_ScriptHelp_PerformanceTest(){
}

/*-------------------------------------------------
		���� - ��ȡ�����б�
*/
QList<double> C_ScriptHelp_PerformanceTest::getCostList(){
	QList<double> result_list = QList<double>();
	for (int i = 0; i < this->cost_list.count(); i++){
		QString cost = this->cost_list.at(i);
		cost = cost.replace(QRegExp("[^0-9e\\.]+"), "");		//��ֻ�����֣�
		result_list.append(cost.toDouble());
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡ�������
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
		��ȡ�� - ��ȡ ���Խ�� �ַ���
*/
void C_ScriptHelp_PerformanceTest::readTest(QString test_context){
	test_context = test_context.replace(QRegExp("^���Է���[:�� ]+"),"");
	QStringList data_list = test_context.split(QRegExp("���Խ��[:�� ]+"));
	if (data_list.count() < 2){ return; }
	
	// > ���Է���
	this->text_method = data_list.at(0);
	
	// > �����б�
	QStringList condition_str_list = data_list.at(1).split(QRegExp("[\n\r\t][ ]+"));
	for (int i = 0; i < condition_str_list.count(); i++){
		QString condition_str = condition_str_list.at(i);
		if (condition_str.isEmpty()){ continue; }

		condition_str = condition_str.replace("��", "");
		QStringList str_list = condition_str.split("��");
		if (str_list.count() < 2){ continue; }
		this->condition_list.append(str_list.at(0));	//����������˵�����֣�
		this->cost_list.append(str_list.at(1));
	}
}


/*
-----==========================================================-----
		�ࣺ		��������-������� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Performance::C_ScriptHelp_Performance(){
	this->working_type = QString();									//��������
	this->time_complexity = QString();								//ʱ�临�Ӷ�
	this->test_list = QList<C_ScriptHelp_PerformanceTest>();		//���Խ���б�
	this->context_note = QStringList();								//�����б�
}
C_ScriptHelp_Performance::~C_ScriptHelp_Performance(){
}
/*-------------------------------------------------
		���� - ��ȡ���Խ���б�
*/
QList<C_ScriptHelp_PerformanceTest> C_ScriptHelp_Performance::getTestList(){
	return this->test_list;
}
/*-------------------------------------------------
		���� - ��ȡ�������
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
		���� - ���ж�
*/
bool C_ScriptHelp_Performance::isNull(){
	return this->test_list.count() == 0;
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
	int i_test = group_reader.d_indexOf(QRegExp("^(���Է���|���Խ��)"));
	int i_testEnd = group_reader.d_indexOf(QRegExp("^���Խ��"), i_test);
	int i_context_note = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"));		//��˵���б�
	for (int k = 0; k < 15; k++){
		if (i_test != -1){

			// > ��������
			QStringList data_list = QStringList();
			int i_nextTest = group_reader.d_indexOf(QRegExp("^(���Է���|���Խ��)"), i_testEnd + 1);	//���ҵ�����½ں�addPage�������Ӻ����м���ϸ�֣�
			int i_nextTestEnd = group_reader.d_indexOf(QRegExp("^���Խ��"), i_test);
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