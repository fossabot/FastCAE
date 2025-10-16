#include "stepcreatewidget.h"
#include "ui_stepcreatewidget.h"
#include "abaqusmodel.h"
#include "QMessageBox"
#include "stepeditwidget.h"

StepCreateWidget::StepCreateWidget(ModelData::AbaqusModel* model, GUI::MainWindow* m)
	: QFDialog(m), _abaqusModel(model)
{

	ui = new Ui::StepCreateWidget();
	ui->setupUi(this);

	init();
}

StepCreateWidget::~StepCreateWidget()
{
	delete ui;
}

void StepCreateWidget::showEvent(QShowEvent *)
{
	initStepList();
}

void StepCreateWidget::init()
{
	ui->tabWidget->tabBar()->hide();
	initConnect();
	connect(ui->listWidget_Step, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(bcListDoublcClick_slot(QListWidgetItem *)));
	initProcedure();
	initGeneral();
	initLinearPerturbation();
}

void StepCreateWidget::initStepList()
{
	ui->listWidget_Step->clear();
	ui->listWidget_Step->addItem(tr("Initial"));
	QList<QString>* listData = _abaqusModel->getStepNameList();
	ui->listWidget_Step->addItems(*listData);
	ui->listWidget_Step->setCurrentRow(0);
}

void StepCreateWidget::initProcedure()
{
	ui->comboBox_type->clear();
	QStringList list;
	list 
		/*<< tr("General")*/ //通用
		<< tr("Linear perturbation"); //线性摄动
	ui->comboBox_type->addItems(list);

}

void StepCreateWidget::initGeneral()
{
	QStringList list;
	list<< "Coupled temp-displacement"
		<< "Coupled thermal-electrical-structural"
		<< "Direct cyclic"
		<< "Geostatic"					
		<< "Soils"								
		<< "Static, General"					
		<< "Visco";								
	ui->listWidget_General->clear();
	ui->listWidget_General->addItems(list);
	ui->listWidget_General->setCurrentRow(0);

}

void StepCreateWidget::initLinearPerturbation()
{
	QStringList list;
	list /*<< "Buckle"*/  //屈曲
		<< "Frequency"  //频率
/*		<< "Static, Linear perturbation"  //静力,线性摄动
		<< "Steady-state dynamics, Direct"  //稳态动力学,直接
		<< "Substructure generation" */;//子结构生成

	//列表中可扩展多个分析类型.每个类型可再扩展详细参数设定,本案例仅提供频率做演示

	ui->listWidget_LinearPerturbation->clear();
	ui->listWidget_LinearPerturbation->addItems(list);
	ui->listWidget_LinearPerturbation->setCurrentRow(0);

}

void StepCreateWidget::initConnect()
{
	connect(ui->comboBox_type, SIGNAL(currentTextChanged(const QString&)), this, SLOT(comboBoxTypeChange_slot(const QString&)));
}

QString StepCreateWidget::checkDataValue()
{
	QString strError;
	QString strStepName = ui->lineEdit_StepName->text().trimmed();
	
	if (strStepName == "")
	{
		strError.append(tr("The Step Name is Empty."));
	}
	return strError;
}

void StepCreateWidget::comboBoxTypeChange_slot(const QString& strText)
{
	if (strText.contains(tr("General")))
	{
		ui->tabWidget->setCurrentIndex(0);
	}
	else if (strText.contains(tr("Linear perturbation")))
	{
		ui->tabWidget->setCurrentIndex(1);
	}
}

void StepCreateWidget::bcListDoublcClick_slot(QListWidgetItem *item)
{
	int index = ui->listWidget_Step->currentRow();
	if (index <= 0)
	{
		return;
	}
	StepEditWidget stepEditWidget(_abaqusModel);
	QString strStepName = ui->listWidget_Step->currentItem()->text();
	stepEditWidget.SetStepNameAndType(strStepName, index);
	this->hide();
	stepEditWidget.exec();
	this->close();
}

void StepCreateWidget::on_pushButton_Continue_clicked()
{
	QString strError = checkDataValue();
	if (strError != "")
	{
		QMessageBox::warning(this, tr("Error"), strError);
		return;
	}

	QString strStepName = ui->lineEdit_StepName->text();

	QString strProcedureType = ui->comboBox_type->currentText();

	QString strStepType;


	if (strProcedureType.contains(tr("General")))
	{
		strStepType = ui->listWidget_General->currentItem()->text();
	}
	else
	{
		strStepType = ui->listWidget_LinearPerturbation->currentItem()->text();
	}

	StepEditWidget stepEditWidget(_abaqusModel);
	int index = ui->listWidget_Step->currentRow();
	stepEditWidget.SetStepNameAndType(strStepName, strStepType, index);
	this->hide();
	stepEditWidget.exec();
	this->close();

}

void StepCreateWidget::on_pushButton_Cancel_clicked()
{
	this->close();
}

