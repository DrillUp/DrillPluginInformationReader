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
		生成器 - 生成 插件清单
*/
void P_ExcelDataGenerator::generatePluginDataList(QString save_path){

	// > 打开
	P_ExcelOperater operater = P_ExcelOperater();
	operater.openSoftware();
	operater.newExcelFile();

	// > 表头
	operater.cell_FreezePanes_OnlyRow();
	operater.cell_SetWidth(2, 30);
	operater.cell_Style_SetBackground_Row(1, this->getColor_grey());
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
				operater.cell_MergeCells("A" + QString::number(cur_row), "F" + QString::number(cur_row), true);
				operater.cell_Style_SetBackground("A" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_grey());
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
		operater.cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), author_text);
		operater.cell_SetValue("B" + QString::number(cur_row), "B" + QString::number(cur_row), annotation.getName());
		operater.cell_SetValue("C" + QString::number(cur_row), "C" + QString::number(cur_row), annotation.getPlugindesc_type());
		operater.cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), annotation.getPlugindesc_name());
		operater.cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), src_text);
		operater.cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), docs_text);

		// > 单行样式设置
		if (annotation.getAuthor().indexOf("Drill_up") == 0 ){	//（名为Drill_up开头的插件允许自动换行）
			operater.cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), true);
		}else{
			operater.cell_SetWrapText("A" + QString::number(cur_row), "A" + QString::number(cur_row), false);
		}
		operater.cell_SetWrapText("E" + QString::number(cur_row), "E" + QString::number(cur_row), true);
		operater.cell_SetWrapText("F" + QString::number(cur_row), "F" + QString::number(cur_row), true);
		operater.cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");

		// > 单行结束
		last_name = annotation.getName();
		cur_row += 1;
	}

	// > 最后一行包裹
	operater.cell_MergeCells("A" + QString::number(cur_row), "F" + QString::number(cur_row), true);
	operater.cell_Style_SetBackground("A" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_grey());
	cur_row += 1;

	// > 保存
	operater.saveAsExcelFile(save_path);
	operater.closeSoftware();
}



/*-------------------------------------------------
		生成器 - 生成 性能测试统计表
*/
void P_ExcelDataGenerator::generatePerformanceDataList(QString save_path){

	// > 打开
	P_ExcelOperater operater = P_ExcelOperater();
	operater.openSoftware();
	operater.newExcelFile();

	// > 表头
	operater.cell_FreezePanes_OnlyRow();
	operater.cell_SetWidth(2, 30);
	operater.cell_Style_SetBackground_Row(1, this->getColor_grey());
	operater.cell_Style_SetFontBold_Row(1, true);
	operater.cell_Style_SetFontFamily_Row(1, "微软雅黑");
	operater.cell_SetWidth(1, 36);
	operater.cell_SetWidth(2, 9);
	operater.cell_SetWidth(3, 28);
	operater.cell_SetWidth(4, 10);
	operater.cell_SetWidth(5, 10);
	operater.cell_SetWidth(6, 10);
	operater.cell_SetWidth(7, 10);
	operater.cell_SetWidth(8, 10);
	operater.cell_SetWidth(9, 32);
	operater.cell_SetValue("A1", "A1", "插件名");
	operater.cell_SetValue("B1", "B1", "插件类型");
	operater.cell_SetValue("C1", "C1", "中文名");
	operater.cell_SetValue("D1", "D1", "工作类型");
	operater.cell_SetValue("E1", "E1", "200个事件");
	operater.cell_SetValue("F1", "F1", "100个事件");
	operater.cell_SetValue("G1", "G1", "50个事件");
	operater.cell_SetValue("H1", "H1", "20个事件");
	operater.cell_SetValue("I1", "I1", "时间复杂度");

	// > 插件数据
	QString last_type = "";
	QString last_name = "";
	this->cur_row = 2;

	// > 性能测试说明
	this->generatePerformanceNotes(&operater);

	// > 地图界面栏
	operater.cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	operater.cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	operater.cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "地图界面");
	operater.cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;

	// > 插件数据
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
				operater.cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
				operater.cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
				cur_row += 1;
			}
		}

		// > 单行文本写入
		operater.cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), annotation.getName());
		operater.cell_SetValue("B" + QString::number(cur_row), "B" + QString::number(cur_row), annotation.getPlugindesc_type());
		operater.cell_SetValue("C" + QString::number(cur_row), "C" + QString::number(cur_row), annotation.getPlugindesc_name());
		C_ScriptHelp_Performance* performance = detail->getPerformance();
		if (performance == nullptr){
			operater.cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), "无");
			operater.cell_SetValue("E" + QString::number(cur_row), "H" + QString::number(cur_row), "无");
			operater.cell_SetValue("I" + QString::number(cur_row), "I" + QString::number(cur_row), "无");
		}else{
			operater.cell_SetValue("D" + QString::number(cur_row), "D" + QString::number(cur_row), performance->working_type);

			// > 分程度
			double temp_cost_4 = performance->getMaxCost_ByLevel(4);
			if (temp_cost_4 > 0){
				double temp_cost_1 = performance->getMaxCost_ByLevel(1);
				double temp_cost_2 = performance->getMaxCost_ByLevel(2);
				double temp_cost_3 = performance->getMaxCost_ByLevel(3);
				double temp_cost_4 = performance->getMaxCost_ByLevel(4);
				operater.cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), QString::number(temp_cost_4) + "ms");
				operater.cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), QString::number(temp_cost_3) + "ms");
				operater.cell_SetValue("G" + QString::number(cur_row), "G" + QString::number(cur_row), QString::number(temp_cost_2) + "ms");
				operater.cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), QString::number(temp_cost_1) + "ms");
				operater.cell_Style_SetBackground("E" + QString::number(cur_row), "E" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_4));
				operater.cell_Style_SetBackground("F" + QString::number(cur_row), "F" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_3));
				operater.cell_Style_SetBackground("G" + QString::number(cur_row), "G" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_2));
				operater.cell_Style_SetBackground("H" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_1));
				
			}else{
				// > 不分程度
				double temp_cost_0 = performance->getMaxCost_ByLevel(0);
				if (temp_cost_0 > 0){
					operater.cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), QString("  ") + QString::number(temp_cost_0) + "ms");
					operater.cell_Style_SetBackground("E" + QString::number(cur_row), "E" + QString::number(cur_row), this->getColor_ByCriticalValue(temp_cost_0));
					operater.cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
				}else{
					operater.cell_SetValue("E" + QString::number(cur_row), "E" + QString::number(cur_row), "数据错误");
					operater.cell_MergeCells("E" + QString::number(cur_row), "H" + QString::number(cur_row), true);
				}
			}
			operater.cell_SetValue("I" + QString::number(cur_row), "I" + QString::number(cur_row), performance->time_complexity);
		}
		operater.cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");

		// > 单行结束
		last_name = annotation.getName();
		cur_row += 1;
	}

	// > 保存
	operater.saveAsExcelFile(save_path);
	operater.closeSoftware();
}
/*-------------------------------------------------
		阶段 - 生成 性能测试说明内容
*/
void P_ExcelDataGenerator::generatePerformanceNotes(P_ExcelOperater* operater){

	operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "性能测试说明");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;
	operater->cell_MergeCells("A" + QString::number(cur_row), "I" + QString::number(cur_row), true);
	operater->cell_Style_SetBackground("A" + QString::number(cur_row), "I" + QString::number(cur_row), this->getColor_grey());
	cur_row += 1;
	cur_row += 1;


	operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "1.性能测试是基于低配电脑的标准，在高配电脑中测试的消耗数值肯定会比低配电脑小得多。");

	operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_grey());
	operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "范围");
	operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "程度");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "2.插件越多，消耗的也越多。你可以减少高消耗的插件来保持游戏流畅性。");

	operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(0));
	operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "0.00ms - 40.00ms");
	operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "几乎无消耗");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "3.按F2可以实时查看游戏的帧数情况，如果持续低于30帧，你就要考虑卡顿问题了。");

	operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(1));
	operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "40.00ms - 80.00ms");
	operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "低消耗");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "4.所有测试的时长为20000.00ms（20秒），ms就是毫秒，1秒=1000毫秒。");

	operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(2));
	operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "80.00ms - 120.00ms");
	operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "中消耗");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "5.测试结果的意思是：20秒的时间里，单个插件共占用了多少毫秒来进行计算。");

	operater->cell_MergeCells("F" + QString::number(cur_row), "G" + QString::number(cur_row), true);
	operater->cell_Style_SetBackground("F" + QString::number(cur_row), "H" + QString::number(cur_row), this->getColor_ByCritical(3));
	operater->cell_SetValue("F" + QString::number(cur_row), "F" + QString::number(cur_row), "120.00ms以上");
	operater->cell_SetValue("H" + QString::number(cur_row), "H" + QString::number(cur_row), "高消耗");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;


	operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "6.测试结果并不是精确值，范围在给定值的10.00ms范围内波动。");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;

	operater->cell_MergeCells("A" + QString::number(cur_row), "E" + QString::number(cur_row), true);
	operater->cell_SetValue("A" + QString::number(cur_row), "A" + QString::number(cur_row), "7.另外一提，变速齿轮可以使得所有消耗爆炸式上升，设置速度越快，消耗越大。");
	operater->cell_Style_SetFontFamily_Row(cur_row, "微软雅黑");
	cur_row += 1;
	cur_row += 1;
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