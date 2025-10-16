#include "bccreatewidget.h"
#include "ui_bccreatewidget.h"
#include "abaqusmodel.h"
#include "meshData\meshSingleton.h"
#include "meshData\meshSet.h"
#include "QMessageBox"
#include "bceditwidget.h"


BCCreateWidget::BCCreateWidget(ModelData::AbaqusModel* model, GUI::MainWindow* m)
	: QFDialog(m), _mainWindow(m), _abaqusModel(model)
{
	ui = new Ui::BCCreateWidget();
	ui->setupUi(this);
	init();
}

BCCreateWidget::~BCCreateWidget()
{
	delete ui;
}

void BCCreateWidget::showEvent(QShowEvent *)
{
	initList();
	initStep();
	initSet();
}

void BCCreateWidget::init()
{
	ui->tabWidget->tabBar()->hide();
	initMechanical(1);
	initElectrical();
	initOther(1);
	initRadio();
	initConnect();
}

void BCCreateWidget::initConnect()
{
	connect(ui->radioButton_Mechanical, SIGNAL(clicked(bool)), this, SLOT(radioCheck_slot(bool)));
	connect(ui->radioButton_Fluid, SIGNAL(clicked(bool)), this, SLOT(radioCheck_slot(bool)));
	connect(ui->radioButton_Electrical, SIGNAL(clicked(bool)), this, SLOT(radioCheck_slot(bool)));
	connect(ui->radioButton_Other, SIGNAL(clicked(bool)), this, SLOT(radioCheck_slot(bool)));

	connect(ui->listWidget_BCList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(bcListDoublcClick_slot(QListWidgetItem *)));

	
}

void BCCreateWidget::initRadio()
{
	ui->radioButton_Fluid->setEnabled(false);
}

void BCCreateWidget::initMechanical(int stepType)
{

	QStringList list;

	switch (stepType)
	{
	case 1:
		list 
			<< "Symmetry/Antisymmetry/Encastre"
			<< "Displacement/Rotation"
			<< "Velocity/Angular velocity"
			<< "Acceleration/Angular acceleration"
			<< "Connector displacement"
			<< "Connector velocity"
			<< "Connector acceleration";
		break;
	case 2:
		list 
			<< "Symmetry/Antisymmetry/Encastre"
			<< "Displacement/Rotation"
			<< "Connector displacement"
			<< "Secondary base";
		break;
	default:
		break;
	}

	ui->listWidget_Mechanical->clear();
	ui->listWidget_Mechanical->addItems(list);
}

void BCCreateWidget::initElectrical()
{
	QStringList list;

	list << tr("Electric potential");

	ui->listWidget_Electrical->clear();
	ui->listWidget_Electrical->addItems(list);

}

void BCCreateWidget::initOther(int stepType)
{
	QStringList list;

	switch (stepType)
	{
	case 1:
		list<< tr("Temperature")
			<< tr("Pore pressure")
			<< tr("Fluid cavity pressure")
			<< tr("Mass concentration")
			<< tr("Acoustic pressure")
			<< tr("Connector material flow");
		break;
	case 2:
		list << tr("Fluid cavity pressure")
			<< tr("Acoustic pressure")
			<< tr("Connector material flow");
		break;
	default:
		break;
	}
	ui->listWidget_Other->clear();
	ui->listWidget_Other->addItems(list);

}

void BCCreateWidget::initStep()
{
	QList<QString>* listStepName = _abaqusModel->getStepNameList();
	ui->comboBox_Step->clear();
	ui->comboBox_Step->addItem(tr("Initial"));
	ui->comboBox_Step->addItems(*listStepName);
}

void BCCreateWidget::initSet()
{
	QList<int> list_Mesh = _abaqusModel->getMeshSetList();

	if (list_Mesh.count() == 0)
	{
		return;
	}

	MeshData::MeshData* md = MeshData::MeshData::getInstance();
	ui->comboBox_Set->clear();
	for (int i = 0; i < list_Mesh.size(); i++)
	{
		MeshData::MeshSet* set = md->getMeshSetAt(i);
		QString str = set->getName();
		ui->comboBox_Set->addItem(str);
	}
}

void BCCreateWidget::initList()
{
	QHash<QString, BCData*>* bcDataHash = _abaqusModel->getBcDataHash();
	QList<QString> bcNameList = bcDataHash->keys();

	ui->listWidget_BCList->clear();
	ui->listWidget_BCList->addItems(bcNameList);

}

QString BCCreateWidget::checkData()
{
	QString strError;
	QString strBCName = ui->lineEdit_BCName->text().trimmed();
	if (strBCName.isEmpty())
	{
		if (!strError.isEmpty())
		{
			strError.append("\r\n");
		}
		strError.append(tr("The BC Name is Empty."));

	}
	int index = ui->comboBox_Set->currentIndex();
	if (index < 0)
	{
		if (!strError.isEmpty())
		{
			strError.append("\r\n");
		}
		strError.append(tr("The Set is Empty."));
	}

	return strError;
}

void BCCreateWidget::openEditWidget(QString strBCNanme, QString strStepName, QString strSetName, QString strBCTypeName)
{
	//Displacement/Rotation
	//Symmetry/Antisymmetry/Encastre
	if (strBCTypeName.contains("Symmetry/Antisymmetry/Encastre")||
		strBCTypeName.contains("Displacement/Rotation")
		)
	{
		this->hide();
		BCEditWidget bcEditWidget(_abaqusModel);
		bcEditWidget.initDataValue(strBCNanme, strStepName, strSetName, strBCTypeName);
		bcEditWidget.exec();
		this->close();
	}
	else
	{
		QMessageBox::warning(this, tr("Error"), tr("Function not implemented"));
	}
}

void BCCreateWidget::radioCheck_slot(bool b)
{
	if (b)
	{
		QString senderName = sender()->objectName();
		if (ui->radioButton_Mechanical->objectName() == senderName)
		{
			ui->tabWidget->setCurrentIndex(0);
		}
		else if (ui->radioButton_Fluid->objectName() == senderName)
		{
			ui->tabWidget->setCurrentIndex(1);
		}
		else if (ui->radioButton_Electrical->objectName() == senderName)
		{
			ui->tabWidget->setCurrentIndex(2);
		}
		else if (ui->radioButton_Other->objectName() == senderName)
		{
			ui->tabWidget->setCurrentIndex(3);
		}

	}
}

void BCCreateWidget::bcListDoublcClick_slot(QListWidgetItem *item)
{

	QString strBCName = item->text();

	BCData* bcData = _abaqusModel->getBcDataHash()->value(strBCName);
	
	openEditWidget(bcData->getBCName(), bcData->getStepName(), bcData->getSetName(),bcData->getBcType());
}

void BCCreateWidget::on_pushButton_Continue_clicked()
{

	QString strError = checkData();
	if (!strError.isEmpty())
	{
		QMessageBox::warning(this, tr("Error"), strError);
		return;
	}

	QString strBCName = ui->lineEdit_BCName->text().trimmed();
	QString strStepName = ui->comboBox_Step->currentText();
	QString strSetName = ui->comboBox_Set->currentText();
	QString strBCTypeName;

	if (ui->radioButton_Mechanical->isChecked())
	{
		strBCTypeName = ui->listWidget_Mechanical->currentItem()->text();
	}
	else if (ui->radioButton_Fluid->isChecked())
	{
		strBCTypeName = ui->listWidget_Fluid->currentItem()->text();
	}
	else if (ui->radioButton_Electrical->isChecked())
	{
		strBCTypeName = ui->listWidget_Electrical->currentItem()->text();
	}
	else if (ui->radioButton_Other->isChecked())
	{
		strBCTypeName = ui->listWidget_Other->currentItem()->text();
	}


	openEditWidget(strBCName, strStepName, strSetName, strBCTypeName);

}

void BCCreateWidget::on_pushButton_Cancle_clicked()
{
	this->close();
}

