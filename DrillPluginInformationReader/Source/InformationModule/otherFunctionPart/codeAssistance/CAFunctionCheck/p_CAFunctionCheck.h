#ifndef P_CAFunctionCheck_H
#define P_CAFunctionCheck_H

#include <QObject>

/*
-----==========================================================-----
		�ࣺ		����У����.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�����Զ����Excel����ʽ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_CAFunctionCheck : public QObject
{
	Q_OBJECT

	public:
		P_CAFunctionCheck(QObject *parent = 0);
		~P_CAFunctionCheck();
		
	//-----------------------------------
	//----������
	public slots: 
								//������ - ���� �����ı�
		QString generateFunctionCheckData();
								//������ - ���� ���в����д
		QString generateFunctionCheckData2();
								//������ - ���� �ظ�����ı�����
		QString generateFunctionCheckData3();

};

#endif // P_CAFunctionCheck_H
