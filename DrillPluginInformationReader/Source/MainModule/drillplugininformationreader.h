#ifndef DRILLPLUGININFORMATIONREADER_H
#define DRILLPLUGININFORMATIONREADER_H

#include <QtWidgets/QMainWindow>
#include "ui_drillplugininformationreader.h"

class DrillPluginInformationReader : public QMainWindow
{
	Q_OBJECT

public:
	DrillPluginInformationReader(QWidget *parent = 0);
	~DrillPluginInformationReader();

private:
	Ui::DrillPluginInformationReaderClass ui;
};

#endif // DRILLPLUGININFORMATIONREADER_H
