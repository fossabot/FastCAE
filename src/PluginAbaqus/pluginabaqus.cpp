#include "pluginabaqus.h"
#include "mainWindow/mainWindow.h"
#include "ModelData/modelDataFactory.h"
#include "ModelData/modelDataSingleton.h"
#include "ModelData/modelDataBase.h"
#include "MainWidgets/ProjectTreeFactory.h"
#include "abaqustree.h"
#include "PluginAbaqus\abaqusmodel.h"
#include "IO/IOConfig.h"
#include "qDebug"
#include "inpwritemanager.h"
#include "QProcess"
#include "odb2vtkconfig.h"
#include "QDir"
#include "QCoreApplication"
#include <QApplication>
#include <QTranslator>
#include <assert.h>



Plugins::PluginAbaqus::PluginAbaqus(GUI::MainWindow* m)
{
	_mainwindow = m;
	_describe = " Abaqus plugin ";
}

Plugins::PluginAbaqus::~PluginAbaqus()
{

}

bool Plugins::PluginAbaqus::install()
{

	ModelData::ModelDataFactory::registerType(PluginDefType + 101, "PluginAbaqus", CreateModel);
	MainWidget::ProjectTreeFactory::registerType(PluginDefType + 101, CreateTree);
	IO::IOConfigure::RegisterInputFile("inp", WriteOut);
	IO::IOConfigure::RegisterMeshImporter("inp", importMeshFun);

	return true;
}

bool Plugins::PluginAbaqus::uninstall()
{
	ModelData::ModelDataFactory::removeType(PluginDefType + 101);
	MainWidget::ProjectTreeFactory::removeType(PluginDefType + 101);
	IO::IOConfigure::RemoveInputFile("inp");
	IO::IOConfigure::RemoveMeshImporter("inp");

	return true;
}

void Plugins::PluginAbaqus::reTranslate(QString lang)
{
	auto app = static_cast<QApplication*>(QCoreApplication::instance());
	app->removeTranslator(_translator);
	if (lang.toLower() == "chinese")
	{
		bool ok = _translator->load("://translation/pluginabaqus_zh");
		assert(ok);
		app->installTranslator(_translator);
	}
}

void Register(GUI::MainWindow* m, QList<Plugins::PluginBase*>* plugs)
{

	Plugins::PluginBase * p = new Plugins::PluginAbaqus(m);
	plugs->append(p);

}

bool CreateModel(int t, QPair<int, ModelData::ModelDataBase*>* p)
{

	if (t == ProjectTreeType::PluginDefType + 101)
	{
		auto m = new ModelData::AbaqusModel((ProjectTreeType)t);
		p->first = t;
		p->second = m;
		return true;
	}
	return false;
}


bool CreateTree(int tp, GUI::MainWindow* m, QPair<int, ProjectTree::ProjectTreeBase*>* t)
{
	if (tp == PluginDefType + 101)
	{
		t->first = tp;
		t->second = new ProjectTree::AbaqusTree(m);
		return true;
	}
	return false;
}


bool  WriteOut(QString path, ModelData::ModelDataBase* d)
{
	qDebug() << d->getName();
	qDebug() << "writeTest";

	ModelData::AbaqusModel* model = static_cast<ModelData::AbaqusModel*>(d);

	QString strURL = model->getPath() + "/input.inp";
	InpWriteManager inp(model);
	inp.writeInit(strURL);

	strURL = model->getPath() + "/ODB2VTK+.cfg";
	ODB2VTKConfig cfg(model);
	cfg.writeConfig(strURL);

	QString sourcePath = QCoreApplication::applicationDirPath() + "/../Solve";
	QString sourceFile = sourcePath + "/ODB2VTK+.py";
	QString targetFile = model->getPath() + "/ODB2VTK+.py";
	QFile file(sourceFile);

	if (file.exists())
	{
		QFile::copy(sourceFile, targetFile);
	}

	QString strVtkUrl = model->getPath() + "/vtk";
	QDir dir;
	if (!dir.exists(strVtkUrl))
	{
		dir.mkpath(strVtkUrl);
	}

	return true;
}

bool importMeshFun(QString)
{
	return true;
}