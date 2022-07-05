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
		类：		Excel表格生成器.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	生成自定义的Excel表格格式。
-----==========================================================-----
*/
P_ExcelDataGenerator::P_ExcelDataGenerator(QObject *parent)
	: QObject(parent)
{

}

P_ExcelDataGenerator::~P_ExcelDataGenerator(){
}

/*-------------------------------------------------
		生成器 - 生成插件清单
*/
void P_ExcelDataGenerator::generatePluginDataList(QString save_path){

	P_ExcelOperater operater = P_ExcelOperater();
	operater.openSoftware();
	operater.newExcelFile();

	// > 表头
	operater.cell_FreezePanes_OnlyRow();
	operater.cell_SetWidth(2, 30);
	operater.cell_Style_SetBackground_Row(1, QColor(217, 217, 217));
	operater.cell_Style_SetFontBold_Row(1, true);
	operater.cell_Style_SetFontFamily_Row(1, "微软雅黑");
	operater.cell_SetWidth(1, 10);
	operater.cell_SetWidth(2, 36);
	operater.cell_SetWidth(3, 9);
	operater.cell_SetWidth(4, 28);
	operater.cell_SetWidth(5, 31);
	operater.cell_SetWidth(6, 50);
	operater.cell_SetValue("A1", "A1", "作者");
	operater.cell_SetValue("B1", "B1", "插件名");
	operater.cell_SetValue("C1", "C1", "插件类型");
	operater.cell_SetValue("D1", "D1", "中文名");
	operater.cell_SetValue("E1", "E1", "关联文件");
	operater.cell_SetValue("F1", "F1", "相关文档");

	// > 插件数据
	QString last_type = "";
	int cur_row = 2;
	QList<C_PluginData*> plugin_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < plugin_list.count(); i++){
		C_PluginData* plugin = plugin_list.at(i);
		C_ScriptAnnotation annotation = S_InformationDataContainer::getInstance()->getAnnotation(plugin->name);
		C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();
		if (detail == nullptr){ continue; }

		// > 空类型的去掉
		if (annotation.getPlugindesc_type() == ""){ continue; }
		if (annotation.getPlugindesc_type() != last_type){
			last_type = annotation.getPlugindesc_type();
			if (annotation.getName().contains("Drill_X_") == false){
				cur_row += 1;	//（不同类型隔开一下，但扩展除外）
			}
		}

		// > 作者
		QString author_text = annotation.getAuthor();
		author_text = author_text.replace(QRegExp("[,，、]"),"\n");

		// > 关联文件
		C_ScriptHelp_Src* src = detail->getSrc();
		QString src_text = "无";
		if (src != nullptr && src->src_list.count() > 0){
			src_text = src->src_list.join("\n");
		}

		// > 相关文档
		C_ScriptHelp_Docs* docs = detail->getDocs();
		QString docs_text = "无";
		if (docs != nullptr && (docs->main_docx.count() > 0 || docs->relative_docx.count() > 0) ){
			QStringList docs_list, docsText_list;
			docs_list << docs->main_docx << docs->relative_docx;
			for (int j = 0; j < docs_list.count(); j++){
				QString docs = docs_list.at(j);
				QString dir_name = S_LinkDirector::getInstance()->getDirName_ByDoc(docs);
				if (dir_name == ""){
					docsText_list.append(docs);
				}else{
					dir_name.append(" > ");			//（显示 真实文件夹名称 + 文档名称）
					dir_name.append(docs);
					docsText_list.append(dir_name);
				}
			}
			docs_text = docsText_list.join("\n");
		}

		operater.cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), author_text);
		operater.cell_SetValue("B" + QString::number(cur_row), "B" + QString::number(cur_row), annotation.getName());
		operater.cell_SetValue("C" + QString::number(cur_row), "C" + QString::number(cur_row), annotation.getPlugindesc_type());
		operater.cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), annotation.getPlugindesc_name());
		operater.cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), src_text);
		operater.cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), docs_text);

		if (annotation.getName().contains("Drill_up")){	//（名为Drill_up的插件允许自动换行）
			operater.cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
		}else{
			operater.cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), false);
		}
		operater.cell_SetWrapText("E" + QString::number(cur_row), "E" + QString::number(cur_row), true);
		operater.cell_SetWrapText("F" + QString::number(cur_row), "F" + QString::number(cur_row), true);
		operater.cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
		cur_row += 1;
	}

	operater.saveAsExcelFile(save_path);
	operater.closeSoftware();
}