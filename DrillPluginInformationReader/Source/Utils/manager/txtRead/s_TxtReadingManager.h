#pragma once

#include <QObject>

/*
-----==========================================================-----
		�ࣺ		log�ļ�������.h
		�汾��		v1.07
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		��ȡ/ת�� log�ļ������ݡ�
					��ר�Ŷ�һƪ�ı��������ٶȽ�����
					����ϸ��cpp��
-----==========================================================-----
*/

class S_TxtReadingManager : public QObject
{
	Q_OBJECT

	//-----------------------------------
	//----�����ṹ
	public:
		S_TxtReadingManager();
		~S_TxtReadingManager();
		static S_TxtReadingManager* cur_instance;		//����
		static S_TxtReadingManager* getInstance();		//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		
	//-----------------------------------
	//----����
	private:
		QString log_context_org;		//ԭlog
		QStringList log_context_list;	//log���ַ��������ģ�
	public:
										//���� - ��ʼ��
		void initLog();
										//���� - ��������
		void setLog(QString log);

	//-----------------------------------
	//----ȫ��
										//ȫ�� - ����ո�
		void trimAllRows();
										//ȫ�� - �滻�ַ�
		void replaceInStrings(QString re_str, QString str);
		void replaceInStrings(QRegExp re, QString str);
										//ȫ�� - �������
		void clearEmptyRows();
										//ȫ�� - ȥ��ע���У��������ַ���
		void clearComment(QString prefix);
										//ȫ�� - ��ȡȫ�У��ݲ�����ֱ�ӻ�ȡ��
		QStringList getAllRows();

	//-----------------------------------
	//----���޸�
										//���޸� - �����
		void appendRow(QString context);
										//���޸� - ��Ӷ���
		void appendRows(QStringList context);
										//���޸� - ������
		void insertRow(int index, QString context);
										//���޸� - �������
		void insertRows(int index, QStringList context);
										//���޸� - �滻��
		void replaceRow(int index, QString context);
										//���޸� - ȥ����
		void removeRow(int index);
										//���޸� - ȥ������
		void removeRows(QList<int> index_list);

	//-----------------------------------
	//----ֱ�Ӳ�����directly��
	private:
		QSet<int> m_used_rows;			//����������
	public:
										//ֱ�� - ��i��
		QString d_rowAt(int i);
										//ֱ�� - ��ȡȫ������
		int d_rowCount();
										//ֱ�� - ��ȡ������
										//		������1���������������ַ���
										//		�����ء�������ֵ��δ�ҵ�����-1��
		int d_indexOf(QString contains);
		int d_indexOf(QRegExp re_contains);
										//ֱ�� - ��ȡ�����У���ĩβ�ң�
										//		������1���������������ַ���
										//		�����ء�������ֵ��δ�ҵ�����-1��
		int d_lastIndexOf(QString contains);
		int d_lastIndexOf(QRegExp re_contains);
										//ֱ�� - ��ȡ�����У�ָ����Χ��
										//		������1����ʼ��
										//		������2����ֹ��
										//		�����ء�����ֵ��δ�ҵ�����-1��
		int d_indexOf(QString contains, int n, int m = -1);
		int d_indexOf(QRegExp re_contains, int n, int m = -1);
										//ֱ�� - ��ȡ�����е������У�������ǰindex�У�
										//		������1����ʼ��
										//		������2������
										//		�����ء����б�δ�ҵ�/��곬�������� ���ؿ��б�
		QStringList d_getRows(int n, int row_count = -1);
										//ֱ�� - ��ȡ������������
										//		������1�������������ַ���
										//		�����ء����а������У�δ�ҵ����ؿ��б�
		QList<int> d_getAllRowIndexsContains(QString contains);
		QList<int> d_getAllRowIndexsContains(QRegExp re_contains);
		QStringList d_getAllRowsContains(QString contains);
		QStringList d_getAllRowsContains(QRegExp re_contains);

										//ֱ�� - ��ȡ������������������
										//		�����ء����������У�����������޸ģ����±�Ҳ����ű䣩
		QList<int> d_getUsedIndexs();
										//ֱ�� - �����¼�Ĳ�����
		void d_clearUsedIndexs();
										//ֱ�� - ��ȡ������������δ����������
										//		������1������ģʽ����cpp������
										//		�����ء�δ�����������б�
		QStringList d_getUnusedRows(QString mode = "");
		
	//-----------------------------------
	//----����������orderly��
	private:
		int cur_pos;
	public:
										//˳����� - ��ʼ����
		//void o_start();
										//˳����� - �жϱ������
		//bool o_isAtEnd();

		//bool o_nextRow();
	public:
		
	//-----------------------------------
	//----�ַ���
	public:
										//�ַ��� - ��ȡ����������եȡ�� 1.0e3 �����������пո�ű���ȡ��
										//		������1�������ַ���
										//		�����ء����б�
		QList<double> s_getDoubleInRow(QString row);
										//�ַ��� - ��ȡ��������եȡ��
		QList<double> s_getDoubleForceInRow(QString row);
										//�ַ��� - ��ȡ��������եȡ�� 23 �����������пո�ű���ȡ��
										//		������1�������ַ���
										//		�����ء����б�
		QList<int> s_getIntInRow(QString row);
										//�ַ��� - ��ȡ������եȡ��
		QList<int> s_getIntForceInRow(QString row);

};

