#pragma once

#include <QObject>
#include <QFileInfo>

/*
-----==========================================================-----
		�ࣺ		����վ������.h
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		��ȡ �ı��ļ��ľ������ݣ��ṩ��ݲ�����
					����ϸ��cpp��
-----==========================================================-----
*/
class P_RecycleBinOperater{

	public:
		P_RecycleBinOperater();
		~P_RecycleBinOperater();
		
	//-----------------------------------
	//----����
	public:
										//���� - �������վ
										//		��˵�������������ʧ���򷵻�false��
		static bool moveToRecycleBin(QString file_path);
		
};

