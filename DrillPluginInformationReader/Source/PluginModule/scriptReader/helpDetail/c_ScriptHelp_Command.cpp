#include "stdafx.h"
#include "c_ScriptHelp_Command.h"

#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		��������-ָ�� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_CommandGroup::C_ScriptHelp_CommandGroup(){
	this->group_name = "";					//������
	this->is_important = false;				//�Ƿ�Ϊ��������
	this->context = QStringList();			//�����б�
}
C_ScriptHelp_CommandGroup::~C_ScriptHelp_CommandGroup(){
}


/*
-----==========================================================-----
		�ࣺ		��������-ָ�� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Command::C_ScriptHelp_Command(){
	this->group_list = QList<C_ScriptHelp_CommandGroup>();
}
C_ScriptHelp_Command::~C_ScriptHelp_Command(){
}
/*-------------------------------------------------
		���� - ���ж�
*/
bool C_ScriptHelp_Command::isNull(){
	return this->group_list.count() == 0;
}
/*-------------------------------------------------
		��ȡ�� - ��ȡ�µ�ָ��ַ���
*/
void C_ScriptHelp_Command::readNextGroup(QString group_context, C_ScriptHelp_Docs* c_docs){
	if (group_context == ""){ return; }
	C_ScriptHelp_CommandGroup group;
	P_TxtFastReader group_reader = P_TxtFastReader(group_context);

	// > ���Ⲷ��
	QString title = group_reader.d_getRows(0, 1).at(0);
	QStringList data_list = title.split(QRegExp("[ -]+"));
	TTool::_QStringList_clearEmptyRows_(&data_list);
	if (data_list.contains("��������")){
		group.is_important = true;
	}else{
		group.is_important = false;
	}
	if (data_list.count() > 1){
		group.group_name = data_list.last();
	}

	//��ָ��������� 3x4 �� 2x2x2 ���ֵ������г����˼���Ե� ���ָ���Ҫ��ʾָ��֮�������У����任�ɺ��ߡ��� ��

	// > ָ���
	//...

}