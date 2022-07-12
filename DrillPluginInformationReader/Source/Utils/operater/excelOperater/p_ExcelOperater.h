#pragma once


// >> QAxWidget�ؼ�x32
#ifndef WIN64
#include <QAxWidget>
#include <QAxObject>

/*
-----==========================================================-----
		�ࣺ		Excel������.h
		�汾��		v1.01
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		����Excel���д�����ݡ�
					��ע�⣬�˲�����ֻ����32λ���������С�
					����ϸ��cpp��
-----==========================================================-----
*/
class P_ExcelOperater : public QObject
{
	Q_OBJECT

	public:
		P_ExcelOperater();
		~P_ExcelOperater();

	//-----------------------------------
	//-----���
	private:
		QAxObject* m_application;		//�������
		QAxObject* m_workBookTank;		//����������
		bool m_isSoftwareInited;		//����Ƿ��ʼ��
		bool m_isSoftwareOpened;		//����Ƿ��
	public:
										//��� - �����
		bool openSoftware();
										//��� - �ر����
		void closeSoftware();
										//��� - �Ƿ�ɹ���
		bool isOpened_Software();

	//-----------------------------------
	//-----������
	private:
		QString m_curPath;				//�ļ�·��
		QAxObject* m_curWorkBook;		//��ǰ������
		QAxObject* m_curSheetTank;		//����������
	public:
										//������ - �½�
										//		��˵�������½����Զ�ѡ��1�Ź�����
		void newExcelFile();
										//������ - ��
										//		��˵�������򿪺��Զ�ѡ��1�Ź�����
		void openExcelFile(QString file_path);
										//������ - ����
		bool saveExcelFile();
										//������ - ���Ϊ
		bool saveAsExcelFile(QString save_path);
										//������ - �Ƿ�ɹ���
		bool isOpened_ExcelFile();

	//-----------------------------------
	//-----������
	protected:
		QAxObject* m_curSheet;			//��ǰ������
	public:
										//������ - ѡ������
										//		��˵������������������� 1 ��ʼ������
		void selectSheet(int i);
										//������ - ���Ƶ�ǰ������
		void copyCurSheet();
										//������ - ����������
		int getSheetCount();
										//������ - �Ƿ�ɹ���
		bool isOpened_Sheet();
										//������ - ��ȡ��ǰ����������
		QString getSheetName();
										//������ - ���õ�ǰ����������
		void setSheetName(QString name);

	//-----------------------------------
	//-----����ֵ
	public:
										//����ֵ - ����ֵ
										//		��˵������start_pos��end_pos����"A1"��"B1"�����и�ʽ��
		void cell_SetValue(QString start_pos, QString end_pos, QString value);
										//����ֵ - ��ȡֵ
										//		��˵�����������Χ��һ����������һ��һ���ۼӻ�ȡ��
		QStringList cell_GetValue(QString start_pos, QString end_pos, QStringList value);

	//-----------------------------------
	//-----������Ԫ��
	public:
										//��Ԫ�� - ���� - ����
		void cell_FreezePanes_OnlyRow();
										//��Ԫ�� - ���� - ����
		void cell_FreezePanes_OnlyColumn();
										//��Ԫ�� - ���� - ���к�����
		void cell_FreezePanes_RowAndColumn();
										//��Ԫ�� - ���� - �ر�
		void cell_FreezePanes_None();

										//��Ԫ�� - ���ÿ��
		void cell_SetWidth(int col_pos, int width);
										//��Ԫ�� - ���ø߶�
		void cell_SetHeight(int row_pos, int height);
										//��Ԫ�� - �ϲ���Ԫ��
										//		��˵������start_pos��end_pos����"A1"��"B1"�����и�ʽ��
		void cell_MergeCells(QString start_pos, QString end_pos, bool enabled);
										//��Ԫ�� - �����Զ�����
		void cell_SetWrapText(QString start_pos, QString end_pos, bool enabled);

	//-----------------------------------
	//-----������ʽ
	public:
		enum XlBordersIndex{			//ö�ٶ������ԣ�https://docs.microsoft.com/zh-cn/dotnet/api/microsoft.office.interop.excel.xlbordersindex?view=excel-pia��
			xlDiagonalDown = 5,			//��Ԫ������Ͻ������½ǵı߿�
			xlDiagonalUp = 6,			//��Ԫ������½������Ͻǵı߿�
			xlEdgeBottom = 9,			//����ĵײ��߿�
			xlEdgeLeft = 7,				//�������߱߿�
			xlEdgeRight = 10,			//������ұ߱߿�
			xlEdgeTop = 8,				//����Ķ����߿�
			xlInsideHorizontal = 12,	//�����ڵ�ˮƽ�߿�
			xlInsideVertical = 11,		//�����ڵĴ�ֱ�߿�
		};
	public:
										//��ʽ - ���ñ���
										//		��˵������start_pos��end_pos����"A1"��"B1"�����и�ʽ��
		void cell_Style_SetBackground(QString start_pos, QString end_pos, QColor color);
		void cell_Style_SetBackground_Row(int row_pos, QColor color);
		void cell_Style_SetBackground_Column(int col_pos, QColor color);
										//��ʽ - ���ñ߿�ɫ
		void cell_Style_SetAllBorder(QString start_pos, QString end_pos, QColor color);
		void cell_Style_SetBorder(QString start_pos, QString end_pos, QColor color, P_ExcelOperater::XlBordersIndex index);
										//��ʽ - ������������
		void cell_Style_SetFontFamily(QString start_pos, QString end_pos, QString font_name);
		void cell_Style_SetFontFamily_Row(int row_pos, QString font_name);
		void cell_Style_SetFontFamily_Column(int col_pos, QString font_name);
										//��ʽ - ��������Ӵ�
		void cell_Style_SetFontBold(QString start_pos, QString end_pos, bool enabled);
		void cell_Style_SetFontBold_Row(int row_pos, bool enabled);
		void cell_Style_SetFontBold_Column(int col_pos, bool enabled);
										//��ʽ - ���������С
		void cell_Style_SetFontSize(QString start_pos, QString end_pos, int font_size);
		void cell_Style_SetFontSize_Row(int row_pos, int font_size);
		void cell_Style_SetFontSize_Column(int col_pos, int font_size);

};

#else
/*
-----==========================================================-----
	�ࣺ		�հ׵Ĳ�����
-----==========================================================-----
*/
class P_ExcelOperater : public QDialog{
	Q_OBJECT
	public:
		P_ExcelOperater();			//���캯��
		~P_ExcelOperater();			//��������
};
#endif // >> QAxWidget�ؼ�x32
