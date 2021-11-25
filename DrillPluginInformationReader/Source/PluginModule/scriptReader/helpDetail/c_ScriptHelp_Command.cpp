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
	this->context_note = QStringList();			//�����б�

	this->context_command = QString();					//ָ��ȫ��
	this->command_PluginCommand = QStringList();		//ָ�� - ���ָ��
	this->command_PluginCommand_old = QStringList();	//ָ�� - ���ָ��(��)
	this->command_EventComment = QStringList();			//ָ�� - �¼�ע��
	this->command_EventComment_old = QStringList();		//ָ�� - �¼�ע��(��)
	this->command_MapNote = QStringList();				//ָ�� - ��ͼ��ע
	this->command_ActorNote = QStringList();			//ָ�� - ��ɫע��
	this->command_EnemyNote = QStringList();			//ָ�� - ����ע��
	this->command_StateNote = QStringList();			//ָ�� - ״̬ע��
	this->command_ItemNote = QStringList();				//ָ�� - ��Ʒ/����/����ע��
	this->command_SkillNote = QStringList();			//ָ�� - ����ע��
	this->command_MoveRoute = QStringList();			//ָ�� - �ƶ�·��ָ��
	this->command_WindowChar = QStringList();			//ָ�� - �����ַ�
	this->command_Other = QStringList();				//ָ�� - ����
}
C_ScriptHelp_CommandGroup::~C_ScriptHelp_CommandGroup(){
}

/*-------------------------------------------------
		��ȡ�� - ���ָ��
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
	}else if (type_str == "��ͼ��ע"){
		this->command_MapNote.append(commend_str);
	}else if (type_str == "��ɫע��" || type_str == "��ɫ��ע"){
		this->command_ActorNote.append(commend_str);
	}else if (type_str == "����ע��" || type_str == "���˱�ע"){
		this->command_EnemyNote.append(commend_str);
	}else if (type_str == "״̬ע��"){
		this->command_StateNote.append(commend_str);
	}else if (type_str == "��Ʒע��" || type_str == "��Ʒ��ע" || 
			  type_str == "����ע��" || type_str == "���߱�ע" || 
			  type_str == "����ע��" || type_str == "������ע" || 
			  type_str == "����ע��" || type_str == "���ױ�ע" || 
			  type_str == "����ע��" || type_str == "���߱�ע" ){
		this->command_ItemNote.append(commend_str);
	}else if (type_str == "����ע��" || type_str == "���ܱ�ע"){
		this->command_SkillNote.append(commend_str);
	}else if (type_str == "�ƶ�·��ָ��" || type_str == "�ƶ�·�߽ű�"){
		this->command_MoveRoute.append(commend_str);
	}else if (type_str == "�����ַ�"){
		this->command_WindowChar.append(commend_str);
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
QStringList C_ScriptHelp_CommandGroup::getAllAvailableCommand(){
	return QStringList()
		<< this->command_PluginCommand
		<< this->command_PluginCommand_old
		<< this->command_EventComment
		<< this->command_EventComment_old
		<< this->command_MapNote
		<< this->command_ActorNote
		<< this->command_EnemyNote
		<< this->command_StateNote
		<< this->command_ItemNote
		<< this->command_SkillNote
		<< this->command_MoveRoute
		<< this->command_WindowChar;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ��
*/
QStringList C_ScriptHelp_CommandGroup::getAllCommand(){
	return this->getAllAvailableCommand() << this->command_Other;
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ���
*/
bool C_ScriptHelp_CommandGroup::hasCommandKeyWord(QString keyWord){
	QStringList data_list = this->getAllAvailableCommand();
	if (keyWord == ""){
		return data_list.count() > 0;
	}
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
/*-------------------------------------------------
		���� - ��ȡ����
*/
QString C_ScriptHelp_CommandGroup::getGroupFullName(){
	QString rusult = "";
	if (this->is_important){
		rusult = "��������";
	}else{
		rusult = "��ѡ�趨";
	}
	if (this->group_name != ""){
		rusult.append(" - ");
		rusult.append(this->group_name);
	}
	return rusult;
}

/*-------------------------------------------------
		���� - �������� - ��ȡȫ����ǩ
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_TagList(){
	QStringList data_list = this->context_command.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 0; i < data_list.count(); i++){
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << re.cap(0);
		}else{
			result_list << "";	//���������У�
		}
	}
	return result_list;
}
/*-------------------------------------------------
		���� - �������� - ��ȡȫ��ָ��
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_CommandList(){
	QStringList data_list = this->context_command.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 0; i < data_list.count(); i++){
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << data.mid(pos + re.cap(0).length());
		}else{
			result_list << data;	//����δ�ɹ���ȡ��ֱ����ʾȫ�����ݣ�
		}
	}
	return result_list;
}
/*-------------------------------------------------
		���� - �������� - ��ȡȫ����ǩ
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_OldTagList(){
	QStringList data_list = this->context_command_old.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 1; i < data_list.count(); i++){	//���ӵڶ��п�ʼ��ȡ��
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << re.cap(0);
		}else{
			result_list << "";	//���������У�
		}
	}
	return result_list;
}
/*-------------------------------------------------
		���� - �������� - ��ȡȫ��ָ��
*/
QStringList C_ScriptHelp_CommandGroup::getGrid_OldCommandList(){
	QStringList data_list = this->context_command_old.split("\n");
	QRegExp re = this->commandRe();
	QStringList result_list = QStringList();
	for (int i = 1; i < data_list.count(); i++){	//���ӵڶ��п�ʼ��ȡ��
		QString data = data_list.at(i);
		int pos = re.indexIn(data);
		if (pos != -1){
			result_list << data.mid(pos + re.cap(0).length());
		}else{
			result_list << data;	//����δ�ɹ���ȡ��ֱ����ʾȫ�����ݣ�
		}
	}
	return result_list;
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
		���� - ��ȡȫ��ָ�� - ���ָ��
*/
QStringList C_ScriptHelp_Command::getAllCommand_PluginCommand(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_PluginCommand);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ���ָ��(��)
*/
QStringList C_ScriptHelp_Command::getAllCommand_PluginCommandOld(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_PluginCommand_old);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - �¼�ע��
*/
QStringList C_ScriptHelp_Command::getAllCommand_EventComment(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_EventComment);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - �¼�ע��(��)
*/
QStringList C_ScriptHelp_Command::getAllCommand_EventCommentOld(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_EventComment_old);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ��ͼ��ע
*/
QStringList C_ScriptHelp_Command::getAllCommand_MapNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_MapNote);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ��ɫע��
*/
QStringList C_ScriptHelp_Command::getAllCommand_ActorNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_ActorNote);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ����ע��
*/
QStringList C_ScriptHelp_Command::getAllCommand_EnemyNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_EnemyNote);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ״̬ע��
*/
QStringList C_ScriptHelp_Command::getAllCommand_StateNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_StateNote);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ��Ʒ/����/����ע��
*/
QStringList C_ScriptHelp_Command::getAllCommand_ItemNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_ItemNote);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ����ע��
*/
QStringList C_ScriptHelp_Command::getAllCommand_SkillNote(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_SkillNote);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - �ƶ�·��ָ��
*/
QStringList C_ScriptHelp_Command::getAllCommand_MoveRoute(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_MoveRoute);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - �����ַ�
*/
QStringList C_ScriptHelp_Command::getAllCommand_WindowChar(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_WindowChar);
	}
	return result_list;
}
/*-------------------------------------------------
		���� - ��ȡȫ��ָ�� - ����
*/
QStringList C_ScriptHelp_Command::getAllCommand_Other(){
	QStringList result_list = QStringList();
	for (int i = 0; i < this->group_list.count(); i++){
		result_list.append(this->group_list.at(i).command_Other);
	}
	return result_list;
}

/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ���
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_All(QString keyWord){
	for (int i = 0; i < this->group_list.count(); i++){
		C_ScriptHelp_CommandGroup group = this->group_list.at(i);
		if (group.hasCommandKeyWord(keyWord) == true){
			return true;
		}
	}
	return false;
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ���ָ��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_PluginCommand(QString keyWord){
	QStringList data_list = this->getAllCommand_PluginCommand();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ���ָ��(��)
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_PluginCommandOld(QString keyWord){
	QStringList data_list = this->getAllCommand_PluginCommandOld();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - �¼�ע��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_EventComment(QString keyWord){
	QStringList data_list = this->getAllCommand_EventComment();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - �¼�ע��(��)
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_EventCommentOld(QString keyWord){
	QStringList data_list = this->getAllCommand_EventCommentOld();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ��ͼ��ע
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_MapNote(QString keyWord){
	QStringList data_list = this->getAllCommand_MapNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ��ɫע��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_ActorNote(QString keyWord){
	QStringList data_list = this->getAllCommand_ActorNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ����ע��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_EnemyNote(QString keyWord){
	QStringList data_list = this->getAllCommand_EnemyNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ״̬ע��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_StateNote(QString keyWord){
	QStringList data_list = this->getAllCommand_StateNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ��Ʒ/����/����ע��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_ItemNote(QString keyWord){
	QStringList data_list = this->getAllCommand_ItemNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ����ע��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_SkillNote(QString keyWord){
	QStringList data_list = this->getAllCommand_SkillNote();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - �ƶ�·��ָ��
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_MoveRoute(QString keyWord){
	QStringList data_list = this->getAllCommand_MoveRoute();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - �����ַ�
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_WindowChar(QString keyWord){
	QStringList data_list = this->getAllCommand_WindowChar();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		���� - ����ָ��ָ��ؼ��� - ����
*/
bool C_ScriptHelp_Command::hasCommandKeyWord_Other(QString keyWord){
	QStringList data_list = this->getAllCommand_Other();
	return this->searchCommandKeyWord(&data_list, keyWord);
}
/*-------------------------------------------------
		˽�� - �жϹؼ���
*/
bool C_ScriptHelp_Command::searchCommandKeyWord(QStringList* command_list, QString keyWord){

	// > ���������
	if (keyWord == ""){
		if (command_list->count() == 0){
			return false;
		}else{
			return true;
		}
	}

	// > �������
	for (int i = 0; i < command_list->count(); i++){
		QString data = command_list->at(i);
		if (data.contains(keyWord)){
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
	if (data_list.contains("��������") || data_list.contains("���ʽ") || data_list.contains("�����")){
		group.is_important = true;
	}else{
		group.is_important = false;
	}
	if (data_list.count() > 2){
		group.group_name = data_list.last();
	}

	//��ָ��������� 3x4 �� 2x2x2 ���ֵ������г����˼���Ե� ���ָ���Ҫ��ʾָ��֮�������У����任�ɺ��ߡ��� ��

	// > ָ���
	int i_command = group_reader.d_indexOf(group.commandRe());
	int i_command_end = group_reader.d_indexOf(QRegExp("^[\\d]+[\\.��]"), i_command + 1);
	int i_command_oldCommandEnd = group_reader.d_indexOf(this->getOldKeyword(), i_command_end);
	if (i_command != -1){
		int row_count = i_command_end - i_command;
		if (row_count < 0){ row_count = -1; }

		// > ָ��ȫ�ģ���ʾ��ϸ��Ϣ�ã�
		QStringList commandComment = group_reader.d_getRows(i_command, row_count);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment);
		group.context_command = commandComment.join("\n");

		// > ���β�����ָ������ã�
		for (int i = 0; i < commandComment.count(); i++){
			group.addOneRowCommand(commandComment.at(i));
		}
	}

	// > ˵���б�
	if (   i_command_end != -1
		&& i_command_end != i_command_oldCommandEnd){

		QStringList command_list = QStringList();
		QStringList commandComment = group_reader.d_getRows(i_command_end);
		if (i_command_oldCommandEnd != -1){
			commandComment = group_reader.d_getRows(i_command_end, i_command_oldCommandEnd-i_command_end);
		}
		if (commandComment.count() > 0 ){

			P_TxtFastReader commentReader = P_TxtFastReader(commandComment.join("\n"));
			int i_page = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."));	//���ҵ����ֵ��У�
			for (int k = 0; k < 15; k++){
				if (i_page != -1){
			
					// > ��������
					QStringList data_list = QStringList();
					int i_nextPage = commentReader.d_indexOf(QRegExp("^[ \\d]+\\."), i_page + 1);	//���ҵ�����½ں�addPage�������Ӻ����м���ϸ�֣�
					if (i_nextPage != -1){
						int page_count = i_nextPage - i_page;
						data_list = commentReader.d_getRows(i_page, page_count);
					}else{
						data_list = commentReader.d_getRows(i_page);
					}
			
					// > ��ӵ��б�
					if (data_list.count() > 0){
						QString data = data_list.join("\n");
						c_docs->addRelativeDocx(c_docs->findDocsNameList(data));	//������ĵ� - ����ĵ���
						command_list.append(data);
					}
			
					i_page = i_nextPage;
				}else{
					break;
				}
			}
		}
		group.context_note = command_list;
	}

	// > ��ָ��
	if (i_command_oldCommandEnd != -1){

		// > ָ��ȫ�ģ���ϸ��Ϣ�ã�
		QStringList commandComment_old = group_reader.d_getRows(i_command_oldCommandEnd);
		TTool::_QStringList_clearEmptyRows_OnlyBack_(&commandComment_old);
		group.context_command_old = commandComment_old.join("\n");

		// > ���β�����ָ������ã�
		for (int i = 0; i < commandComment_old.count(); i++){
			group.addOneRowCommand(commandComment_old.at(i));
		}
	}
	this->group_list.append(group);
}
/*-------------------------------------------------
		��ȡ�� - ��ȡĬ�Ϲؼ���
*/
QString C_ScriptHelp_Command::getOldKeyword(){
	return "�����Ǿɰ汾��ָ��";
}