#include "stdafx.h"
#include "p_ExcelDataGenerator.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Src.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Docs.h"

#include "Source/Utils/operater/excelOperater/p_ExcelOperater.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		�ࣺ		Excel����������.cpp
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�����Զ����Excel�����ʽ��
-----==========================================================-----
*/
P_ExcelDataGenerator::P_ExcelDataGenerator(QObject *parent)
	: QObject(parent)
{
	this->cur_operater = nullptr;
}

P_ExcelDataGenerator::~P_ExcelDataGenerator(){
}


/*-------------------------------------------------
		������ - ���� ����嵥
*/
void P_ExcelDataGenerator::generatePluginDataList(QString save_path){

	// > ��
	cur_operater = new P_ExcelOperater();
	cur_operater->openSoftware();
	cur_operater->newExcelFile();

	// > ��ͷ
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "΢���ź�");
	cur_operater->cell_SetWidth(1, 10);
	cur_operater->cell_SetWidth(2, 36);
	cur_operater->cell_SetWidth(3, 9);
	cur_operater->cell_SetWidth(4, 28);
	cur_operater->cell_SetWidth(5, 31);
	cur_operater->cell_SetWidth(6, 50);
	cur_operater->cell_SetValue("A1", "A1", "����");
	cur_operater->cell_SetValue("B1", "B1", "�����");
	cur_operater->cell_SetValue("C1", "C1", "�������");
	cur_operater->cell_SetValue("D1", "D1", "������");
	cur_operater->cell_SetValue("E1", "E1", "�����ļ�");
	cur_operater->cell_SetValue("F1", "F1", "����ĵ�");

	// > �������
	QString last_type = "";
	QString last_name = "";
	this->cur_row = 2;
	QList<C_PluginData*> plugin_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < plugin_list.count(); i++){
		C_PluginData* plugin = plugin_list.at(i);
		C_ScriptAnnotation annotation = S_InformationDataContainer::getInstance()->getAnnotation(plugin->name);
		C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();
		if (detail == nullptr){ continue; }

		// > �����͵Ĳ��ȥ��
		if (annotation.getPlugindesc_type() == ""){ continue; }

		// > ��ͬ���͸���һ��
		if (annotation.getPlugindesc_type() != last_type){
			last_type = annotation.getPlugindesc_type();
			if (annotation.getName().contains("Drill_X_") == true &&
				last_name.contains("Drill_X_") == true){
				//��������֮�䶼����չ���򲻸�����
			}else{
				cur_operater->cell_MergeCells("A" + QString::number(cur_row), "F" + QString::number(cur_row), true);
				cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_grey());
				cur_row += 1;
			}
		}

		// > �ı� - ����
		QString author_text = annotation.getAuthor();
		author_text = author_text.replace(QRegExp("[,����]"),"\n");

		// > �ı� - �����ļ�
		C_ScriptHelp_Src* src = detail->getSrc();
		QString src_text = "��";
		if (src != nullptr && src->src_list.count() > 0){
			src_text = src->src_list.join("\n");
		}

		// > �ı� - ����ĵ�
		C_ScriptHelp_Docs* docs = detail->getDocs();
		QString docs_text = "��";
		if (docs != nullptr && (docs->main_docx.count() > 0 || docs->relative_docx.count() > 0) ){
			QStringList docs_list, docsText_list;
			docs_list << docs->main_docx << docs->relative_docx;
			for (int j = 0; j < docs_list.count(); j++){
				QString docs = docs_list.at(j);
				QString dir_name = S_LinkDirector::getInstance()->getDirName_ByDoc(docs);
				if (dir_name == ""){
					docsText_list.append(docs);
				}else{
					dir_name.append(" > ");			//����ʾ ��ʵ�ļ������� + �ĵ����ƣ�
					dir_name.append(docs);
					docsText_list.append(dir_name);
				}
			}
			docs_text = docsText_list.join("\n");
		}

		// > �����ı�д��
		cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), author_text);
		cur_operater->cell_SetValue("B" + QString::number(cur_row), "B" + QString::number(cur_row), annotation.getName());
		cur_operater->cell_SetValue("C" + QString::number(cur_row), "C" + QString::number(cur_row), annotation.getPlugindesc_type());
		cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), annotation.getPlugindesc_name());
		cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), src_text);
		cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), docs_text);

		// > ������ʽ����
		if (annotation.getAuthor().indexOf("Drill_up") == 0 ){	//����ΪDrill_up��ͷ�Ĳ�������Զ����У�
			cur_operater->cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
		}else{
			cur_operater->cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), false);
		}
		cur_operater->cell_SetWrapText("E" + QString::number(cur_row), "E" + QString::number(cur_row), true);
		cur_operater->cell_SetWrapText("F" + QString::number(cur_row), "F" + QString::number(cur_row), true);
		cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");

		// > ���н���
		last_name = annotation.getName();
		cur_row += 1;
	}

	// > ���һ�а���
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "F" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_grey());
	cur_row += 1;

	// > ����
	cur_operater->saveAsExcelFile(save_path);
	cur_operater->closeSoftware();
	delete cur_operater;
}



/*-------------------------------------------------
		������ - ���� ���ܲ���ͳ�Ʊ�
*/
void P_ExcelDataGenerator::generatePerformanceDataList(QString save_path){

	// > ��
	cur_operater = new P_ExcelOperater();
	cur_operater->openSoftware();
	cur_operater->newExcelFile();

	// > �����嵥��
	cur_operater->copyCurSheet();
	cur_operater->copyCurSheet();
	cur_operater->selectSheet(1);
	cur_operater->setSheetName("��ͼ����");
	cur_operater->selectSheet(2);
	cur_operater->setSheetName("ս������");
	cur_operater->selectSheet(3);
	cur_operater->setSheetName("�˵�����");


	// > ��ͷ
	cur_operater->selectSheet(1);
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "΢���ź�");
	cur_operater->cell_SetWidth(1, 36);
	cur_operater->cell_SetWidth(2, 9);
	cur_operater->cell_SetWidth(3, 28);
	cur_operater->cell_SetWidth(4, 11);
	cur_operater->cell_SetWidth(5, 10);
	cur_operater->cell_SetWidth(6, 10);
	cur_operater->cell_SetWidth(7, 10);
	cur_operater->cell_SetWidth(8, 10);
	cur_operater->cell_SetWidth(9, 38);
	cur_operater->cell_SetValue("A1", "A1", "�����");
	cur_operater->cell_SetValue("B1", "B1", "�������");
	cur_operater->cell_SetValue("C1", "C1", "������");
	cur_operater->cell_SetValue("D1", "D1", "��������");
	cur_operater->cell_SetValue("E1", "E1", "200���¼�");
	cur_operater->cell_SetValue("F1", "F1", "100���¼�");
	cur_operater->cell_SetValue("G1", "G1", "50���¼�");
	cur_operater->cell_SetValue("H1", "H1", "20���¼�");
	cur_operater->cell_SetValue("I1", "I1", "ʱ�临�Ӷ�");

	// > ���ܲ���˵����ͷ��
	this->cur_row = 2;
	this->generatePerformanceNotes();

	// > ��ͼ��������ͷ��
	QString scene_name = "��ͼ����";
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), scene_name);
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;

	// > ���ɽ�����������
	this->generatePerformanceSceneData(scene_name);


	// > ��ͷ
	cur_operater->selectSheet(2);
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "΢���ź�");
	cur_operater->cell_SetWidth(1, 36);
	cur_operater->cell_SetWidth(2, 9);
	cur_operater->cell_SetWidth(3, 28);
	cur_operater->cell_SetWidth(4, 11);
	cur_operater->cell_SetWidth(5, 10);
	cur_operater->cell_SetWidth(6, 10);
	cur_operater->cell_SetWidth(7, 10);
	cur_operater->cell_SetWidth(8, 10);
	cur_operater->cell_SetWidth(9, 38);
	cur_operater->cell_SetValue("A1", "A1", "�����");
	cur_operater->cell_SetValue("B1", "B1", "�������");
	cur_operater->cell_SetValue("C1", "C1", "������");
	cur_operater->cell_SetValue("D1", "D1", "��������");
	cur_operater->cell_SetValue("E1", "E1", "8-16����λ");
	cur_operater->cell_SetValue("F1", "F1", "4-8����λ");
	cur_operater->cell_SetValue("G1", "G1", "1-2����λ");
	cur_operater->cell_SetValue("H1", "H1", "��");
	cur_operater->cell_SetValue("I1", "I1", "ʱ�临�Ӷ�");

	// > ���ܲ���˵����ͷ��
	this->cur_row = 2;
	this->generatePerformanceNotes();

	// > ��ͼ��������ͷ��
	scene_name = "ս������";
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), scene_name);
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;

	// > ���ɽ�����������
	this->generatePerformanceSceneData(scene_name);


	// > ��ͷ
	cur_operater->selectSheet(3);
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "΢���ź�");
	cur_operater->cell_SetWidth(1, 36);
	cur_operater->cell_SetWidth(2, 9);
	cur_operater->cell_SetWidth(3, 28);
	cur_operater->cell_SetWidth(4, 11);
	cur_operater->cell_SetWidth(5, 10);
	cur_operater->cell_SetWidth(6, 10);
	cur_operater->cell_SetWidth(7, 10);
	cur_operater->cell_SetWidth(8, 10);
	cur_operater->cell_SetWidth(9, 38);
	cur_operater->cell_SetValue("A1", "A1", "�����");
	cur_operater->cell_SetValue("B1", "B1", "�������");
	cur_operater->cell_SetValue("C1", "C1", "������");
	cur_operater->cell_SetValue("D1", "D1", "��������");
	cur_operater->cell_SetValue("E1", "E1", "�̶�4");
	cur_operater->cell_SetValue("F1", "F1", "�̶�3");
	cur_operater->cell_SetValue("G1", "G1", "�̶�2");
	cur_operater->cell_SetValue("H1", "H1", "�̶�1");
	cur_operater->cell_SetValue("I1", "I1", "ʱ�临�Ӷ�");

	// > ���ܲ���˵����ͷ��
	this->cur_row = 2;
	this->generatePerformanceNotes();

	// > ��ͼ��������ͷ��
	scene_name = "�˵�����";
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), scene_name);
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;

	// > ���ɽ�����������
	this->generatePerformanceSceneData(scene_name);


	// > ����
	cur_operater->saveAsExcelFile(save_path);
	cur_operater->closeSoftware();
}
/*-------------------------------------------------
		�׶� - ���� ���ܲ���˵������
*/
void P_ExcelDataGenerator::generatePerformanceNotes(){

	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "���ܲ���˵��");
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_row += 1;
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "1.���ܲ����ǻ��ڵ�����Եı�׼���ڸ�������в��Ե�������ֵ�϶���ȵ������С�öࡣ");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0,0,0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "��Χ");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "�̶�");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "2.���Խ�࣬���ĵ�ҲԽ�ࡣ����Լ��ٸ����ĵĲ����������Ϸ�����ԡ�");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(0));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "0.00ms - 40.00ms");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "����������");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "3.��F2����ʵʱ�鿴��Ϸ��֡������������������30֡�����Ҫ���ǿ��������ˡ�");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(1));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "40.00ms - 80.00ms");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "������");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "4.���в��Ե�ʱ��Ϊ20000.00ms��20�룩��ms���Ǻ��룬1��=1000���롣");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(2));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "80.00ms - 120.00ms");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "������");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "5.���Խ������˼�ǣ�20���ʱ������������ռ���˶��ٺ��������м��㡣");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(3));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "120.00ms����");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "������");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "6.���Խ�������Ǿ�ȷֵ����Χ�ڸ���ֵ��10.00ms��Χ�ڲ�����");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;

	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "7.����һ�ᣬִ�з�ʽΪ'���ʳ���'�Ĳ��������ʹ���������ı����������������ֵԽ�ߣ�����Խ��");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");
	cur_row += 1;
	cur_row += 1;
}
/*-------------------------------------------------
		�׶� - ���� ������������
*/
void P_ExcelDataGenerator::generatePerformanceSceneData(QString scene_name){

	// > �������
	QString last_type = "";
	QString last_name = "";
	QList<C_PluginData*> plugin_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < plugin_list.count(); i++){
		C_PluginData* plugin = plugin_list.at(i);
		C_ScriptAnnotation annotation = S_InformationDataContainer::getInstance()->getAnnotation(plugin->name);
		C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();
		if (detail == nullptr){ continue; }

		// > �����͵Ĳ��ȥ��
		if (annotation.getPlugindesc_type() == ""){ continue; }

		// > ��ͬ���͸���һ��
		if (annotation.getPlugindesc_type() != last_type){
			last_type = annotation.getPlugindesc_type();
			if (annotation.getName().contains("Drill_X_") == true &&
				last_name.contains("Drill_X_") == true){
				//��������֮�䶼����չ���򲻸�����
			}
			else{
				cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
				cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
				cur_row += 1;
			}
		}

		// > �����ı�д��
		cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), annotation.getName());
		cur_operater->cell_SetValue("B" + QString::number(cur_row), "B" + QString::number(cur_row), annotation.getPlugindesc_type());
		cur_operater->cell_SetValue("C" + QString::number(cur_row), "C" + QString::number(cur_row), annotation.getPlugindesc_name());
		C_ScriptHelp_Performance* performance = detail->getPerformance();
		C_ScriptHelp_EffectScope* scope = detail->getEffectScope();

		// > û�в�������ʱ
		if (performance == nullptr){
			cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), "��");

		}else{

			// > ��������
			if (performance->working_type == "���ʳ���"){
				cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), performance->working_type);
				cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), "ֱ��Ӱ����Ϸ�������������");
				cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
				cur_operater->cell_SetValue("I" + QString::number(cur_row), "I" + QString::number(cur_row), performance->time_complexity);
			}else{

				// > ���ݴ������
				double max_cost = performance->getMaxCost();
				if (max_cost == -1){
					cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), "���ݴ���");
					cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
				}
				else{

					// > �������ͣ�����ִ��/����ִ�У�
					cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), performance->working_type);

					// > �̶ֳȣ�ֻҪ��һ������ֵ ����5ms ���㣩
					double temp_cost_4 = performance->getMinCost_ByLevel(scene_name, 4);
					if (temp_cost_4 > 5){
						double temp_cost_1 = performance->getMinCost_ByLevel(scene_name, 1);
						double temp_cost_2 = performance->getMinCost_ByLevel(scene_name, 2);
						double temp_cost_3 = performance->getMinCost_ByLevel(scene_name, 3);
						double temp_cost_4 = performance->getMinCost_ByLevel(scene_name, 4);
						QString temp_costStr_1 = QString::number(temp_cost_1) + "ms";
						QString temp_costStr_2 = QString::number(temp_cost_2) + "ms";
						QString temp_costStr_3 = QString::number(temp_cost_3) + "ms";
						QString temp_costStr_4 = QString::number(temp_cost_4) + "ms";
						if (temp_cost_1 <= 5){ temp_costStr_1 = "5ms����"; }
						if (temp_cost_2 <= 5){ temp_costStr_2 = "5ms����"; }
						if (temp_cost_3 <= 5){ temp_costStr_3 = "5ms����"; }
						if (temp_cost_4 <= 5){ temp_costStr_4 = "5ms����"; }
						if (temp_cost_1 < 0){ temp_costStr_1 = "δ��"; }
						if (temp_cost_2 < 0){ temp_costStr_2 = "δ��"; }
						if (temp_cost_3 < 0){ temp_costStr_3 = "δ��"; }
						if (temp_cost_4 < 0){ temp_costStr_4 = "δ��"; }
						cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), temp_costStr_4);
						cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), temp_costStr_3);
						cur_operater->cell_SetValue("G" + QString::number(cur_row), "G" + QString::number(cur_row), temp_costStr_2);
						cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), temp_costStr_1);
						cur_operater->cell_Style_SetBackground("E" + QString::number(cur_row), "E" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_4));
						cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_3));
						cur_operater->cell_Style_SetBackground("G" + QString::number(cur_row), "G" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_2));
						cur_operater->cell_Style_SetBackground("H" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_1));

					}
					else{

						// > ���̶ֳȣ�ֻҪ��һ������ʾ�Ĳ���ֵ ���㣩
						double temp_cost_0 = performance->getMinCost_ByLevel(scene_name, 0);
						if (temp_cost_4 > 0){ temp_cost_0 = temp_cost_4; }	//������ĸ�ȫ��С��5ms����ô����ʾ������Ϊ"5ms����"��
						if (temp_cost_0 > 0){
							QString temp_costStr_0 = QString("  ") + QString::number(temp_cost_0) + "ms";
							if (temp_cost_0 <= 5){ temp_costStr_0 = "  5ms����"; }
							cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), temp_costStr_0);
							cur_operater->cell_Style_SetBackground("E" + QString::number(cur_row), "E" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_0));
							cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);

							// > ��ûֵ��˵���������ڴ˴���
						}
						else{
							if (scope->isEnableScene(scene_name)){
								cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), "����ȱʧ");
								cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
							}
							else{
								cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), QString("ֻ������") + scope->getEnabledScene().join("��"));
								cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
							}
						}
					}

					// > ʱ�临�Ӷ�
					cur_operater->cell_SetValue("I" + QString::number(cur_row), "I" + QString::number(cur_row), performance->time_complexity);
				}
			}
		}

		// > �߿�����+��������
		cur_operater->cell_Style_SetAllBorder("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
		cur_operater->cell_Style_SetFontFamily_Row(cur_row, "΢���ź�");

		// > ���н���
		last_name = annotation.getName();
		cur_row += 1;
	}
}
/*-------------------------------------------------
		��ɫ - ��ɫ
*/
QColor P_ExcelDataGenerator::getColor_grey(){
	return QColor(217, 217, 217);
}
/*-------------------------------------------------
		��ɫ - ��ɫ
*/
QColor P_ExcelDataGenerator::getColor_ByCritical(int critical){
	if (critical == 0){
		return QColor(255, 255, 255);
	}
	if (critical == 1){
		return QColor(242, 220, 219);
	}
	if (critical == 2){
		return QColor(230, 184, 183);
	}
	if (critical == 3){
		return QColor(204, 108, 106);
	}
	return QColor(255, 255, 255);
}
/*-------------------------------------------------
		��ɫ - ��ɫ������ֵ��
*/
QColor P_ExcelDataGenerator::getColor_ByCriticalValue(double critical_value){
	if (critical_value >= 120){
		return this->getColor_ByCritical(3);
	}
	if (critical_value >= 80){
		return this->getColor_ByCritical(2);
	}
	if (critical_value >= 40){
		return this->getColor_ByCritical(1);
	}
	return this->getColor_ByCritical(0);
}