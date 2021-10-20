#include "stdafx.h"
#include "c_ScriptHelp_Subsection.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"


/*
-----==========================================================-----
		�ࣺ		��������-���� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�еĽ������ݡ�
					����ͷ"========"����ļ������ݡ�
-----==========================================================-----
*/
C_ScriptHelp_SubsectionHeader::C_ScriptHelp_SubsectionHeader(){
	this->introduction = "";
	this->package = "";
	this->condition = QStringList();
}
C_ScriptHelp_SubsectionHeader::~C_ScriptHelp_SubsectionHeader(){
}

/*
-----==========================================================-----
		�ࣺ		��������-�½� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
					��"----�趨ע������"�����С�ֶ����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_SubsectionPage::C_ScriptHelp_SubsectionPage(){
	this->title = "";
	this->context = QStringList();
}
C_ScriptHelp_SubsectionPage::~C_ScriptHelp_SubsectionPage(){
}

/*
-----==========================================================-----
		�ࣺ		��������-�ֶ�˵�� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
					���ۺ� ��������� �� "������"��������ݵ㡿
-----==========================================================-----
*/
C_ScriptHelp_Subsection::C_ScriptHelp_Subsection(){
	this->header = C_ScriptHelp_SubsectionHeader();
	this->main_list = QStringList();
	this->page_list = QList<C_ScriptHelp_SubsectionPage>();
}
C_ScriptHelp_Subsection::~C_ScriptHelp_Subsection(){
}

/*-------------------------------------------------
		��ȡ�� - ��ȡ ���� ����
*/
void C_ScriptHelp_Subsection::readHeader(QString context){
	if (context == ""){ return; }
	P_TxtFastReader header_reader = P_TxtFastReader(context);
	header_reader.clearEmptyRows();				//��������У�
	C_ScriptHelp_SubsectionHeader header;

	int i_introductionEnd = header_reader.d_indexOf(QRegExp("[����]"));
	if (i_introductionEnd == -1){

		// > �������� ���
		header.introduction = context.replace(QRegExp("[\n\r]+")," ");
	}else{
		
		// > ���
		QStringList introduction_list = header_reader.d_getRows(0,i_introductionEnd);
		header.introduction = introduction_list.join(" ");

		// > ���֧����ʾ
		QStringList data_list = header_reader.d_getRows(i_introductionEnd);
		QString data = data_list.first();
		if (data.contains("��")){
			header.package = data.replace(QRegExp("[����]"), "");
		}else{

			// > ��Ҫ�����б�
			header.condition.append(data);	//�ﲻ�滻
		}

		// > ��Ҫ�����б�
		if (data_list.count() > 1){
			for (int i = 1; i < data_list.count(); i++){
				QString data = data_list.at(i);
				header.condition.append(data);	//�ﲻ�滻
			}
		}
	}
	this->header = header;
}
/*-------------------------------------------------
		��ȡ�� - ��ȡ �ֶ�˵�� ����
*/
void C_ScriptHelp_Subsection::readSubsection(QString subsection_context, C_ScriptHelp_Docs* c_docs){
	P_TxtFastReader main_reader = P_TxtFastReader(subsection_context);
	main_reader.clearEmptyRows();				//��������У�

	// > �ֶ�˵�� - ������
	QStringList main_context = QStringList();
	int i_main = main_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"));
	int i_page = i_main;
	for (int k = 0; k < 15; k++){
		if (i_main != -1){

			// > ��������
			QString data = QString();
			int i_nextMain = main_reader.d_indexOf(QRegExp("^[^ ]+"), i_main + 1);	//���������пո��ʾ����û�꣩
			if (i_nextMain != -1){
				int main_count = i_nextMain - i_main;
				data = main_reader.d_getRows(i_main, main_count).join("\n");
			}
			else{
				data = main_reader.d_getRows(i_main).join("\n");
			}

			// > ��ӵ��б�
			if (data.isEmpty() == false &&
				data.contains("�����������") == false){	//�������������˵����
				data = data.replace(QRegExp("^[\\d]+[\\.��]"), "");
				c_docs->addMainDocx(c_docs->findDocsNameList(data));	//������ĵ� - ��Ҫ�ĵ���
				main_context.append(data.trimmed());
			}

			i_main = main_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"), i_main + 1);
		}
		else{
			break;
		}
	}
	this->main_list = main_context;

	// > �ֶ�˵�� - �½�
	i_page = main_reader.d_indexOf(QRegExp("^[^ \\d]+"), i_page + 1);	//���ҵ��ǿո񡢷����ֵ��У�
	for (int k = 0; k < 15; k++){
		if (i_page != -1){

			// > ��������
			QStringList data_list = QStringList();
			int i_nextPage = main_reader.d_indexOf(QRegExp("^[^ \\d]+"), i_page + 1);	//���ҵ�����½ں�addPage�������Ӻ����м���ϸ�֣�
			if (i_nextPage != -1){
				int page_count = i_nextPage - i_page;
				data_list = main_reader.d_getRows(i_page, page_count);
			}
			else{
				data_list = main_reader.d_getRows(i_page);
			}

			// > ��ӵ��б�
			if (data_list.count() > 0){
				QString data = data_list.join("\n");
				c_docs->addRelativeDocx(c_docs->findDocsNameList(data));	//������ĵ� - ����ĵ���
				this->readNextPage(data);
			}

			i_page = i_nextPage;
		}
		else{
			break;
		}
	}
}
/*-------------------------------------------------
		��ȡ�� - ����½�
*/
void C_ScriptHelp_Subsection::readNextPage(QString page_context){
	if (page_context == ""){ return; }
	C_ScriptHelp_SubsectionPage page;
	P_TxtFastReader page_reader = P_TxtFastReader(page_context);

	// > ����
	QString title = page_reader.d_getRows(0, 1).at(0);
	title = title.replace(QRegExp("[:��]"), "").trimmed();
	page.title = title;
	
	// > С�½�
	QRegExp page_re("^[ ]+[\\(��][\\d]+\\.");
	int i_label = page_reader.d_indexOf(page_re, 1);	//���ҵ������½ڣ�
	for (int i = 0; i < 15; i++){
		if (i_label != -1){
			int i_nextLabel = page_reader.d_indexOf(page_re, i_label + 1);
			if (i_nextLabel != -1){
				int page_count = i_nextLabel - i_label;
				QStringList data_list = page_reader.d_getRows(i_label, page_count);

				// > ȥ�� ���ǰ׺�Ϳո�
				QStringList result_list = QStringList();
				for (int j = 0; j < data_list.count(); j++){
					QString text = data_list.at(j);
					text = text.replace(page_re, "");
					result_list.append(text.trimmed());
				}

				page.context.append(result_list.join("\n"));
				i_label = i_nextLabel;
			}else{
				QStringList data_list = page_reader.d_getRows(i_label);

				// > ȥ�� ���ǰ׺�Ϳո�
				QStringList result_list = QStringList();
				for (int j = 0; j < data_list.count(); j++){
					QString text = data_list.at(j);
					text = text.replace(page_re, "");
					result_list.append(text.trimmed());
				}

				page.context.append(result_list.join("\n"));
				break;
			}
		}
		else{
			break;
		}
	}

	this->page_list.append(page);
}


/*-------------------------------------------------
		���� - ���ж�
*/
bool C_ScriptHelp_Subsection::isNull(){
	return this->main_list.count() == 0 && this->page_list.count() == 0 && this->header.introduction == "";
}
/*-------------------------------------------------
		���� - ��ȡ������
*/
QStringList C_ScriptHelp_Subsection::getMainContext(){
	return this->main_list;
}
/*-------------------------------------------------
		���� - ��ȡ��������
*/
C_ScriptHelp_SubsectionHeader C_ScriptHelp_Subsection::getHeader(){
	return this->header;
}
/*-------------------------------------------------
		���� - ��ȡ�½ڱ���
*/
QStringList C_ScriptHelp_Subsection::getAllTitle(){
	QStringList result;
	for (int i = 0; i < this->page_list.count(); i++){
		result.append(page_list.at(i).title);
	}
	return result;
}
/*-------------------------------------------------
		���� - ��ȡ�½ڣ����ݱ��⣩
*/
C_ScriptHelp_SubsectionPage C_ScriptHelp_Subsection::getPageByTitle(QString title){
	for (int i = 0; i < this->page_list.count(); i++){
		C_ScriptHelp_SubsectionPage page = this->page_list.at(i);
		if (page.title == title){
			return page;
		}
	}
	return C_ScriptHelp_SubsectionPage();
}
/*-------------------------------------------------
		���� - ��ȡ�½����ݣ����ݱ��⣩
*/
QStringList C_ScriptHelp_Subsection::getPageContextByTitle(QString title){
	return this->getPageByTitle(title).context;
}
