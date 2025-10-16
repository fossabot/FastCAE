#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "ui_testwidget.h"

class TestWidget : public QWidget
{
	Q_OBJECT

public:
	TestWidget(QWidget *parent = 0);
	~TestWidget();

private:
	Ui::TestWidget ui;
};

#endif // TESTWIDGET_H
