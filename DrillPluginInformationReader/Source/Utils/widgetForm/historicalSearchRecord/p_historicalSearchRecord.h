#ifndef P_HistoricalSearchRecord_H
#define P_HistoricalSearchRecord_H

#include <QtWidgets/QDialog>
#include "ui_P_HistoricalSearchRecord.h"

/*
-----==========================================================-----
		�ࣺ		��ʷ������¼.h
		�汾��		v1.01
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		��ʾ ��ʷ������¼ �õĿؼ���
					����ϸ��cpp��
-----==========================================================-----
*/

class P_HistoricalSearchRecord : public QWidget
{
	Q_OBJECT

	public:
		P_HistoricalSearchRecord(QWidget *parent = 0);		//���캯��
		~P_HistoricalSearchRecord();						//��������
		
	//-----------------------------------
	//----��������
	protected:
		int m_lengthLimit;				//��¼��������
		QStringList m_textList;			//��¼����
	public:
										//�������� - ����¼�¼
		void addText(QString text);
										//�������� - ȥ����¼
		void removeText(QString text);
		
	//-----------------------------------
	//----�ؼ�
	protected:
		QList<QWidget*> m_layerList;
	public slots:
										//�ؼ� - �ؽ���ť��
		void rebuildUI();
										//�ؼ� - ȡ��ȫ����ť��
		void takeAllLayer();
	signals:
										//�ź� - ĳ��ť�����
		void textClicked(QString text);

	protected slots:
										//�ؼ� - ��ȡ��ť��(�����ı�)
		QWidget* getLayerByText(QString text);
										//�ؼ� - ������ť��
		QWidget* createLayer(QString text);
										//�ؼ� - ָ�� �ı���ť �����
		void searchBtn_action();
										//�ؼ� - ָ�� ȡ����ť �����
		void cancelBtn_action();

	//-----------------------------------
	//----��
	public:
										//�� - �������ݣ��޸ģ�
		void setData(QStringList data);
										//�� - ȡ������
		QStringList getData();
	private:
		Ui::P_HistoricalSearchRecord ui;
		
};

#endif // P_HistoricalSearchRecord_H
