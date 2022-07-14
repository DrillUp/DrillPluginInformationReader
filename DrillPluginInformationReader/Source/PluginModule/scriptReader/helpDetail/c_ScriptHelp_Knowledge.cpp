#include "stdafx.h"
#include "c_ScriptHelp_Knowledge.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��������-֪ʶ�� ������.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_KnowledgeGroup::C_ScriptHelp_KnowledgeGroup(){
	this->group_name = "";						//������
	this->context_data = QStringList();			//�����б�
	this->context_note = QStringList();			//�����б�
}
C_ScriptHelp_KnowledgeGroup::~C_ScriptHelp_KnowledgeGroup(){
}


/*
-----==========================================================-----
		�ࣺ		��������-ָ�� ������.cpp
		���ߣ�		drill_up
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Knowledge::C_ScriptHelp_Knowledge(){
	this->group_list = QList<C_ScriptHelp_KnowledgeGroup>();
}
C_ScriptHelp_Knowledge::~C_ScriptHelp_Knowledge(){
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_ScriptHelp_Knowledge::isNull(){
	return this->group_list.count() == 0;
}
/*-------------------------------------------------
		���� - ָ��б�
*/
QList<C_ScriptHelp_KnowledgeGroup> C_ScriptHelp_Knowledge::getGroupList(){
	return this->group_list;
}

/*-------------------------------------------------
		��ȡ�� - ��ȡ�µ�ָ��ַ���
*/
void C_ScriptHelp_Knowledge::readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs){
	if (group_context == ""){ return; }
	C_ScriptHelp_KnowledgeGroup group;
	P_TxtFastReader group_reader = P_TxtFastReader(group_context);

	// > ���Ⲷ��
	QString title = group_reader.d_getRows(0, 1).at(0);
	QStringList data_list = title.split(QRegExp("[ -]+"));
	if (data_list.count() > 2){
		group.group_name = data_list.last();
	}

	// > ���ݲ���
	int i_context_note = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"), 1);
	if (i_context_note > 0){

		// > ��˵������ʱ
		int row_count = i_context_note - 1;
		QStringList commandComment = group_reader.d_getRows(1, row_count);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.context_data = commandComment;
	}else{

		// > ��˵������ʱ����ȫ��Ϊ���ݣ�
		QStringList commandComment = group_reader.d_getRows(1);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.context_data = commandComment;
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
						c_docs->addRelativeDocx(c_docs->findDocsNameList(data));	//������ĵ� - ����ĵ���
						contextComment.append(data);
					}

					i_page = i_nextPage;
				}
				else{
					break;
				}
			}
		}
		group.context_note = contextComment;
	}

	this->group_list.append(group);
}