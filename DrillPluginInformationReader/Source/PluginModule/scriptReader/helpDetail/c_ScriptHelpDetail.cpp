#include "stdafx.h"
#include "c_ScriptHelpDetail.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"

/*
-----==========================================================-----
		�ࣺ		���ע�� ʵ����.cpp
		����ģ�飺	���ģ��
		���ܣ�		���ע������ݡ�

		��Ҫ���	> �������Ϊ��js�ű��ж�ȡ�������ݡ�
					  ����js�ű���ʱ�ɱ䣬���Բ�����洢��
-----==========================================================-----
*/
C_ScriptHelpDetail::C_ScriptHelpDetail(){
	this->name = "";			 	//��������ļ�����
	this->help = "";				//������Ϣ��@help��

	this->m_effectScope = nullptr;			//������
	this->m_pluginRelation = nullptr;		//�����չ
	this->m_src = nullptr;					//��Դ·��
	this->m_docs = nullptr;					//����ĵ�
	this->m_subsection = nullptr;			//�ֶ�˵��
	this->m_command = nullptr;				//ָ��
	this->m_performance = nullptr;			//�������
}
C_ScriptHelpDetail::~C_ScriptHelpDetail(){
}


/*-------------------------------------------------
		���� - ���ò����
*/
void C_ScriptHelpDetail::setName(QString name){
	this->name = name;
}
/*-------------------------------------------------
		���� - ���ð�����Ϣ
*/
void C_ScriptHelpDetail::setHelpContext(QString help){
	this->help = help;
	this->initHelpContext();
}
/*-------------------------------------------------
		���� - ��ȡ�����
*/
QString C_ScriptHelpDetail::getName(){
	return this->name;
}
/*-------------------------------------------------
		���� - ��ȡ������Ϣ
*/
QString C_ScriptHelpDetail::getHelpContext(){
	return this->help;
}


/*-------------------------------------------------
		˽�� - ������Ϣ��ʼ��
*/
void C_ScriptHelpDetail::initHelpContext(){
	P_TxtFastReader reader = P_TxtFastReader(this->help);
	this->m_docs = new C_ScriptHelp_Docs();			//����ĵ�����ʼ��Ҫ������
	this->m_command = new C_ScriptHelp_Command();	//ָ���ʼ��Ҫ������

	// > �����չ
	int i_relation = reader.d_indexOf("----�����չ");
	if (i_relation != -1){
		//...
	}

	// > ������
	int i_effectScope = reader.d_indexOf("�����������");
	if (i_effectScope != -1){
		this->m_effectScope = new C_ScriptHelp_EffectScope();
		QStringList row_list = reader.d_getRows(i_effectScope, 4);
		for (int k = 0; k < row_list.count(); k++){
			QString row = row_list.at(k);
			if (k == 0){
				QString data = row.split("�����������").last();
				data = data.replace(QRegExp("[\\.��]"), "").trimmed();
				this->m_effectScope->scope_list = data.split(QRegExp("[��,��]"));
				continue;
			}
			if (row.count() > 0 && row.at(0) == ' '){	//���пո��ʾ�½�û˵�꣩
				this->m_effectScope->comments.append(row);
				this->m_effectScope->comments.append("\n");
			}else{
				break;
			}
		}
	}


	// > �ֶ�˵��
	int i_mainComment = reader.d_indexOf("----�趨ע������");
	int i_mainComment_end = reader.d_indexOf("----------------------", i_mainComment + 1);
	if (i_mainComment != -1){
		int row_count = i_mainComment_end - i_mainComment - 1;
		QStringList mainComment = reader.d_getRows(i_mainComment + 1, row_count);
		P_TxtFastReader main_reader = P_TxtFastReader(mainComment.join("\n"));

		this->m_subsection = new C_ScriptHelp_Subsection();

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
				}else{
					data = main_reader.d_getRows(i_main).join("\n");
				}

				// > ��ӵ��б�
				if (data.isEmpty() == false &&
					data.contains("�����������") == false){	//�������������˵����
					data = data.replace(QRegExp("^[\\d]+[\\.��]"), "");
					this->m_docs->addMainDocx(this->findDocsNameList(data));	//������ĵ� - ��Ҫ�ĵ���
					main_context.append(data.trimmed());
				}

				i_main = main_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"), i_main + 1);
			}else{
				break;
			}
		}
		this->m_subsection->setMainContext(main_context);

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
				}else{
					data_list = main_reader.d_getRows(i_page);
				}

				// > ��ӵ��б�
				if (data_list.count() > 0){
					QString data = data_list.join("\n");
					this->m_docs->addRelativeDocx(this->findDocsNameList(data));	//������ĵ� - ����ĵ���
					this->m_subsection->readNextPage(data);
				}

				i_page = i_nextPage;
			}else{
				break;
			}
		}
	}

	// > ��Դ·��
	int i_src = reader.d_indexOf("----�����ļ�");
	int i_src_end = reader.d_indexOf("----------------------", i_src + 1);
	if (i_src != -1){
		int row_count = i_src_end - i_src - 1;
		QStringList srcComment = reader.d_getRows(i_src + 1, row_count);
		this->m_src = new C_ScriptHelp_Src();

		int i_context = 0;
		for (int i = 0; i < 4; i++){
			QString row = srcComment.at(i);
			if (row.contains("��Դ·����")){
				QString data = row.replace("��Դ·����", "");
				data = data.mid(0, data.indexOf(QRegExp("[ \\(��\n]"))).trimmed();
				if (data.isEmpty() == false){
					this->m_src->src_list.append(data);
				}
				i_context += 1;
			}else{
				break;
			}
		}
		
		QString context = "";
		QString example = "";
		bool is_context = true;
		for (int i = i_context; i < srcComment.count(); i++){
			QString row = srcComment.at(i);
			if (is_context == true && row.contains(QRegExp("[:��]"))){		//��������һ�е�ð�����ָ� ·��˵�� �� ����˵�� ��
				is_context = false;
				context.append(row);
				continue;
			}
			
			// > ·��˵��
			if (is_context){
				context.append(row);
				context.append("\n");
				continue;
			}

			// > ����˵��
			example.append(row);
			if (i < srcComment.count()-1){
				example.append("\n");
			}
		}
		this->m_src->context = context;
		this->m_src->example = example;

	}

	// > ָ��
	int i_command = reader.d_indexOf(QRegExp("----(��������|��ѡ�趨)"));
	int i_command_end = reader.d_indexOf("----------------------", i_command + 1);
	for (int k = 0; k < 20; k++){
		if (i_command == -1){ break; }

		int row_count = i_command_end - i_command - 1;
		if (row_count < 0){ row_count = -1; }
		QStringList commandComment = reader.d_getRows(i_command + 1, row_count);
		this->m_command->readNextGroup(commandComment.join("\n"));

		i_command = reader.d_indexOf(QRegExp("----(��������|��ѡ�趨)"), i_command + 1);
		i_command_end = reader.d_indexOf("----------------------", i_command + 1);
	}

	// > �������

}
/*-------------------------------------------------
		���� - ��ȡ������
*/
C_ScriptHelp_EffectScope* C_ScriptHelpDetail::getEffectScope(){
	return this->m_effectScope;
}
/*-------------------------------------------------
		���� - ��ȡ�����չ
*/
C_ScriptHelp_PluginRelation* C_ScriptHelpDetail::getPluginRelation(){
	return this->m_pluginRelation;
}
/*-------------------------------------------------
		���� - ��ȡ��Դ·��
*/
C_ScriptHelp_Src* C_ScriptHelpDetail::getSrc(){
	return this->m_src;
}
/*-------------------------------------------------
		���� - ��ȡ����ĵ�
*/
C_ScriptHelp_Docs* C_ScriptHelpDetail::getDocs(){
	return this->m_docs;
}
/*-------------------------------------------------
		���� - ��ȡ�ֶ�˵��
*/
C_ScriptHelp_Subsection* C_ScriptHelpDetail::getSubsection(){
	return this->m_subsection;
}
/*-------------------------------------------------
		���� - ��ȡָ��
*/
C_ScriptHelp_Command* C_ScriptHelpDetail::getCommand(){
	return this->m_command;
}
/*-------------------------------------------------
		���� - ��ȡ�������
*/
C_ScriptHelp_Performance* C_ScriptHelpDetail::getPerformance(){
	return this->m_performance;
}

/*-------------------------------------------------
		˽�� - Ѱ���ĵ�����
*/
QStringList C_ScriptHelpDetail::findDocsNameList(QString context){

	// > ��ȡ��ƥ�䣨����ǰ���� �ո����� �����ԣ�
	QRegExp rx("[ \"��]([^ \"��]+\\.(docx|xlsx))");
	QStringList match_list = QStringList();
	int pos = 0;
	while ((pos = rx.indexIn(context, pos)) != -1) {
		match_list << rx.cap(1);
		pos += rx.matchedLength();
	}
	return match_list;
}


/*-------------------------------------------------
		���ж�
*/
bool C_ScriptHelpDetail::isNull(){
	return this->name == "";
}
/*-------------------------------------------------
		���������
*/
const bool C_ScriptHelpDetail::operator== (const C_ScriptHelpDetail& a)const {
	return this->name == a.name;
}
/*-------------------------------------------------
		ʵ���� -> QJsonObject
*/
QJsonObject C_ScriptHelpDetail::getJsonObject(){
	QJsonObject obj = QJsonObject();
	obj.insert("name", this->name);
	obj.insert("help", this->help);
	return obj;
}
/*-------------------------------------------------
		QJsonObject -> ʵ����
*/
void C_ScriptHelpDetail::setJsonObject(QJsonObject obj){

	if (obj.value("name").isUndefined() == false){ this->name = obj.value("name").toString(); }
	if (obj.value("help").isUndefined() == false){ this->help = obj.value("help").toString(); }

}

