#pragma once
#include <QList>
#include "private/c_DesignTip_Cell.h"

/*
-----==========================================================-----
		�ࣺ		���������-�����м��� ������.h
		����ģ�飺	���ģ��
		���ܣ�		������������õ������ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/
class C_DesignTipGenerator{

	public:
		C_DesignTipGenerator();
		~C_DesignTipGenerator();

	//-----------------------------------
	//----����
	protected:
		QList<C_DesignTip_Cell> tip_list;	//�����м���
	public:
								//���� - ���ϳ�ʼ��
		void initData();
	public:
								//���� - ��ȡ����
		C_DesignTip_Cell getCellByIndex(int index);
								//���� - ��ȡ����
		int count();
								//���� - �ж��Ƿ��Ѻ�ĳ���ݣ���ֹ����������������ظ���
		bool hasContext(QString context);
								//���� - ���ж�
		bool isNull();

};
