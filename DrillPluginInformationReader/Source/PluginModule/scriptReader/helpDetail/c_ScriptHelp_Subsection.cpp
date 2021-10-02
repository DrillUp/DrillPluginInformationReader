#include "stdafx.h"
#include "c_ScriptHelp_Subsection.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"

/*
-----==========================================================-----
		�ࣺ		��������-�½� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е��½ڡ�
-----==========================================================-----
*/
C_ScriptHelp_SubsectionPage::C_ScriptHelp_SubsectionPage(){
	this->title = "";
	this->comment_list = QStringList();
}
C_ScriptHelp_SubsectionPage::~C_ScriptHelp_SubsectionPage(){
}

/*
-----==========================================================-----
		�ࣺ		��������-�ֶ�˵�� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Subsection::C_ScriptHelp_Subsection(){
	this->main_list = QStringList();
	this->page_list = QList<C_ScriptHelp_SubsectionPage>();
}
C_ScriptHelp_Subsection::~C_ScriptHelp_Subsection(){
}

/*-------------------------------------------------
		���� - ����½�
*/
void C_ScriptHelp_Subsection::addPage(QString page_context){
	if (page_context == ""){ return; }
	C_ScriptHelp_SubsectionPage page;
	P_TxtFastReader page_reader = P_TxtFastReader(page_context);

	// > ����
	QString title = page_reader.d_getRows(0, 1).at(0);
	title = title.replace(QRegExp("[:��]"), "").trimmed();
	page.title = title;
	
	// > С��
	int i_label = page_reader.d_indexOf(QRegExp("^[ ]+[\\(��][\\d]+"),1);	//���ҵ������½ڣ�
	for (int i = 0; i < 15; i++){
		if (i_label != -1){
			int i_nextLabel = page_reader.d_indexOf(QRegExp("^[ ]+[\\(��][\\d]+"), i_label + 1);
			if (i_nextLabel != -1){
				int page_count = i_nextLabel - i_label;
				QStringList data = page_reader.d_getRows(i_label, page_count);
				page.comment_list.append(data.join("\n"));
				i_label = i_nextLabel;
			}else{
				QStringList data = page_reader.d_getRows(i_label);
				page.comment_list.append(data.join("\n"));
				break;
			}
		}
		else{
			break;
		}
	}

	this->page_list.append(page);
}

