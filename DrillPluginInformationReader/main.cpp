#include "stdafx.h"
#include "drillplugininformationreader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DrillPluginInformationReader w;
	w.show();
	return a.exec();
}
