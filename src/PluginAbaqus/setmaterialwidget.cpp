#include "setmaterialwidget.h"
#include "ui_setmaterialwidget.h"
#include "abaqusmodel.h"
#include "meshData\meshSingleton.h"
#include "meshData\meshSet.h"
#include "QMessageBox"



SetMaterialWidget::SetMaterialWidget(ModelData::AbaqusModel* model, GUI::MainWindow* m)
	: QFDialog(m), _abaqusModel(model)
{
	ui = new Ui::SetMaterialWidget();
	ui->setupUi(this);
}

SetMaterialWidget::~SetMaterialWidget()
{
	delete ui;
}

void SetMaterialWidget::showEvent(QShowEvent *)
{
	initList();
	initData();
}

void SetMaterialWidget::initList()
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

QString SetMaterialWidget::checkData()
{
	QString strError;

	QString strName = ui->lineEdit_Name->text().trimmed();

	if (strName == "")
	{
		strError.append(tr("The Material Name is Empty."));
	}

	if (ui->comboBox_Set->currentIndex() < 0)
	{
		if (!strError.isEmpty())
		{
			strError.append("\r\n");
		}
		strError.append(tr("The Set is Empty."));
	}


	return strError;
}

void SetMaterialWidget::initData()
{
	MaterialStruct* materialStruct = _abaqusModel->getMaterialStruct();

	if (materialStruct->strMaterialName.isEmpty())
	{
		return;
	}

	ui->lineEdit_Name->setText(materialStruct->strMaterialName);
	ui->comboBox_Set->setCurrentText(materialStruct->strSetName);
	ui->lineEdit_Density->setText(materialStruct->strDensity);
	ui->lineEdit_Modulus->setText(materialStruct->strModulus);
	ui->lineEdit_Ratio->setText(materialStruct->strRatio);
}

void SetMaterialWidget::on_pushButton_OK_clicked()
{
	QString strError = checkData();
	if (strError != "")
	{
		QMessageBox::warning(this, tr("Error"), strError);
		return;
	}
	MaterialStruct* materialStruct = _abaqusModel->getMaterialStruct();

	materialStruct->strMaterialName = ui->lineEdit_Name->text();
	materialStruct->strSetName = ui->comboBox_Set->currentText();
	materialStruct->strDensity = ui->lineEdit_Density->text();
	materialStruct->strModulus = ui->lineEdit_Modulus->text();
	materialStruct->strRatio = ui->lineEdit_Ratio->text();

	this->close();
}

void SetMaterialWidget::on_pushButton_Cancel_clicked()
{
	this->close();
}

