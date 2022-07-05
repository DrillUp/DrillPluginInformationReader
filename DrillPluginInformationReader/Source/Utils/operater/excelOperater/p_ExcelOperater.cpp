#include "stdafx.h"
#include "P_ExcelOperater.h"

// >> QAxWidget�ؼ�x32
#ifndef WIN64

/*
-----==========================================================-----
		�ࣺ		Excel������.cpp
		�汾��		v1.00
		���ߣ�		drill_up
		����ģ�飺	����ģ��
		���ܣ�		����Excel���д�����ݡ�
					��ע�⣬�˲�����ֻ����32λ���������С�

		ʹ�÷�����
				>��ʼ��

-----==========================================================-----
*/
P_ExcelOperater::P_ExcelOperater(){
	
	this->m_application = new QAxObject();		//�������
	this->m_workBookTank = nullptr;				//����������
	this->m_isSoftwareInited = false;			//����Ƿ��ʼ��
	this->m_isSoftwareOpened = false;			//����Ƿ��

	this->m_curPath = "";						//�ļ�·��
	this->m_curWorkBook = nullptr;				//��ǰ������
	this->m_curSheetTank = nullptr;				//����������

	this->m_curSheet = nullptr;					//��ǰ������
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
		��� - �����
*/
bool P_ExcelOperater::openSoftware(){
	if (this->m_isSoftwareInited == true){ return this->m_isSoftwareOpened; }
	this->m_isSoftwareInited = true;

	// > �����
	bool success = this->m_application->setControl("Excel.Application");
	if ( success == false){
		QMessageBox::about(nullptr, "����", "�޷���Excel�����");
		this->m_isSoftwareOpened = false;
		return false;
	}
	// > ���ڿɼ�
	this->m_application->setProperty("Visible", true);
	// > ������ʾ
	this->m_application->setProperty("DisplayAlerts", true);
	// > ��ʾsheet�仯����
	this->m_application->setProperty("ScreenUpdating", true);

	// > ����������
	this->m_workBookTank = this->m_application->querySubObject("WorkBooks");
	if (this->m_workBookTank == nullptr){
		QMessageBox::about(nullptr, "����", "�޷���WorkBooks������������");
		this->m_isSoftwareOpened = false;
		return false;
	}
	this->m_isSoftwareOpened = true;
	return true;
}
/*-------------------------------------------------
		��� - �ر����
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
		��� - �Ƿ�ɹ���
*/
bool P_ExcelOperater::isOpened_Software(){
	return this->m_isSoftwareOpened;
}


/*-------------------------------------------------
		������ - �½�
*/
void P_ExcelOperater::newExcelFile(){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return; }
	
	// > �½�
	this->m_workBookTank->dynamicCall("Add");
	
	// > �򿪵�ǰ������
	this->m_curWorkBook = this->m_application->querySubObject("ActiveWorkBook");
	if (this->m_curWorkBook == nullptr){
		QMessageBox::about(nullptr, "����", "�޷��򿪵�ǰ��������");
		return;
	}

	// > �򿪹���������
	this->m_curSheetTank = this->m_curWorkBook->querySubObject("Sheets");
	if (this->m_curSheetTank == nullptr){
		QMessageBox::about(nullptr, "����", "�޷���Sheets������������");
		return;
	}
	
	// > ѡ��1�Ź�����
	this->selectSheet(1);
}
/*-------------------------------------------------
		������ - ��
*/
void P_ExcelOperater::openExcelFile(QString file_path){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return; }
	
	// > ��·��
	this->m_workBookTank->dynamicCall("Open(QString)", QDir::toNativeSeparators(file_path), QString(), false);
	
	// > �򿪵�ǰ������
	this->m_curWorkBook = this->m_application->querySubObject("ActiveWorkBook");
	if (this->m_curWorkBook == nullptr){
		QMessageBox::about(nullptr, "����", "�޷��򿪵�ǰ��������");
		return;
	}
	this->m_curPath = file_path;

	// > �򿪹���������
	this->m_curSheetTank = this->m_curWorkBook->querySubObject("Sheets");
	if (this->m_curSheetTank == nullptr){
		QMessageBox::about(nullptr, "����", "�޷���Sheets������������");
		return;
	}

	// > ѡ��1�Ź�����
	this->selectSheet(1);
}
/*-------------------------------------------------
		������ - ����
*/
bool P_ExcelOperater::saveExcelFile(){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return false; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return false; }
	if (this->m_curPath == ""){ Q_ASSERT(false); return false; }
	this->m_curWorkBook->dynamicCall("Save()");
	return true;
}
/*-------------------------------------------------
		������ - ���Ϊ
*/
bool P_ExcelOperater::saveAsExcelFile(QString file_path){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return false; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return false; }
	this->m_curWorkBook->dynamicCall("SaveAs(QString)", QDir::toNativeSeparators(file_path));
	return true;
}
/*-------------------------------------------------
		������ - �Ƿ�ɹ���
*/
bool P_ExcelOperater::isOpened_ExcelFile(){
	return this->m_curWorkBook != nullptr;
}



/*-------------------------------------------------
		������ - ѡ������
*/
void P_ExcelOperater::selectSheet(int i){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return; }
	if (this->m_curSheetTank == nullptr){ Q_ASSERT(false); return; }
	this->m_curSheet = this->m_curSheetTank->querySubObject("Item(int)", i);
}
/*-------------------------------------------------
		������ - ���ƹ�����
*/
void P_ExcelOperater::copyCurSheet(){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QVariant sheetObj = this->m_curSheet->asVariant();
	this->m_curSheet->dynamicCall("Copy(QVariant)", sheetObj);
}
/*-------------------------------------------------
		������ - ����������
*/
int P_ExcelOperater::getSheetCount(){
	if (this->isOpened_Software() == false){ Q_ASSERT(false); return 0; }
	if (this->isOpened_ExcelFile() == false){ Q_ASSERT(false); return 0; }
	if (this->m_curSheetTank == nullptr){ Q_ASSERT(false); return 0; }
	return this->m_curSheetTank->property("Count").toInt();
}
/*-------------------------------------------------
		������ - �Ƿ�ɹ���
*/
bool P_ExcelOperater::isOpened_Sheet(){
	return this->m_curSheet != nullptr;
}


/*-------------------------------------------------
		����ֵ - ����ֵ
*/
void P_ExcelOperater::cell_SetValue(QString start_pos, QString end_pos, QString value){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	temp_range->setProperty("Value", value);
	delete temp_range;
}
/*-------------------------------------------------
		����ֵ - ��ȡֵ
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
		��Ԫ�� - ��������
*/
void P_ExcelOperater::cell_FreezePanes_OnlyRow(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "����", "����ʧ��(��������)��");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	temp_activeWindow->setProperty("SplitColumn", 0);
	temp_activeWindow->setProperty("SplitRow", 1);
	temp_activeWindow->setProperty("FreezePanes", true);
	delete temp_activeWindow;
}
/*-------------------------------------------------
		��Ԫ�� - ��������
*/
void P_ExcelOperater::cell_FreezePanes_OnlyColumn(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "����", "����ʧ��(��������)��");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	temp_activeWindow->setProperty("SplitColumn", 1);
	temp_activeWindow->setProperty("SplitRow", 0);
	temp_activeWindow->setProperty("FreezePanes", true);
	delete temp_activeWindow;
}
/*-------------------------------------------------
		��Ԫ�� - �������к�����
*/
void P_ExcelOperater::cell_FreezePanes_RowAndColumn(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "����", "����ʧ��(�������к�����)��");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	temp_activeWindow->setProperty("SplitColumn", 1);
	temp_activeWindow->setProperty("SplitRow", 1);
	temp_activeWindow->setProperty("FreezePanes", true);
	delete temp_activeWindow;
}
/*-------------------------------------------------
		��Ԫ�� - ����ر�
*/
void P_ExcelOperater::cell_FreezePanes_None(){
	QAxObject* temp_activeWindow = this->m_application->querySubObject("ActiveWindow");
	if (temp_activeWindow == nullptr){
		QMessageBox::about(nullptr, "����", "����ʧ��(�رն���)��");
		return;
	}
	temp_activeWindow->setProperty("FreezePanes", false);
	delete temp_activeWindow;
}

/*-------------------------------------------------
		��Ԫ�� - ���ÿ��
*/
void P_ExcelOperater::cell_SetWidth(int col_pos, int width){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_col = this->m_curSheet->querySubObject("Columns(int)", col_pos);
	temp_col->setProperty("ColumnWidth", width);
	delete temp_col;
}
/*-------------------------------------------------
		��Ԫ�� - ���ø߶�
*/
void P_ExcelOperater::cell_SetHeight(int row_pos, int height){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_row = this->m_curSheet->querySubObject("Rows(int)", row_pos);
	temp_row->setProperty("RowHeight", height);
	delete temp_row;
}
/*-------------------------------------------------
		��Ԫ�� - �ϲ���Ԫ��
*/
void P_ExcelOperater::cell_MergeCells(QString start_pos, QString end_pos, bool enabled){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	temp_range->setProperty("MergeCells", enabled);
	delete temp_range;
}
/*-------------------------------------------------
		��Ԫ�� - �����Զ�����
*/
void P_ExcelOperater::cell_SetWrapText(QString start_pos, QString end_pos, bool enabled){
	if (this->isOpened_Sheet() == false){ Q_ASSERT(false); return; }
	QAxObject *temp_range = this->m_curSheet->querySubObject("Range(QVariant, QVariant)", start_pos, end_pos);
	temp_range->setProperty("WrapText", enabled);
	delete temp_range;
}


/*-------------------------------------------------
		��ʽ - ���ñ���
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
		��ʽ - ������������
		���������ȥ������ Font ��������ԣ�
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
		��ʽ - ��������Ӵ�
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
		��ʽ - ���������С
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



#endif // >> QAxWidget�ؼ�x32