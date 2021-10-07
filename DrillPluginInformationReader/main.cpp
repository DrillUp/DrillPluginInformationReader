#include "stdafx.h"
#include "drillplugininformationreader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// > Ö÷´°Ìå
	DrillPluginInformationReader::getInstance()->show();

	return a.exec();
}
