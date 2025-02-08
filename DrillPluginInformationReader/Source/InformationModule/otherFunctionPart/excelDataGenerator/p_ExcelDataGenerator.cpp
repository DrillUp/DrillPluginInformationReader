#include "stdafx.h"
#include "p_ExcelDataGenerator.h"

#include "Source/RmmvInteractiveModule/InformationData/S_InformationDataContainer.h"
#include "Source/InformationModule/LinkDirector/S_LinkDirector.h"
#include "Source/RmmvUtilsPluginModule/StorageData/S_PluginDataContainer.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelpDetail.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelp_Src.h"
#include "Source/RmmvUtilsPluginModule/ScriptReader/HelpDetail/C_ScriptHelp_Docs.h"

#include "Source/Utils/Operater/ExcelOperater/P_ExcelOperater.h"
#include "Source/Utils/Common/TTool.h"

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
	this->cur_operater = nullptr;
}

P_ExcelDataGenerator::~P_ExcelDataGenerator(){
}


/*-------------------------------------------------
		生成器 - 生成 插件清单
*/
void P_ExcelDataGenerator::generatePluginDataList(QString save_path){

	// > 打开
	cur_operater = new P_ExcelOperater();
	cur_operater->openSoftware();
	cur_operater->newExcelFile();

	// > 表头
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "微软雅黑");
	cur_operater->cell_SetWidth(1, 10);
	cur_operater->cell_SetWidth(2, 36);
	cur_operater->cell_SetWidth(3, 9);
	cur_operater->cell_SetWidth(4, 28);
	cur_operater->cell_SetWidth(5, 31);
	cur_operater->cell_SetWidth(6, 50);
	cur_operater->cell_SetValue("A1", "A1", "作者");
	cur_operater->cell_SetValue("B1", "B1", "插件名");
	cur_operater->cell_SetValue("C1", "C1", "插件类型");
	cur_operater->cell_SetValue("D1", "D1", "中文名");
	cur_operater->cell_SetValue("E1", "E1", "关联文件");
	cur_operater->cell_SetValue("F1", "F1", "相关文档");

	// > 插件数据
	QString last_type = "";
	QString last_name = "";
	this->cur_row = 2;
	QList<C_PluginData*> plugin_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < plugin_list.count(); i++){
		C_PluginData* plugin = plugin_list.at(i);
		C_ScriptAnnotation annotation = S_InformationDataContainer::getInstance()->getAnnotation(plugin->name);
		C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();
		if (detail == nullptr){ continue; }

		// > 空类型的插件去掉
		if (annotation.getPlugindesc_type() == ""){ continue; }

		// > 不同类型隔开一下
		if (annotation.getPlugindesc_type() != last_type){
			last_type = annotation.getPlugindesc_type();
			if (annotation.getName().contains("Drill_X_") == true &&
				last_name.contains("Drill_X_") == true){
				//（如果插件之间都是扩展，则不隔开）
			}else{
				cur_operater->cell_MergeCells("A" + QString::number(cur_row), "F" + QString::number(cur_row), true);
				cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_grey());
				cur_row += 1;
			}
		}

		// > 文本 - 作者
		QString author_text = annotation.getAuthor();
		author_text = author_text.replace(QRegExp("[,，、]"),"\n");

		// > 文本 - 关联文件
		C_ScriptHelp_Src* src = detail->getSrc();
		QString src_text = "无";
		if (src != nullptr && src->src_list.count() > 0){
			src_text = src->src_list.join("\n");
		}

		// > 文本 - 相关文档
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

		// > 单行文本写入
		cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), author_text);
		cur_operater->cell_SetValue("B" + QString::number(cur_row), "B" + QString::number(cur_row), annotation.getName());
		cur_operater->cell_SetValue("C" + QString::number(cur_row), "C" + QString::number(cur_row), annotation.getPlugindesc_type());
		cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), annotation.getPlugindesc_name());
		cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), src_text);
		cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), docs_text);

		// > 单行样式设置
		if (annotation.getAuthor().indexOf("Drill_up") == 0 ){	//（名为Drill_up开头的插件允许自动换行）
			cur_operater->cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
		}else{
			cur_operater->cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), false);
		}
		cur_operater->cell_SetWrapText("E" + QString::number(cur_row), "E" + QString::number(cur_row), true);
		cur_operater->cell_SetWrapText("F" + QString::number(cur_row), "F" + QString::number(cur_row), true);
		cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");

		// > 单行结束
		last_name = annotation.getName();
		cur_row += 1;
	}

	// > 最后一行包裹
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "F" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_grey());
	cur_row += 1;

	// > 保存
	cur_operater->saveAsExcelFile(save_path);
	cur_operater->closeSoftware();
	delete cur_operater;
}



/*-------------------------------------------------
		生成器 - 生成 性能测试统计表
*/
void P_ExcelDataGenerator::generatePerformanceDataList(QString save_path){

	// > 打开
	cur_operater = new P_ExcelOperater();
	cur_operater->openSoftware();
	cur_operater->newExcelFile();

	// > 工作清单表
	cur_operater->copyCurSheet();
	cur_operater->copyCurSheet();
	cur_operater->selectSheet(1);
	cur_operater->setSheetName("地图界面");
	cur_operater->selectSheet(2);
	cur_operater->setSheetName("战斗界面");
	cur_operater->selectSheet(3);
	cur_operater->setSheetName("菜单界面");


	// > 表头
	cur_operater->selectSheet(1);
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "微软雅黑");
	cur_operater->cell_SetWidth(1, 36);
	cur_operater->cell_SetWidth(2, 9);
	cur_operater->cell_SetWidth(3, 28);
	cur_operater->cell_SetWidth(4, 11);
	cur_operater->cell_SetWidth(5, 10);
	cur_operater->cell_SetWidth(6, 10);
	cur_operater->cell_SetWidth(7, 10);
	cur_operater->cell_SetWidth(8, 10);
	cur_operater->cell_SetWidth(9, 38);
	cur_operater->cell_SetValue("A1", "A1", "插件名");
	cur_operater->cell_SetValue("B1", "B1", "插件类型");
	cur_operater->cell_SetValue("C1", "C1", "中文名");
	cur_operater->cell_SetValue("D1", "D1", "工作类型");
	cur_operater->cell_SetValue("E1", "E1", "200个事件");
	cur_operater->cell_SetValue("F1", "F1", "100个事件");
	cur_operater->cell_SetValue("G1", "G1", "50个事件");
	cur_operater->cell_SetValue("H1", "H1", "20个事件");
	cur_operater->cell_SetValue("I1", "I1", "时间复杂度");

	// > 性能测试说明（头）
	this->cur_row = 2;
	this->generatePerformanceNotes();

	// > 地图界面栏（头）
	QString scene_name = "地图界面";
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), scene_name);
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;

	// > 生成界面数据内容
	this->generatePerformanceSceneData(scene_name);


	// > 表头
	cur_operater->selectSheet(2);
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "微软雅黑");
	cur_operater->cell_SetWidth(1, 36);
	cur_operater->cell_SetWidth(2, 9);
	cur_operater->cell_SetWidth(3, 28);
	cur_operater->cell_SetWidth(4, 11);
	cur_operater->cell_SetWidth(5, 10);
	cur_operater->cell_SetWidth(6, 10);
	cur_operater->cell_SetWidth(7, 10);
	cur_operater->cell_SetWidth(8, 10);
	cur_operater->cell_SetWidth(9, 38);
	cur_operater->cell_SetValue("A1", "A1", "插件名");
	cur_operater->cell_SetValue("B1", "B1", "插件类型");
	cur_operater->cell_SetValue("C1", "C1", "中文名");
	cur_operater->cell_SetValue("D1", "D1", "工作类型");
	cur_operater->cell_SetValue("E1", "E1", "8-16个单位");
	cur_operater->cell_SetValue("F1", "F1", "4-8个单位");
	cur_operater->cell_SetValue("G1", "G1", "1-2个单位");
	cur_operater->cell_SetValue("H1", "H1", "无");
	cur_operater->cell_SetValue("I1", "I1", "时间复杂度");

	// > 性能测试说明（头）
	this->cur_row = 2;
	this->generatePerformanceNotes();

	// > 地图界面栏（头）
	scene_name = "战斗界面";
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), scene_name);
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;

	// > 生成界面数据内容
	this->generatePerformanceSceneData(scene_name);


	// > 表头
	cur_operater->selectSheet(3);
	cur_operater->cell_FreezePanes_OnlyRow();
	cur_operater->cell_SetWidth(2, 30);
	cur_operater->cell_Style_SetBackground_Row(1, this->getColor_grey());
	cur_operater->cell_Style_SetFontBold_Row(1, true);
	cur_operater->cell_Style_SetFontFamily_Row(1, "微软雅黑");
	cur_operater->cell_SetWidth(1, 36);
	cur_operater->cell_SetWidth(2, 9);
	cur_operater->cell_SetWidth(3, 28);
	cur_operater->cell_SetWidth(4, 11);
	cur_operater->cell_SetWidth(5, 10);
	cur_operater->cell_SetWidth(6, 10);
	cur_operater->cell_SetWidth(7, 10);
	cur_operater->cell_SetWidth(8, 10);
	cur_operater->cell_SetWidth(9, 38);
	cur_operater->cell_SetValue("A1", "A1", "插件名");
	cur_operater->cell_SetValue("B1", "B1", "插件类型");
	cur_operater->cell_SetValue("C1", "C1", "中文名");
	cur_operater->cell_SetValue("D1", "D1", "工作类型");
	cur_operater->cell_SetValue("E1", "E1", "程度4");
	cur_operater->cell_SetValue("F1", "F1", "程度3");
	cur_operater->cell_SetValue("G1", "G1", "程度2");
	cur_operater->cell_SetValue("H1", "H1", "程度1");
	cur_operater->cell_SetValue("I1", "I1", "时间复杂度");

	// > 性能测试说明（头）
	this->cur_row = 2;
	this->generatePerformanceNotes();

	// > 地图界面栏（头）
	scene_name = "菜单界面";
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), scene_name);
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;

	// > 生成界面数据内容
	this->generatePerformanceSceneData(scene_name);


	// > 保存
	cur_operater->saveAsExcelFile(save_path);
	cur_operater->closeSoftware();
}
/*-------------------------------------------------
		阶段 - 生成 性能测试说明内容
*/
void P_ExcelDataGenerator::generatePerformanceNotes(){

	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "性能测试说明");
	cur_operater->cell_Style_SetFontBold("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;
	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_row += 1;
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "1.性能测试是基于低配电脑的标准，在高配电脑中测试的消耗数值肯定会比低配电脑小得多。");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_grey());
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0,0,0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "范围");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "程度");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "2.插件越多，消耗的也越多。你可以减少高消耗的插件来保持游戏流畅性。");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(0));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "0.00ms - 40.00ms");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "几乎无消耗");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "3.按F2可以实时查看游戏的帧数情况，如果持续低于30帧，你就要考虑卡顿问题了。");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(1));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "40.00ms - 80.00ms");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "低消耗");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "4.所有测试的时长为20000.00ms（20秒），ms就是毫秒，1秒=1000毫秒。");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(2));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "80.00ms - 120.00ms");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "中消耗");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "5.测试结果的意思是：20秒的时间里，单个插件共占用了多少毫秒来进行计算。");

	cur_operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	cur_operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(3));
	cur_operater->cell_Style_SetAllBorder("F" + QString::number(cur_row), "H" + QString::number(cur_row), QColor(0, 0, 0));
	cur_operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "120.00ms以上");
	cur_operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "高消耗");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "6.测试结果并不是精确值，范围在给定值的10.00ms范围内波动。");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;

	cur_operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "7.另外一提，执行方式为'倍率持续'的插件，可以使得所有消耗倍数上升，插件设置值越高，消耗越大。");
	cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;
	cur_row += 1;
}
/*-------------------------------------------------
		阶段 - 生成 界面数据内容
*/
void P_ExcelDataGenerator::generatePerformanceSceneData(QString scene_name){

	// > 插件数据
	QString last_type = "";
	QString last_name = "";
	QList<C_PluginData*> plugin_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < plugin_list.count(); i++){
		C_PluginData* plugin = plugin_list.at(i);
		C_ScriptAnnotation annotation = S_InformationDataContainer::getInstance()->getAnnotation(plugin->name);
		C_ScriptHelpDetail* detail = annotation.getScriptHelpDetail();
		if (detail == nullptr){ continue; }

		// > 空类型的插件去掉
		if (annotation.getPlugindesc_type() == ""){ continue; }

		// > 不同类型隔开一下
		if (annotation.getPlugindesc_type() != last_type){
			last_type = annotation.getPlugindesc_type();
			if (annotation.getName().contains("Drill_X_") == true &&
				last_name.contains("Drill_X_") == true){
				//（如果插件之间都是扩展，则不隔开）
			}
			else{
				cur_operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
				cur_operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
				cur_row += 1;
			}
		}

		// > 单行文本写入
		cur_operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), annotation.getName());
		cur_operater->cell_SetValue("B" + QString::number(cur_row), "B" + QString::number(cur_row), annotation.getPlugindesc_type());
		cur_operater->cell_SetValue("C" + QString::number(cur_row), "C" + QString::number(cur_row), annotation.getPlugindesc_name());
		C_ScriptHelp_Performance* performance = detail->getPerformance();
		C_ScriptHelp_EffectScope* scope = detail->getEffectScope();

		// > 没有测试数据时
		if (performance == nullptr){
			cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), "无");

		}else{

			// > 特殊类型
			if (performance->working_type == "倍率持续"){
				cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), performance->working_type);
				cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), "直接影响游戏整体的运行消耗");
				cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
				cur_operater->cell_SetValue("I" + QString::number(cur_row), "I" + QString::number(cur_row), performance->time_complexity);
			}else{

				// > 数据错误情况
				double max_cost = performance->getMaxCost();
				if (max_cost == -1){
					cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), "数据错误");
					cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
				}
				else{

					// > 工作类型（持续执行/单次执行）
					cur_operater->cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), performance->working_type);

					// > 分程度（只要有一个测试值 大于5ms 就算）
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
						if (temp_cost_1 <= 5){ temp_costStr_1 = "5ms以下"; }
						if (temp_cost_2 <= 5){ temp_costStr_2 = "5ms以下"; }
						if (temp_cost_3 <= 5){ temp_costStr_3 = "5ms以下"; }
						if (temp_cost_4 <= 5){ temp_costStr_4 = "5ms以下"; }
						if (temp_cost_1 < 0){ temp_costStr_1 = "未测"; }
						if (temp_cost_2 < 0){ temp_costStr_2 = "未测"; }
						if (temp_cost_3 < 0){ temp_costStr_3 = "未测"; }
						if (temp_cost_4 < 0){ temp_costStr_4 = "未测"; }
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

						// > 不分程度（只要有一个能显示的测试值 就算）
						double temp_cost_0 = performance->getMinCost_ByLevel(scene_name, 0);
						if (temp_cost_4 > 0){ temp_cost_0 = temp_cost_4; }	//（如果四个全部小于5ms，那么就显示整个的为"5ms以下"）
						if (temp_cost_0 > 0){
							QString temp_costStr_0 = QString("  ") + QString::number(temp_cost_0) + "ms";
							if (temp_cost_0 <= 5){ temp_costStr_0 = "  5ms以下"; }
							cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), temp_costStr_0);
							cur_operater->cell_Style_SetBackground("E" + QString::number(cur_row), "E" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_0));
							cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);

							// > 都没值（说明作用域不在此处）
						}
						else{
							if (scope->isEnableScene(scene_name)){
								cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), "数据缺失");
								cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
							}
							else{
								cur_operater->cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), QString("只作用于") + scope->getEnabledScene().join("、"));
								cur_operater->cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
							}
						}
					}

					// > 时间复杂度
					cur_operater->cell_SetValue("I" + QString::number(cur_row), "I" + QString::number(cur_row), performance->time_complexity);
				}
			}
		}

		// > 边框设置+字体设置
		cur_operater->cell_Style_SetAllBorder("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
		cur_operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");

		// > 单行结束
		last_name = annotation.getName();
		cur_row += 1;
	}
}
/*-------------------------------------------------
		颜色 - 灰色
*/
QColor P_ExcelDataGenerator::getColor_grey(){
	return QColor(217, 217, 217);
}
/*-------------------------------------------------
		颜色 - 红色
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
		颜色 - 红色（根据值）
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