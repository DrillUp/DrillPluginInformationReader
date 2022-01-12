#include "stdafx.h"
#include "drillplugininformationreader.h"
#include "Source/MainModule/firstTip/w_SoftwareFirstTip.h"
#include "Source/ProjectModule/storageGlobal/s_IniManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// > 主窗体
	DrillPluginInformationReader::getInstance()->show();

	// > 首页提示
	if (S_IniManager::getInstance()->getConfig("PIR_NoMoreFirstTip") != "true"){
		W_SoftwareFirstTip::getInstance()->show();
	}

	return a.exec();
}
