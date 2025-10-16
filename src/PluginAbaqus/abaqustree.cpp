#include "abaqustree.h"
#include "mainWindow/mainWindow.h"
#include "QTreeWidget"
#include "ModelData/modelDataBase.h"
#include "QDebug"

#include "bccreatewidget.h"
#include "stepcreatewidget.h"
#include "setmaterialwidget.h"
#include "abaqusmodel.h"
#include "inpwritemanager.h"
#include "QProcess"
#include "QMenu"
#include "QDir"
#include "custompostwidget.h"

ProjectTree::AbaqusTree::AbaqusTree(GUI::MainWindow* m)
	:ProjectTreeWithBasicNode(m)
{
	qDebug() << "  AbaqusTree  ";
	connect(_mainWindow, SIGNAL(closePostWindowSig(Post::PostWindowBase*)), this, SLOT(close3DPostWindow(Post::PostWindowBase*)));

}

ProjectTree::AbaqusTree::~AbaqusTree()
{

}

void ProjectTree::AbaqusTree::initBasicNode(QTreeWidgetItem* root)
{
	ProjectTreeWithBasicNode::initBasicNode(root);

	disableItems();

	QTreeWidgetItem* stepCreateWidgetitem = 
		new QTreeWidgetItem(_simulationSettingItem, TreeItemType::SelfDefineItem);
	stepCreateWidgetitem->setText(0, tr("StepCreate"));
	stepCreateWidgetitem->setData(0, Qt::UserRole + 2, StepCreate);

	QTreeWidgetItem* setMaterialtitem = 
		new QTreeWidgetItem(_simulationSettingItem, TreeItemType::SelfDefineItem);
	setMaterialtitem->setText(0, tr("SetMaterial"));
	setMaterialtitem->setData(0, Qt::UserRole + 2, MaterialWidget);

	_customVectortitem = new QTreeWidgetItem(_root, TreeItemType::SelfDefineItem);
	_customVectortitem->setText(0, tr("Vector"));
	_customVectortitem->setData(0, Qt::UserRole + 2, CustomVector);



}

void ProjectTree::AbaqusTree::contextMenu(QMenu* menu)
{
	qDebug() << _name << "  Right click";

	QAction* action = nullptr;
	TreeItemType type = (TreeItemType)_currentItem->type();
	int index = _currentItem->data(0, Qt::UserRole + 2).toInt();
	switch (type)
	{
	case ProjectBoundaryCondation:
		break;
	case SelfDefineItem:
		if (index ==  CustomVector)
		{
			action = menu->addAction(tr("Refresh"));
			connect(action, SIGNAL(triggered()), this, SLOT(refresh_slot()));
		}

		break;
	default:
		ProjectTreeWithBasicNode::contextMenu(menu);
	}

}

void ProjectTree::AbaqusTree::singleClicked()
{
	this->getCurrentItemData();

	qDebug() << _name << "  single click";

	TreeItemType type = (TreeItemType)_currentItem->type();
	int index = _currentItem->data(0, Qt::UserRole + 2).toInt();

	if (StepCreate == index)
	{
		ModelData::AbaqusModel* model = static_cast<ModelData::AbaqusModel*>(_data);
		StepCreateWidget stepCreate(model, _mainWindow);
		stepCreate.exec();
	}
	else if (MaterialWidget == index)
	{
		ModelData::AbaqusModel* model = static_cast<ModelData::AbaqusModel*>(_data);
		SetMaterialWidget materialWidget(model, _mainWindow);
		materialWidget.exec();
	}
	else if (ProjectBoundaryCondation == type)
	{
		ModelData::AbaqusModel* model = static_cast<ModelData::AbaqusModel*>(_data);
		BCCreateWidget bCCreate(model, _mainWindow);
		bCCreate.exec();
	}
	else if (PostWindow == index)
	{
		QString strName = _currentItem->text(0);

		if (_customPostWidget == nullptr)
		{
			ModelData::AbaqusModel* model = static_cast<ModelData::AbaqusModel*>(_data);
			_customPostWidget = new CustomPostWidget(_mainWindow, model, model->getID());
		}
		_customPostWidget->drawImage(strName);
		emit openPostWindowSig(_customPostWidget);
		emit showPostWindowInfo(_data->getID(), Post::PostWindowType::D3);
	}
	else
	{
		ProjectTreeWithBasicNode::singleClicked();
	}

}

void ProjectTree::AbaqusTree::doubleClicked()
{
	qDebug() << _name << "  double click";

	ProjectTreeWithBasicNode::doubleClicked();
}

void ProjectTree::AbaqusTree::createTree(QTreeWidgetItem* root, GUI::MainWindow* mainwindow)
{
	ProjectTreeBase::createTree(root, mainwindow);
	//**********对配置节点进行操作***********



	//***************
}

void ProjectTree::AbaqusTree::updateMeshSubTree()
{
	////add here********

	/////************

	ProjectTreeWithBasicNode::updateMeshSubTree();

}

void ProjectTree::AbaqusTree::reTranslate()
{



	ProjectTreeWithBasicNode::reTranslate();
}

void ProjectTree::AbaqusTree::updateTree()
{
	ProjectTreeWithBasicNode::updateTree();
}

void ProjectTree::AbaqusTree::close3DPostWindow(Post::PostWindowBase* base)
{
	//if (base == _customPostWidget)
	//{
	//	delete _customPostWidget;
	//	_customPostWidget = nullptr;
	//}
}

void ProjectTree::AbaqusTree::disableItems()
{
	QStringList disableList;
	disableList << "Monitor"
		<< "Vector"
		<< "Boundary Type"
		<< "Solver Setting"
		<<"Post";

	setDisableItems(disableList);
}

void ProjectTree::AbaqusTree::refresh_slot()
{
	ModelData::AbaqusModel* model = static_cast<ModelData::AbaqusModel*>(_data);
	QString strURL = model->getPath() + "/vtk";

	QDir dir(strURL);

	if (!dir.exists())

		return ;

	QStringList nameFilters;

	nameFilters << "*.vtu";

	QStringList listFiles = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);


	int count = listFiles.count();
	_customVectortitem->takeChildren();
	for (int i = 0; i < count; i++)
	{
		QTreeWidgetItem* postWindowitem = 
			new QTreeWidgetItem(_customVectortitem, TreeItemType::ProjectPostCounterChild);
		postWindowitem->setText(0, listFiles.at(i));
		postWindowitem->setData(0, Qt::UserRole + 2, PostWindow);
	}

}

