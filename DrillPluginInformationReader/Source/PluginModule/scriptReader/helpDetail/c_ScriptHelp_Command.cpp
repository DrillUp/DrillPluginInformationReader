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
	this->group_name = "";						//������
	this->is_important = false;					//�Ƿ�Ϊ��������
	this->note_context = QStringList();			//�����б�

	this->command_context = QString();					//ָ��ȫ��
	this->command_PluginCommand = QStringList();		//ָ�� - ���ָ��
	this->command_PluginCommand_old = QStringList();	//ָ�� - ���ָ��(��)
	this->command_EventComment = QStringList();			//ָ�� - �¼�ע��
	this->command_EventComment_old = QStringList();		//ָ�� - �¼�ע��(��)
	this->command_EventNote = QStringList();			//ָ�� - �¼���ע
	this->command_MapNote = QStringList();				//ָ�� - ��ͼ��ע
	this->command_ActorNote = QStringList();			//ָ�� - ��ɫע��
	this->command_EnemyNote = QStringList();			//ָ�� - ����ע��
	this->command_Other = QStringList();				//ָ�� - ����
}
C_ScriptHelp_CommandGroup::~C_ScriptHelp_CommandGroup(){
}

/*-------------------------------------------------
		���� - ���ָ��
*/
void C_ScriptHelp_CommandGroup::addOneRowCommand(QString command_row){
	if (command_row.isEmpty()){ return; }
	if (command_row.contains(this->commandRe()) == false){ return; }

	int index = command_row.indexOf(QRegExp("[:��]"));
	QString type_str = command_row.mid(0, index);
	QString commend_str = command_row.mid(index + 1);
	if (type_str == "���ָ��"){
		this->command_PluginCommand.append(commend_str);
	}else if (type_str == "�¼�ע��"){
		this->command_EventComment.append(commend_str);
	}else if (type_str == "�¼���ע"){
		this->command_EventNote.append(commend_str);
	}else if (type_str == "��ͼ��ע"){
		this->command_MapNote.append(commend_str);
	}else if (type_str == "��ɫע��" || type_str == "��ɫ��ע"){
		this->command_ActorNote.append(commend_str);
	}else if (type_str == "����ע��" || type_str == "���˱�ע"){
		this->command_EnemyNote.append(commend_str);
	}else if (type_str == "���ָ��(��)" || type_str == "���ָ��ɣ�"){
		this->command_PluginCommand_old.append(commend_str);
	}else if (type_str == "�¼�ע��(��)" || type_str == "�¼�ע�ͣ��ɣ�"){
		this->command_EventComment_old.append(commend_str);
	}else{
		this->command_Other.append(commend_str);
	}
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ��
*/
QStringList C_ScriptHelp_CommandGroup::getAllCommand(){
	return QStringList()
		<< this->command_PluginCommand
		<< this->command_PluginCommand_old
		<< this->command_EventComment
		<< this->command_EventComment_old
		<< this->command_EventNote
		<< this->command_MapNote
		<< this->command_ActorNote
		<< this->command_EnemyNote
		<< this->command_Other;
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ���
*/
bool C_ScriptHelp_CommandGroup::hasCommandKeyWord(QString keyWord){
	QStringList data_list = this->getAllCommand();
	for (int j = 0; j < data_list.count(); j++){
		QString data = data_list.at(j);
		if (data.contains(keyWord)){
			return true;
		}
	}
	return false;
}
/*-------------------------------------------------
		���� - ָ����������
*/
QRegExp C_ScriptHelp_CommandGroup::commandRe(){
	return QRegExp("^[^ ]{4,7}[:��]");		//������4��7���������Һ�ð�ŵģ�����һ��ָ���У����� "���ָ��(��)��" ��
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
		���� - ָ��б�
*/
QList<C_ScriptHelp_CommandGroup> C_ScriptHelp_Command::getGroupList(){
	return this->group_list;
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ���
*/
bool C_ScriptHelp_Command::hasCommandKeyWord(QString keyWord){
	if (keyWord.isEmpty()){ return false; }

	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_CommandGroup group = this->group_list.at(i);
		if (group.hasCommandKeyWord(keyWord) == true){
			return true;
		}
	}
	return false;
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
	int i_command = group_reader.d_indexOf(group.commandRe());
	int i_command_end = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"), i_command + 1);
	if (i_command != -1){
		int row_count = i_command_end - i_command;
		if (row_count < 0){ row_count = -1; }
		QStringList commandComment = group_reader.d_getRows(i_command, row_count);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.command_context = commandComment.join("\n");

		for (int i = 0; i < commandComment.count(); i++){
			group.addOneRowCommand(commandComment.at(i));
		}
	}

	// > ˵���б�
	if (i_command_end != -1){
		QStringList commandComment = group_reader.d_getRows(i_command_end);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.note_context = commandComment;
	}
}