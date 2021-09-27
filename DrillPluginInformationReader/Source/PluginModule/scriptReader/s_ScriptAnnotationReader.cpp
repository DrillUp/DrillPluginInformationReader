#include "stdafx.h"
#include "s_ScriptAnnotationReader.h"

#include "helpDetail/c_ScriptHelpDetail.h"
#include "scriptDictionary/c_ScriptDictionary.h"
#include "Source/Utils/manager/txtRead/p_TxtFastReader.h"

/*
-----==========================================================-----
		�ࣺ		���ע���ȡ��.cpp
		����ģ�飺	���ģ��
		���ܣ�		��ȡjs�ļ��ڵ��������� @��ע�� ���ݡ�

		ʹ�÷�����
				>��ʼ����
				
-----==========================================================-----
*/

S_ScriptAnnotationReader::S_ScriptAnnotationReader(){
}
S_ScriptAnnotationReader::~S_ScriptAnnotationReader() {
}

/* --------------------------------------------------------------
----------PluginFrameManager ����
*/
S_ScriptAnnotationReader* S_ScriptAnnotationReader::cur_manager = NULL;
S_ScriptAnnotationReader* S_ScriptAnnotationReader::getInstance() {
	if (cur_manager == NULL) {
		cur_manager = new S_ScriptAnnotationReader();
	}
	return cur_manager;
}


/*-------------------------------------------------
		��ȡ - �����������Ҫ��
*/
C_ScriptAnnotation S_ScriptAnnotationReader::readPlugin_simple(QString file_fullPath) {
	C_ScriptAnnotation c_ScriptFrame = C_ScriptAnnotation();

	// > ��ȡ�����ļ�
	QFile plugin_file(file_fullPath);
	if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "����", "�޷����ļ���" + file_fullPath, QMessageBox::Yes);
		return c_ScriptFrame;
	}
	QString plugin_context = plugin_file.readAll();
	plugin_file.close();

	// > ��ȡ������Ϣ
	P_TxtFastReader reader = P_TxtFastReader(plugin_context);
	reader.prepare_trimAllRows();									// ȥ���ո�
	reader.prepare_replaceInStrings(QRegExp("^\\*[ ]?"), "");		// ȥ��ע�͵�ǰ׺����


	// > ��ȡ �����
	QString name = QFileInfo(file_fullPath).completeBaseName();
	c_ScriptFrame.setName(name);

	// > ��һƪע��
	int i_comment_start = reader.d_indexOf("/*:");
	int i_comment_end = reader.d_indexOf("*/", i_comment_start);
	if (i_comment_start != -1) {

		// > ��ȡ ����
		int i_plugindesc = reader.d_indexOf("@plugindesc", i_comment_start);
		if (i_plugindesc != -1 && i_plugindesc <= i_comment_end) {
			QString s_rows = reader.d_getRows(i_plugindesc,2).join(" ");
			QStringList list_plugindesc = s_rows.split("@");
			if (list_plugindesc.size() >= 2) {
				QString s = list_plugindesc.at(1);
				QString plugindesc = s.replace("plugindesc", "").trimmed();
				c_ScriptFrame.setPlugindesc(plugindesc);
			}
		}

		// > ��ȡ ����
		int i_author = reader.d_indexOf("@author", i_comment_start);
		if (i_author != -1 && i_author <= i_comment_end) {
			QStringList list_author = reader.d_rowAt(i_author).split("@author");
			if (list_author.size() >= 2) {
				QString author = list_author.at(1).trimmed();
				c_ScriptFrame.setAuthor(author);
			}
		}

		// > ��ȡ ������Ϣ
		int i_help = reader.d_indexOf("@help", i_comment_start, i_comment_end);
		if (i_help != -1 && i_help <= i_comment_end) {
			QStringList list_help = reader.d_getRows(i_help, i_comment_end - i_help).join("\n").split("@help");	// ��@help��ʼ��ע�ͽ�������"@"
			if (list_help.size() >= 2) {
				QString help_text = list_help.at(1);
				help_text = help_text.replace("@help", "");
				int index = help_text.indexOf("@");
				help_text = help_text.mid(0, index);
				help_text = help_text.trimmed();	// ȥ����ͷ�Ľ�β��"\n"�Ϳո�
				C_ScriptHelpDetail* helpDetail = this->readScriptHelpDetail(help_text);
				c_ScriptFrame.setScriptHelpDetail(helpDetail);
			}
		}
	}
	return c_ScriptFrame;
}
/*-------------------------------------------------
		��ȡ - ���������������
*/
C_ScriptAnnotation S_ScriptAnnotationReader::readPlugin_complete(QString file_fullPath) {
	C_ScriptAnnotation c_ScriptFrame = this->readPlugin_simple(file_fullPath);

	// > ��ȡ�����ļ�
	QFile plugin_file(file_fullPath);
	if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(nullptr, "����", "�޷����ļ���" + file_fullPath, QMessageBox::Yes);
		return c_ScriptFrame;
	}
	QString plugin_context = plugin_file.readAll();
	plugin_file.close();

	C_ScriptDictionary* dictionary = this->readScriptDictionary(plugin_context);
	c_ScriptFrame.setScriptDictionary(dictionary);

	return c_ScriptFrame;
}


/*-------------------------------------------------
		˽�� - ����������Ϣ ��ȡ�� ����
*/
C_ScriptHelpDetail* S_ScriptAnnotationReader::readScriptHelpDetail(QString help_context){
	C_ScriptHelpDetail* helpDetail = new C_ScriptHelpDetail();

	helpDetail->help = help_context;

	return helpDetail;
}

/*-------------------------------------------------
		˽�� - ���������Ϣ ��ȡ�� ����
*/
C_ScriptDictionary* S_ScriptAnnotationReader::readScriptDictionary(QString plugin_context){
	C_ScriptDictionary* dictionary = new C_ScriptDictionary();

	// > ��ȡ������Ϣ
	P_TxtFastReader reader = P_TxtFastReader(plugin_context);
	reader.prepare_trimAllRows();									// ȥ���ո�
	reader.prepare_replaceInStrings(QRegExp("^\\*[ ]?"), "");		// ȥ��ע�͵�ǰ׺����

	// > ��һƪע��
	int i_comment_start = reader.d_indexOf("/*:");
	int i_comment_end = reader.d_indexOf("*/", i_comment_start);
	if (i_comment_start != -1) {

		// > ��ȡ ����
		int i_param = reader.d_indexOf("@param", i_comment_start, i_comment_end);
		//..

	}

	// > �ṹ��
	int i_comment_struct = reader.d_indexOf(QRegExp("/\\*~struct~[\\S]+:"));
	//...

	return dictionary;
}