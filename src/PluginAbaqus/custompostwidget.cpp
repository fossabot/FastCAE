#include "custompostwidget.h"
#include "ui_custompostwidget.h"
#include "PostWidgets\Post3DWidget.h"
#include "QFileInfo"
#include "abaqusmodel.h"


CustomPostWidget::CustomPostWidget
(GUI::MainWindow* mainwindow, ModelData::AbaqusModel* model, int projectid)
	: PostWindowBase(mainwindow, projectid, ModuleBase::Post3D, Post::D3)
	, _projectID(projectid), _model(model)
{
	ui = new Ui::CustomPostWidget();
	ui->setupUi(this);
	initPost3D();
}

CustomPostWidget::~CustomPostWidget()
{
	delete ui;
}

void CustomPostWidget::initPost3D()
{
	_post3DWindow = new Post::Post3DWindow(_mainWindow, _projectID);
	ui->verticalLayout->addWidget(_post3DWindow);
	this->appendGraphWindow(_post3DWindow);
}

void CustomPostWidget::drawImage(QString fileName)
{
	_post3DWindow->clearAll();

	QString strURL = _model->getPath() + "/vtk/" + fileName;

		QFileInfo file(strURL);
	if (file.exists())
		_post3DWindow->openFile(strURL);

	setTreeWidget(_post3DWindow->getTreeWidget());
	setPropWidget(_post3DWindow->getPropWidget());
	_toolBarList.append(_post3DWindow->getToolBars());

}

