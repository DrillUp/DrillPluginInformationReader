#ifndef P_ExcelDataGenerator_H
#define P_ExcelDataGenerator_H

#include <QObject>

/*
-----==========================================================-----
		�ࣺ		Excel���������.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�����Զ����Excel����ʽ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ExcelDataGenerator : public QObject
{
	Q_OBJECT

	public:
		P_ExcelDataGenerator(QObject *parent = 0);
		~P_ExcelDataGenerator();
		
	//-----------------------------------
	//----������
	public slots: 
								//������ - ���� ����嵥
		void generatePluginDataList(QString save_path);
								//������ - ���� ���ʾ��λ�ñ��˹��ܲ�������������ƿصģ�
		//void generateMapPosList(QString save_path);

};

#endif // P_ExcelDataGenerator_H
