#include "stdafx.h"
#include "P_ExcelOperater.h"

// >> QAxWidget控件x32
#ifndef WIN64

/*
-----==========================================================-----
		类：		Excel操作器.cpp
		版本：		v1.00
		作者：		drill_up
		所属模块：	工具模块
		功能：		操作Excel表格，写入数据。
					【注意，此操作器只能在32位编译下运行】

		使用方法：
				>初始化

-----==========================================================-----
*/
P_ExcelOperater::P_ExcelOperater(){
	
	this->m_application = new QAxObject();		//软件对象
	this->m_workBookTank = nullptr;				//工作簿容器
	this->m_isSoftwareInited = false;			//软件是否初始化
	this->m_isSoftwareOpened = false;			//软件是否打开

	this->m_curPath = "";						//文件路径
	this->m_curWorkBook = nullptr;				//当前工作簿
	this->m_curSheetTank = nullptr;				//工作表容器

	this->m_curSheet = nullptr;					//当前工作表
}
P_ExcelOperater::~P_ExcelOperater(){
	delete this->m_curSheet;
	this->m_curSheet = nullptr;
	delete this->m_curSheetTank;
	this->m_curSheetTank = nullptr;
	delete this->m_curWorkBook;
	this->m_curWorkBook = nullptr;
	delete this->m_workBookTank;
	this->m_workBookTank = nullptr;
	delete this->m_application;
	this->m_application = nullptr;
}


/*-------------------------------------------------
		软件 - 打开软件
*/
bool P_ExcelOperater::openSoftware(){
	if (this->m_isSoftwareInited == true){ return this->m_isSoftwareOpened; }
	this->m_isSoftwareInited = true;

	// > 打开软件
	bool success = this->m_application->setControl("Excel.Application");
	if ( success == false){
		QMessageBox::about(nullptr, "错误", "无法打开Excel软件。");
		this->m_isSoftwareOpened = false;
		return false;
	}
	// > 窗口可见
	this->m_application->setProperty("Visible", true);
	// > 警告显示
	this->m_application->setProperty("DisplayAlerts", true);
	// > 显示sheet变化内容
	this->m_application->setProperty("ScreenUpdating", true);

	// > 工作簿容器
	this->m_workBookTank = this->m_application->querySubObject("WorkBooks");
	if (this->m_workBookTank == nullptr){
		QMessageBox::about(nullptr, "错误", "无法打开WorkBooks工作簿容器。");
		this->m_isSoftwareOpened = false;
		return false;
	}
	this->m_isSoftwareOpened = true;
	return true;
}
/*-------------------------------------------------
		软件 - 关闭软件
*/
void P_ExcelOperater::closeSoftware(){
	this->m_application->dynamicCall("Quit()");
	this->m_isSoftwareInited = false;
	this->m_curPath = "";
	delete this->m_curSheet;
	this->m_curSheet = nullptr;
	delete this->m_curSheetTank;
	this->m_curSheetTank = nullptr;
	delete this->m_curWorkBook;
	this->m_curWorkBook = nullptr;
}
/*-------------------------------------------------
		软件 - 是否成功打开
*/
bool P_ExcelOperater::isOpened_Software(){
	return this->m_isSoftwareOpened;
}


/*-------------------------------------------------
		工作簿 - 新建
*/
void P_ExcelOperater::newExcelFile(){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return; }
	
	// > 新建
	this->m_workBookTank->dynamicCall("Add");
	
	// > 打开当前工作簿
	this->m_curWorkBook = this->m_application->querySubObject("ActiveWorkBook");
	if (this->m_curWorkBook == nullptr){
		QMessageBox::about(nullptr, "错误", "无法打开当前工作簿。");
		return;
	}

	// > 打开工作表容器
	this->m_curSheetTank = this->m_curWorkBook->querySubObject("Sheets");
	if (this->m_curSheetTank == nullptr){
		QMessageBox::about(nullptr, "错误", "无法打开Sheets工作表容器。");
		return;
	}
	
	// > 选择1号工作表
	this->selectSheet(1);
}
/*-------------------------------------------------
		工作簿 - 打开
*/
void P_ExcelOperater::openExcelFile(QString file_path){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return; }
	
	// > 打开路径
	this->m_workBookTank->dynamicCall("Open(QString)", QDir::toNativeSeparators(file_path), QString(), false);
	
	// > 打开当前工作簿
	this->m_curWorkBook = this->m_application->querySubObject("ActiveWorkBook");
	if (this->m_curWorkBook == nullptr){
		QMessageBox::about(nullptr, "错误", "无法打开当前工作簿。");
		return;
	}
	this->m_curPath = file_path;

	// > 打开工作表容器
	this->m_curSheetTank = this->m_curWorkBook->querySubObject("Sheets");
	if (this->m_curSheetTank == nullptr){
		QMessageBox::about(nullptr, "错误", "无法打开Sheets工作表容器。");
		return;
	}

	// > 选择1号工作表
	this->selectSheet(1);
}
/*-------------------------------------------------
		工作簿 - 保存
*/
bool P_ExcelOperater::saveExcelFile(){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return false; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return false; }
	if (this->m_curPath == ""){ Q_ASSERT(false); return false; }
	this->m_curWorkBook->dynamicCall("Save()");
	return true;
}
/*-------------------------------------------------
		工作簿 - 另存为
*/
bool P_ExcelOperater::saveAsExcelFile(QString file_path){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return false; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return false; }
	this->m_curWorkBook->dynamicCall("SaveAs(QString)", QDir::toNativeSeparators(file_path));
	return true;
}
/*-------------------------------------------------
		工作簿 - 是否成功打开
*/
bool P_ExcelOperater::isOpened_ExcelFile(){
	return this->m_curWorkBook != nullptr;
}



/*-------------------------------------------------
		工作表 - 选择工作表
*/
void P_ExcelOperater::selectSheet(int i){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return; }
	if (this->m_curSheetTank == nullptr){ Q_ASSERT(false); return; }
	this->m_curSheet = this->m_curSheetTank->querySubObject("Item(int)", i);
}
/*-------------------------------------------------
		工作表 - 复制工作表
*/
void P_ExcelOperater::copyCurSheet(){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QVariant sheetObj = this->m_curSheet->asVariant();
	this->m_curSheet->dynamicCall("Copy(QVariant)", sheetObj);
}
/*-------------------------------------------------
		工作表 - 工作表数量
*/
int P_ExcelOperater::getSheetCount(){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return 0; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return 0; }
	if (this->m_curSheetTank == nullptr){ Q_ASSERT(false); return 0; }
	return this->m_curSheetTank->property("Count").toInt();
}
/*-------------------------------------------------
		工作表 - 是否成功打开
*/
bool P_ExcelOperater::isOpened_Sheet(){
	return this->m_curSheet != nullptr;
}


/*-------------------------------------------------
		操作值 - 设置值
*/
void P_ExcelOperater::cell_SetValue(QString start_pos, QString end_pos, QString value){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	temp_range->setProperty("Value", value);
	delete temp_range;
}
/*-------------------------------------------------
		操作值 - 获取值
*/
QStringList P_ExcelOperater::cell_GetValue(QString start_pos, QString end_pos, QStringList value){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return QStringList(); }
	QAxObject *temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	QVariant var_matrix = temp_range->dynamicCall("Value");
	QVariantList var_rowList = var_matrix.toList();
	if (var_rowList.isEmpty()){ return QStringList(); }
	QStringList result_list;
	for (int i = 0; i < var_rowList.size(); i++){
		QVariantList var_row = var_rowList[i].toList();
		for (int j = 0; j < var_row.size(); j++){
			QString data = var_row[i].toString();
			result_list.push_back(data);
		}
	}
	delete temp_range;
	return result_list;
}

/*-------------------------------------------------
		单元格 - 冻结首行
*/
void P_ExcelOperater::cell_FreezePanes_OnlyRow(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "错误", "操作失败(冻结首行)。");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	temp_activeWindow->setProperty("SplitColumn", 0);
	temp_activeWindow->setProperty("SplitRow", 1);
	temp_activeWindow->setProperty("FreezePanes", true);
	delete temp_activeWindow;
}
/*-------------------------------------------------
		单元格 - 冻结首列
*/
void P_ExcelOperater::cell_FreezePanes_OnlyColumn(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "错误", "操作失败(冻结首列)。");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	temp_activeWindow->setProperty("SplitColumn", 1);
	temp_activeWindow->setProperty("SplitRow", 0);
	temp_activeWindow->setProperty("FreezePanes", true);
	delete temp_activeWindow;
}
/*-------------------------------------------------
		单元格 - 冻结首行和首列
*/
void P_ExcelOperater::cell_FreezePanes_RowAndColumn(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "错误", "操作失败(冻结首行和首列)。");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	temp_activeWindow->setProperty("SplitColumn", 1);
	temp_activeWindow->setProperty("SplitRow", 1);
	temp_activeWindow->setProperty("FreezePanes", true);
	delete temp_activeWindow;
}
/*-------------------------------------------------
		单元格 - 冻结关闭
*/
void P_ExcelOperater::cell_FreezePanes_None(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "错误", "操作失败(关闭冻结)。");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	delete temp_activeWindow;
}

/*-------------------------------------------------
		单元格 - 设置宽度
*/
void P_ExcelOperater::cell_SetWidth(int col_pos, int width){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_col = this->m_curSheet->querySubObject("Columns(int)", col_pos);
	temp_col->setProperty("ColumnWidth", width);
	delete temp_col;
}
/*-------------------------------------------------
		单元格 - 设置高度
*/
void P_ExcelOperater::cell_SetHeight(int row_pos, int height){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_row = this->m_curSheet->querySubObject("Rows(int)", row_pos);
	temp_row->setProperty("RowHeight", height);
	delete temp_row;
}
/*-------------------------------------------------
		单元格 - 合并单元格
*/
void P_ExcelOperater::cell_MergeCells(QString start_pos, QString end_pos, bool enabled){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	temp_range->setProperty("MergeCells", enabled);
	delete temp_range;
}
/*-------------------------------------------------
		单元格 - 设置自动换行
*/
void P_ExcelOperater::cell_SetWrapText(QString start_pos, QString end_pos, bool enabled){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	temp_range->setProperty("WrapText", enabled);
	delete temp_range;
}


/*-------------------------------------------------
		样式 - 设置背景
*/
void P_ExcelOperater::cell_Style_SetBackground(QString start_pos, QString end_pos, QColor color){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject* temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	QAxObject* temp_interior = temp_range->querySubObject("Interior");
	temp_interior->setProperty("Color", color);
	delete temp_interior;
	delete temp_range;
}
void P_ExcelOperater::cell_Style_SetBackground_Row(int row_pos, QColor color){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_row = this->m_curSheet->querySubObject("Rows(int)", row_pos);
	QAxObject* temp_interior = temp_row->querySubObject("Interior");
	temp_interior->setProperty("Color", color);
	delete temp_interior;
	delete temp_row;
}
void P_ExcelOperater::cell_Style_SetBackground_Column(int col_pos, QColor color){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_col = this->m_curSheet->querySubObject("Columns(int)", col_pos);
	QAxObject* temp_interior = temp_col->querySubObject("Interior");
	temp_interior->setProperty("Color", color);
	delete temp_interior;
	delete temp_col;
}
/*-------------------------------------------------
		样式 - 设置字体名称
		（字体可以去官网找 Font 对象的属性）
*/
void P_ExcelOperater::cell_Style_SetFontFamily(QString start_pos, QString end_pos, QString font_name){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject* temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	QAxObject* temp_font = temp_range->querySubObject("Font");
	temp_font->setProperty("Name", font_name);
	delete temp_font;
	delete temp_range;
}
void P_ExcelOperater::cell_Style_SetFontFamily_Row(int row_pos, QString font_name){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_row = this->m_curSheet->querySubObject("Rows(int)", row_pos);
	QAxObject* temp_font = temp_row->querySubObject("Font");
	temp_font->setProperty("Name", font_name);
	delete temp_font;
	delete temp_row;
}
void P_ExcelOperater::cell_Style_SetFontFamily_Column(int col_pos, QString font_name){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_col = this->m_curSheet->querySubObject("Columns(int)", col_pos);
	QAxObject* temp_font = temp_col->querySubObject("Font");
	temp_font->setProperty("Name", font_name);
	delete temp_font;
	delete temp_col;
}
/*-------------------------------------------------
		样式 - 设置字体加粗
*/
void P_ExcelOperater::cell_Style_SetFontBold(QString start_pos, QString end_pos, bool enabled){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject* temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	QAxObject* temp_font = temp_range->querySubObject("Font");
	temp_font->setProperty("Bold", enabled);
	delete temp_font;
	delete temp_range;
}
void P_ExcelOperater::cell_Style_SetFontBold_Row(int row_pos, bool enabled){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_row = this->m_curSheet->querySubObject("Rows(int)", row_pos);
	QAxObject* temp_font = temp_row->querySubObject("Font");
	temp_font->setProperty("Bold", enabled);
	delete temp_font;
	delete temp_row;
}
void P_ExcelOperater::cell_Style_SetFontBold_Column(int col_pos, bool enabled){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_col = this->m_curSheet->querySubObject("Columns(int)", col_pos);
	QAxObject* temp_font = temp_col->querySubObject("Font");
	temp_font->setProperty("Bold", enabled);
	delete temp_font;
	delete temp_col;
}
/*-------------------------------------------------
		样式 - 设置字体大小
*/
void P_ExcelOperater::cell_Style_SetFontSize(QString start_pos, QString end_pos, int font_size){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject* temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	QAxObject* temp_font = temp_range->querySubObject("Font");
	temp_font->setProperty("Size", font_size);
	delete temp_font;
	delete temp_range;
}
void P_ExcelOperater::cell_Style_SetFontSize_Row(int row_pos, int font_size){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_row = this->m_curSheet->querySubObject("Rows(int)", row_pos);
	QAxObject* temp_font = temp_row->querySubObject("Font");
	temp_font->setProperty("Size", font_size);
	delete temp_font;
	delete temp_row;
}
void P_ExcelOperater::cell_Style_SetFontSize_Column(int col_pos, int font_size){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_col = this->m_curSheet->querySubObject("Columns(int)", col_pos);
	QAxObject* temp_font = temp_col->querySubObject("Font");
	temp_font->setProperty("Size", font_size);
	delete temp_font;
	delete temp_col;
}



#endif // >> QAxWidget控件x32