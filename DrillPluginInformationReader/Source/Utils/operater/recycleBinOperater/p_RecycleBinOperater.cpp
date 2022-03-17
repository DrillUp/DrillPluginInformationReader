#include "stdafx.h"
#include "p_RecycleBinOperater.h"

/*
-----==========================================================-----
		�ࣺ		����վ������.cpp
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		��ȡ �ı��ļ��ľ������ݣ��ṩ��ݲ�����

		ʹ�÷�����
				> ��ʼ��
					P_MatrixReader reader = new P_MatrixReader();
					reader.initSetSkipRow(0);							//������
					reader.initSetSkipComment(QStringList()<<"#");		//ȥ��ע����
					reader.initSetSeparator(QRegExp("[, \t]+"));		//����ָ�����Ĭ�Ͽո��\t��
					this->m_matrix = reader.readMatrixByFile(QFileInfo(path));			//ִ�г�ʼ��
					if (this->m_matrix == nullptr){ return; }

-----==========================================================-----
*/
P_RecycleBinOperater::P_RecycleBinOperater(){
}
P_RecycleBinOperater::~P_RecycleBinOperater() {
}


/*-------------------------------------------------
		���� - �������վ
*/
bool P_RecycleBinOperater::moveToRecycleBin(QString file_path){
	QFileInfo fileinfo(file_path);
	if (fileinfo.exists() == false){
		return false;
	}
	WCHAR from[MAX_PATH];
	memset(from, 0, sizeof(from));
	int l = fileinfo.absoluteFilePath().toWCharArray(from);
	if (l < 0){ return false; }
	if (l >= MAX_PATH){ return false; }
	from[l] = '\0';
	SHFILEOPSTRUCT fileop;
	memset(&fileop, 0, sizeof(fileop));
	fileop.wFunc = FO_DELETE;
	fileop.pFrom = from;
	fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
	int rv = SHFileOperation(&fileop);
	if (0 != rv){
		qDebug() << rv << QString::number(rv).toInt(0, 8);
		return false;
	}
	return true;
}
