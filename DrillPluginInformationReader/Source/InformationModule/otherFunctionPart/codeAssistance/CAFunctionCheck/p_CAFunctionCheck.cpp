#include "stdafx.h"
#include "p_CAFunctionCheck.h"

#include "Source/RmmvInteractiveModule/custom/s_InformationDataContainer.h"
#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/RmmvInteractiveModule/base/s_RmmvDataContainer.h"
#include "Source/PluginModule/storageData/s_PluginDataContainer.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelpDetail.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Src.h"
#include "Source/PluginModule/scriptReader/helpDetail/c_ScriptHelp_Docs.h"

#include "Source/Utils/operater/excelOperater/p_ExcelOperater.h"
#include "Source/Utils/common/TTool.h"

/*
-----==========================================================-----
		类：		函数校验器.cpp
		作者：		drill_up
		所属模块：	信息模块
		
		主功能：	生成自定义的Excel表格格式。
-----==========================================================-----
*/
P_CAFunctionCheck::P_CAFunctionCheck(QObject *parent)
	: QObject(parent)
{
}

P_CAFunctionCheck::~P_CAFunctionCheck(){
}


/*-------------------------------------------------
		生成器 - 生成 函数文本
*/
QString P_CAFunctionCheck::generateFunctionCheckData(){
	QString result;

	QList<C_PluginData*> plugin_list = S_PluginDataContainer::getInstance()->getPluginDataTank();
	for (int i = 0; i < plugin_list.count(); i++){
		C_PluginData* plugin = plugin_list.at(i); 
		result.append("=================================");
		result.append("\n");
		result.append(plugin->name);
		result.append("\n");

		QFileInfo fileinfo = S_RmmvDataContainer::getInstance()->getRmmvFile_Plugin(plugin->name);

		// > 读取工程文件
		QFile plugin_file(fileinfo.absoluteFilePath());
		if (!plugin_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(nullptr, "错误", "无法打开文件：" + fileinfo.absoluteFilePath(), QMessageBox::Yes);
			continue;
		}
		QString plugin_context = plugin_file.readAll();
		plugin_file.close();

		// > 读取基本信息
		P_TxtFastReader reader = P_TxtFastReader(plugin_context);

		int i_first = 0;
		while (true)
		{
			i_first = reader.d_indexOf(QRegExp("^var[^=]*=[^=]*\\.prototype\\."), i_first+1);
			if (i_first == -1){ break; }

			QString code_var = reader.d_rowAt(i_first);
			QString code_function = reader.d_rowAt(i_first+1);

			// > 全显示
			//result.append(code_var);
			//result.append("\n");
			//result.append(code_function);
			//result.append("\n");

			QRegExp re("[\\w]+\\.prototype\\.[\\w]+");
			int i_var = code_var.indexOf(re);
			QString matched_var = re.cap(0);
			int i_function = code_function.indexOf(re);
			QString matched_function = re.cap(0);

			// > 排列位置不正确的
			if (i_var == -1 || i_function == -1){
				result.append(code_var);
				result.append("\n");
				result.append(code_function);
				result.append("\n");
			}
			
			// > 显示错误的
			if (matched_var != matched_function){
				result.append(code_var);
				result.append("\n");
				result.append(code_function);
				result.append("\n");
			}

		}
	}

	return result;
}


