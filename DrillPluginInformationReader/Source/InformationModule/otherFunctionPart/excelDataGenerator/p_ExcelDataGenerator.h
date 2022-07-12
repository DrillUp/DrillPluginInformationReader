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
class P_ExcelOperater;
class P_ExcelDataGenerator : public QObject
{
	Q_OBJECT

	public:
		P_ExcelDataGenerator(QObject *parent = 0);
		~P_ExcelDataGenerator();
		
	//-----------------------------------
	//----������
	public:
		int cur_row;
		P_ExcelOperater* cur_operater;
	public slots: 
								//������ - ���� ����嵥
		void generatePluginDataList(QString save_path);
								//������ - ���� ���ܲ���ͳ�Ʊ�
		void generatePerformanceDataList(QString save_path);
								//������ - ���� ���ʾ��λ�ñ��˹��ܲ�������������ƿصģ�
		//void generateMapPosList(QString save_path);
	
	private:
								//�׶� - ���� ���ܲ���˵������
		void generatePerformanceNotes();
								//�׶� - ���� ������������
		void generatePerformanceSceneData(QString scene_name);
	private:
								//��ɫ - ��ɫ
		QColor getColor_grey();
								//��ɫ - ��ɫ�����ݳ̶ȣ�
		QColor getColor_ByCritical(int critical);
								//��ɫ - ��ɫ������ֵ��
		QColor getColor_ByCriticalValue(double critical_value);

};

#endif // P_ExcelDataGenerator_H
