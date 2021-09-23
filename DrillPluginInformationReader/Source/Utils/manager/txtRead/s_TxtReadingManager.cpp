#include "stdafx.h"
#include "S_TxtReadingManager.h"

#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		log�ļ�������.cpp
		�汾��		v1.07
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		��ȡ/�淶/ת�� �ı��ļ������ݡ�
					��ר�Ŷ�һƪ�ı��������ٶȽ�����

		Ŀ�꣺		1.�����ַ����ָ�ʱ���ֵ����������
					2.�淶ȷ��ÿ�ж��ܱ�������
					3.ֱ�Ӳ�����ֱ���������ҵ�����ַ���
					  ����������һ��һ�������ң�ֻ����һ�Ρ�
					4.�������ı����̱仯�ϴ��log��־�ļ��ķ��롣

		ע�����	1.�ù�����ֻ���ı��������ع淶�õ��ı���

		ʹ�÷�����
				>�淶�ı�
					S_TxtReadingManager* _log_ = S_TxtReadingManager::getInstance();
					_log_->initLog();
					_log_->setLog(context);
	
					_log_->trimAllRows();
					_log_->clearEmptyRows();
					_log_->clearComment("#");

-----==========================================================-----
*/

S_TxtReadingManager::S_TxtReadingManager(){
	initLog();
}
S_TxtReadingManager::~S_TxtReadingManager() {
}
/* -------------����------------ */
S_TxtReadingManager* S_TxtReadingManager::cur_instance = NULL;
S_TxtReadingManager* S_TxtReadingManager::getInstance() {
	if (cur_instance == NULL) {
		cur_instance = new S_TxtReadingManager();
	}
	return cur_instance;
}

/*-------------------------------------------------
		���� - ��ʼ��
*/
void S_TxtReadingManager::initLog() {
	this->log_context_org = "";
	this->log_context_list = QStringList();
}
/*-------------------------------------------------
		���� - ��������
*/
void S_TxtReadingManager::setLog(QString log) {
	this->log_context_org = log;
	this->log_context_list = this->log_context_org.split(QRegExp("[\n\r]+"));
}

/*-------------------------------------------------
		ȫ�� - ����ո�
*/
void S_TxtReadingManager::trimAllRows() {
	this->log_context_list.replaceInStrings(QRegExp("^[ \t]+"), "");
	this->log_context_list.replaceInStrings(QRegExp("[ \t]+$"), "");
}
/*-------------------------------------------------
		ȫ�� - �滻�ַ�
*/
void S_TxtReadingManager::replaceInStrings(QString re_str, QString str) {
	this->log_context_list.replaceInStrings(re_str, str);
}
void S_TxtReadingManager::replaceInStrings(QRegExp re, QString str) {
	this->log_context_list.replaceInStrings(re, str);
}
/*-------------------------------------------------
		ȫ�� - �������
*/
void S_TxtReadingManager::clearEmptyRows() {
	QStringList result = QStringList();
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString str = this->log_context_list.at(i).trimmed();
		if (str != "") {
			result.push_back(str);
		}
	}
	this->log_context_list = result;
}
/*-------------------------------------------------
		ȫ�� - ȥ��ע���У��������ַ���
*/
void S_TxtReadingManager::clearComment(QString prefix) {
	QStringList result = QStringList();
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString str = this->log_context_list.at(i);
		if (str.mid(0, prefix.length()) != prefix) {
			result.push_back(str);
		}
	}
	this->log_context_list = result;
}
/*-------------------------------------------------
		ȫ�� - ��ȡȫ��
*/
QStringList S_TxtReadingManager::getAllRows() {
	return this->log_context_list;
}

/*-------------------------------------------------
		���޸� - �����
*/
void S_TxtReadingManager::appendRow(QString context) {
	this->log_context_list.append(context);
}
/*-------------------------------------------------
		���޸� - ��Ӷ���
*/
void S_TxtReadingManager::appendRows(QStringList context) {
	this->log_context_list.append(context);
}
/*-------------------------------------------------
		���޸� - ������
*/
void S_TxtReadingManager::insertRow(int index, QString context) {
	this->log_context_list.insert(index,context);
	QList<int> list = m_used_rows.toList();		//�����������޸��±�
	for (int i = 0; i < list.count();i++) {
		if (list.at(i) >= index) { list[i] = list.at(i) + 1; }
	}
	m_used_rows = list.toSet();
}
/*-------------------------------------------------
		���޸� - �������
*/
void S_TxtReadingManager::insertRows(int index, QStringList context) {
	for (int i = 0; i < context.count(); i++) {
		this->log_context_list.insert(index+i, context.at(i));
	}
	QList<int> list = m_used_rows.toList();		//�����������޸��±�
	for (int i = 0; i < list.count(); i++) {
		if (list.at(i) >= index) {
			list[i] = list.at(i) + context.count();
		}
	}
	m_used_rows = list.toSet();
}
/*-------------------------------------------------
		���޸� - �滻��
*/
void S_TxtReadingManager::replaceRow(int index, QString context) {
	this->log_context_list.replace(index, context);
	QList<int> list = m_used_rows.toList();		//�����������޸��±�
	for (int i = 0; i < list.count(); i++) {
		if (list.at(i) == index) {
			list.removeAt(i);
			break;
		}
	}
	m_used_rows = list.toSet();
}
/*-------------------------------------------------
		���޸� - ȥ����
*/
void S_TxtReadingManager::removeRow(int index) {
	this->log_context_list.removeAt(index);
	QList<int> list = m_used_rows.toList();		//�����������޸��±�
	for (int i = 0; i < list.count(); i++) {
		if (list.at(i) == index) {
			list.removeAt(i);
			break;
		}
	}
	m_used_rows = list.toSet();
}
/*-------------------------------------------------
		���޸� - ȥ������
*/
void S_TxtReadingManager::removeRows(QList<int> index_list) {
	qSort(index_list.begin(), index_list.end());
	for (int i = index_list.count()-1; i >= 0; i--) {
		this->log_context_list.removeAt(index_list.at(i));
	}
	QList<int> list = m_used_rows.toList();		//�����������޸��±�
	for (int i = list.count()-1; i >= 0; i--) {
		if (index_list.contains(list.at(i))) {
			list.removeAt(i);
			break;
		}
	}
	m_used_rows = list.toSet();
}

/*-------------------------------------------------
		ֱ�� - ��i��
*/
QString S_TxtReadingManager::d_rowAt(int i) {
	if (i<0 || i>=this->d_rowCount()) {
		return "";
	}
	m_used_rows.insert(i);
	return log_context_list.at(i);
}
/*-------------------------------------------------
		ֱ�� - ����
*/
int S_TxtReadingManager::d_rowCount() {
	return log_context_list.count();
}

/*-------------------------------------------------
		ֱ�� - ��ȡ������
*/
int S_TxtReadingManager::d_indexOf(QString contains) {
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(contains)) {
			m_used_rows.insert(i);
			return i;
		}
	}
	return -1;
}
int S_TxtReadingManager::d_indexOf(QRegExp re_contains) {
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(re_contains)) {
			m_used_rows.insert(i);
			return i;
		}
	}
	return -1;
}
/*-------------------------------------------------
		ֱ�� - ��ȡ�����У���ĩβ�ң�
*/
int S_TxtReadingManager::d_lastIndexOf(QString contains) {
	for (int i = this->log_context_list.count()-1; i >=0 ; i--) {
		QString result = this->log_context_list.at(i);
		if (result.contains(contains)) {
			m_used_rows.insert(i);
			return i;
		}
	}
	return -1;
}
int S_TxtReadingManager::d_lastIndexOf(QRegExp re_contains) {
	for (int i = this->log_context_list.count() - 1; i >= 0; i--) {
		QString result = this->log_context_list.at(i);
		if (result.contains(re_contains)) {
			m_used_rows.insert(i);
			return i;
		}
	}
	return -1;
}

/*-------------------------------------------------
		ֱ�� - ��ȡ�����У�ָ����Χ��
*/
int S_TxtReadingManager::d_indexOf(QString contains, int n, int m) {
	if (n == -1) { n = 0; }
	if (m == -1) { m = this->log_context_list.count(); }
	if (m >= this->log_context_list.count() ) { m = this->log_context_list.count(); }
	for (int i = n; i < m; i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(contains)) {
			m_used_rows.insert(i);
			return i;
		}
	}
	return -1;
}
int S_TxtReadingManager::d_indexOf(QRegExp re_contains, int n, int m) {
	if (n == -1) { n = 0; }
	if (m == -1) { m = this->log_context_list.count(); }
	if (m >= this->log_context_list.count()) { m = this->log_context_list.count(); }
	for (int i = n; i < m; i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(re_contains)) {
			m_used_rows.insert(i);
			return i;
		}
	}
	return -1;
}

/*-------------------------------------------------
		ֱ�� - ��ȡ�����У�ָ����Χ��
*/
QStringList S_TxtReadingManager::d_getRows(int n, int row_count) {
	if (n == -1) { n = 0; }
	int m = n + row_count;
	if (row_count == -1) { m = this->log_context_list.count(); }
	if (m >= this->log_context_list.count()) { m = this->log_context_list.count(); }
	QStringList result_list = QStringList();
	for (int i = n; i < m; i++) {
		QString result = this->log_context_list.at(i);
		m_used_rows.insert(i);
		result_list.push_back(result);
	}
	return result_list;
}


/*-------------------------------------------------
		ֱ�� - ��ȡ������������
*/
QList<int> S_TxtReadingManager::d_getAllRowIndexsContains(QString contains){
	QList<int> result_list = QList<int>();
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(contains)) {
			m_used_rows.insert(i);
			result_list.push_back(i);
		}
	}
	return result_list;
}
QList<int> S_TxtReadingManager::d_getAllRowIndexsContains(QRegExp re_contains){
	QList<int> result_list = QList<int>();
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(re_contains)) {
			m_used_rows.insert(i);
			result_list.push_back(i);
		}
	}
	return result_list;
}
QStringList S_TxtReadingManager::d_getAllRowsContains(QString contains) {
	QStringList result_list = QStringList();
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(contains)) {
			m_used_rows.insert(i);
			result_list.push_back(result);
		}
	}
	return result_list;
}
QStringList S_TxtReadingManager::d_getAllRowsContains(QRegExp re_contains) {
	QStringList result_list = QStringList();
	for (int i = 0; i < this->log_context_list.count(); i++) {
		QString result = this->log_context_list.at(i);
		if (result.contains(re_contains)) {
			m_used_rows.insert(i);
			result_list.push_back(result);
		}
	}
	return result_list;
}

/*-------------------------------------------------
		ֱ�� - ��ȡ������������������
*/
QList<int> S_TxtReadingManager::d_getUsedIndexs(){
	return m_used_rows.toList();
}
void S_TxtReadingManager::d_clearUsedIndexs() {
	m_used_rows.clear();
}
/*-------------------------------------------------
		ֱ�� - ��ȡ������������������
*/
QStringList S_TxtReadingManager::d_getUnusedRows(QString mode) {
	QStringList result_list = QStringList();
	for (int i = 0; i < this->log_context_list.count() ; i++) {
		QString str = this->log_context_list.at(i);
		if ( !m_used_rows.contains(i)) {
			result_list.push_back(str);
		}
		else {
			if (mode == "") { continue; }
			if (mode == "empty_mode"){
				result_list.push_back("");
			}
			if (mode == "color_mode") {
				result_list.push_back("<span style=\" color:#bbbbbb; \">" + str + "</span>");	//��ɫ��ʾ
			}
		}
	}
	return result_list;
}

/*-------------------------------------------------
		�ַ��� - ��ȡ����
*/
QList<int> S_TxtReadingManager::s_getIntInRow(QString row) {
	QList<int> result_list = QList<int>();
	QStringList s_list = row.split(QRegExp("[ \t]+"));
	for (int i = 0; i < s_list.count(); i++) {
		QString result = s_list.at(i);
		if (TTool::_match_re_int_(result)) {
			result_list.push_back(result.toInt());
		}
	}
	return result_list;
}
QList<int> S_TxtReadingManager::s_getIntForceInRow(QString row) {
	return TTool::_to_ints_(row);
}

/*-------------------------------------------------
		�ַ��� - ��ȡ������
*/
QList<double> S_TxtReadingManager::s_getDoubleInRow(QString row) {
	QList<double> result_list = QList<double>();
	QStringList s_list = row.split(QRegExp("[ \t]+"));
	for (int i = 0; i < s_list.count(); i++) {
		QString result = s_list.at(i);
		if (TTool::_match_re_double_e_(result)) {
			result_list.push_back(result.toDouble());
		}
	}
	return result_list;
}
QList<double> S_TxtReadingManager::s_getDoubleForceInRow(QString row) {
	return TTool::_to_doubles_e_(row);
}