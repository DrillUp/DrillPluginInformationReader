#pragma once


// >> QAxWidget控件x32
#ifndef WIN64
#include <QAxWidget>
#include <QAxObject>

/*
-----==========================================================-----
		类：		Excel操作器.h
		版本：		v1.01
		作者：		drill_up
		所属模块：	工具模块
		功能：		操作Excel表格，写入数据。
					【注意，此操作器只能在32位编译下运行】
					（详细见cpp）
-----==========================================================-----
*/
class P_ExcelOperater : public QObject
{
	Q_OBJECT

	public:
		P_ExcelOperater();
		~P_ExcelOperater();

	//-----------------------------------
	//-----软件
	private:
		QAxObject* m_application;		//软件对象
		QAxObject* m_workBookTank;		//工作簿容器
		bool m_isSoftwareInited;		//软件是否初始化
		bool m_isSoftwareOpened;		//软件是否打开
	public:
										//软件 - 打开软件
		bool openSoftware();
										//软件 - 关闭软件
		void closeSoftware();
										//软件 - 是否成功打开
		bool isOpened_Software();

	//-----------------------------------
	//-----工作簿
	private:
		QString m_curPath;				//文件路径
		QAxObject* m_curWorkBook;		//当前工作簿
		QAxObject* m_curSheetTank;		//工作表容器
	public:
										//工作簿 - 新建
										//		【说明】：新建后，自动选择1号工作表。
		void newExcelFile();
										//工作簿 - 打开
										//		【说明】：打开后，自动选择1号工作表。
		void openExcelFile(QString file_path);
										//工作簿 - 保存
		bool saveExcelFile();
										//工作簿 - 另存为
		bool saveAsExcelFile(QString save_path);
										//工作簿 - 是否成功打开
		bool isOpened_ExcelFile();

	//-----------------------------------
	//-----工作表
	protected:
		QAxObject* m_curSheet;			//当前工作表
	public:
										//工作表 - 选择工作表
										//		【说明】：工作表的索引从 1 开始计数。
		void selectSheet(int i);
										//工作表 - 复制当前工作表
		void copyCurSheet();
										//工作表 - 工作表数量
		int getSheetCount();
										//工作簿 - 是否成功打开
		bool isOpened_Sheet();
										//工作表 - 获取当前工作表名称
		QString getSheetName();
										//工作表 - 设置当前工作表名称
		void setSheetName(QString name);

	//-----------------------------------
	//-----操作值
	public:
										//操作值 - 设置值
										//		【说明】：start_pos与end_pos需填"A1"、"B1"的行列格式。
		void cell_SetValue(QString start_pos, QString end_pos, QString value);
										//操作值 - 获取值
										//		【说明】：如果范围是一个矩阵，则按照一行一行累加获取。
		QStringList cell_GetValue(QString start_pos, QString end_pos, QStringList value);

	//-----------------------------------
	//-----操作单元格
	public:
										//单元格 - 冻结 - 首行
		void cell_FreezePanes_OnlyRow();
										//单元格 - 冻结 - 首列
		void cell_FreezePanes_OnlyColumn();
										//单元格 - 冻结 - 首行和首列
		void cell_FreezePanes_RowAndColumn();
										//单元格 - 冻结 - 关闭
		void cell_FreezePanes_None();

										//单元格 - 设置宽度
		void cell_SetWidth(int col_pos, int width);
										//单元格 - 设置高度
		void cell_SetHeight(int row_pos, int height);
										//单元格 - 合并单元格
										//		【说明】：start_pos与end_pos需填"A1"、"B1"的行列格式。
		void cell_MergeCells(QString start_pos, QString end_pos, bool enabled);
										//单元格 - 设置自动换行
		void cell_SetWrapText(QString start_pos, QString end_pos, bool enabled);

	//-----------------------------------
	//-----操作样式
	public:
		enum XlBordersIndex{			//枚举定义来自（https://docs.microsoft.com/zh-cn/dotnet/api/microsoft.office.interop.excel.xlbordersindex?view=excel-pia）
			xlDiagonalDown = 5,			//单元格的左上角至右下角的边框
			xlDiagonalUp = 6,			//单元格的左下角至右上角的边框
			xlEdgeBottom = 9,			//区域的底部边框
			xlEdgeLeft = 7,				//区域的左边边框
			xlEdgeRight = 10,			//区域的右边边框
			xlEdgeTop = 8,				//区域的顶部边框
			xlInsideHorizontal = 12,	//区域内的水平边框
			xlInsideVertical = 11,		//区域内的垂直边框
		};
	public:
										//样式 - 设置背景
										//		【说明】：start_pos与end_pos需填"A1"、"B1"的行列格式。
		void cell_Style_SetBackground(QString start_pos, QString end_pos, QColor color);
		void cell_Style_SetBackground_Row(int row_pos, QColor color);
		void cell_Style_SetBackground_Column(int col_pos, QColor color);
										//样式 - 设置边框色
		void cell_Style_SetAllBorder(QString start_pos, QString end_pos, QColor color);
		void cell_Style_SetBorder(QString start_pos, QString end_pos, QColor color, P_ExcelOperater::XlBordersIndex index);
										//样式 - 设置字体名称
		void cell_Style_SetFontFamily(QString start_pos, QString end_pos, QString font_name);
		void cell_Style_SetFontFamily_Row(int row_pos, QString font_name);
		void cell_Style_SetFontFamily_Column(int col_pos, QString font_name);
										//样式 - 设置字体加粗
		void cell_Style_SetFontBold(QString start_pos, QString end_pos, bool enabled);
		void cell_Style_SetFontBold_Row(int row_pos, bool enabled);
		void cell_Style_SetFontBold_Column(int col_pos, bool enabled);
										//样式 - 设置字体大小
		void cell_Style_SetFontSize(QString start_pos, QString end_pos, int font_size);
		void cell_Style_SetFontSize_Row(int row_pos, int font_size);
		void cell_Style_SetFontSize_Column(int col_pos, int font_size);

};

#else
/*
-----==========================================================-----
	类：		空白的操作器
-----==========================================================-----
*/
class P_ExcelOperater : public QDialog{
	Q_OBJECT
	public:
		P_ExcelOperater();			//构造函数
		~P_ExcelOperater();			//析构函数
};
#endif // >> QAxWidget控件x32
