#include "stdafx.h"
#include "C_ScriptHelp_Src.h"


/*
-----==========================================================-----
		�ࣺ		��������-��Դ·�� ������.cpp
		����ģ�飺	���ģ��
		���ܣ�		������Ϣ�е����ݡ�
-----==========================================================-----
*/
C_ScriptHelp_Src::C_ScriptHelp_Src(){
	this->src_list = QStringList();				//��Դ·��
	this->context = QString();					//·��˵��
	this->example = QString();					//����˵��
}
C_ScriptHelp_Src::~C_ScriptHelp_Src(){
}

/*-------------------------------------------------
		���� - ��ȡ ��Դ·�� �ַ���
*/
void C_ScriptHelp_Src::readSrc(QStringList src_contextRows){

	// > ��Դ·�� ����
	int i_context = 0;
	for (int i = 0; i < 4; i++){
		QString row = src_contextRows.at(i);
		if (row.contains("��Դ·����")){
			QString data = row.replace("��Դ·����", "");
			data = data.mid(0, data.indexOf(QRegExp("[ \\(��\n]"))).trimmed();
			if (data.isEmpty() == false){
				this->src_list.append(data);
			}
			i_context += 1;
		}
		else{
			break;
		}
	}

	// > ����˵���ı� ����
	QString context = "";
	QString example = "";
	bool is_context = true;
	for (int i = i_context; i < src_contextRows.count(); i++){
		QString row = src_contextRows.at(i);
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
		if (i < src_contextRows.count() - 1){
			example.append("\n");
		}
	}
	this->context = context;
	this->example = example;
}
