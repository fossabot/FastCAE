#include "bceditwidget.h"
#include "ui_bceditwidget.h"
#include "abaqusmodel.h"
#include "bcdata.h"


BCEditWidget::BCEditWidget(ModelData::AbaqusModel* model, QDialog *parent)
	: QDialog(parent)
{
	ui = new Ui::BCEditWidget();
	ui->setupUi(this);
	_abaqusModel = model;
	init();
}

BCEditWidget::~BCEditWidget()
{
	delete ui;
	if (_group)
	{
		delete _group;
	}
}

void BCEditWidget::initDataValue(QString strBCNanme, QString strStepName, QString strSetName, QString strBCTypeName)
{
	ui->label_BCName->setText(strBCNanme);
	ui->label_TypeName->setText(strBCTypeName);
	ui->label_StepName->setText(strStepName);
	ui->label_RegionName->setText(strSetName);

	if (strBCTypeName.contains("Displacement/Rotation"))
	{
		ui->tabWidget->setCurrentIndex(0);
	}
	else if (strBCTypeName.contains("Symmetry/Antisymmetry/Encastre"))
	{
		ui->tabWidget->setCurrentIndex(1);
	}

	initModelData();
}


void BCEditWidget::init()
{
	initRadioGroup();
	ui->tabWidget->tabBar()->hide();
}

void BCEditWidget::initRadioGroup()
{
	_group = new QButtonGroup(this);
	_group->addButton(ui->radioButton_XSYMM, BCEnumType::SymmetryType::XSYMM);
	_group->addButton(ui->radioButton_YSYMM, BCEnumType::SymmetryType::YSYMM);
	_group->addButton(ui->radioButton_ZSYMM, BCEnumType::SymmetryType::ZSYMM);
	_group->addButton(ui->radioButton_XASSYMM, BCEnumType::SymmetryType::XASYMM);
	_group->addButton(ui->radioButton_YASSYMM, BCEnumType::SymmetryType::YASYMM);
	_group->addButton(ui->radioButton_ZASSYMM, BCEnumType::SymmetryType::ZASYMM);
	_group->addButton(ui->radioButton_PINNED, BCEnumType::SymmetryType::PINNED);
	_group->addButton(ui->radioButton_ENCASTRE, BCEnumType::SymmetryType::ENCASTRE);

	ui->radioButton_XSYMM->setChecked(true);

}

void BCEditWidget::initModelData()
{
	QHash<QString, BCData*>* bcDataHash = _abaqusModel->getBcDataHash();

	QString strBCName = ui->label_BCName->text();
	if (bcDataHash->contains(strBCName))
	{
		BCData*bcData = bcDataHash->value(strBCName);
		if (bcData->getBcType().contains("Displacement/Rotation"))
		{
			DisplacementStruct displacement = bcData->getDisplacement();

			ui->checkBox_U1->setChecked(displacement.bU1);
			ui->checkBox_U2->setChecked(displacement.bU2);
			ui->checkBox_U3->setChecked(displacement.bU3);
			ui->checkBox_UR1->setChecked(displacement.bUR1);
			ui->checkBox_UR2->setChecked(displacement.bUR2);
			ui->checkBox_UR3->setChecked(displacement.bUR3);

		}
		else if (ui->label_TypeName->text().contains("Symmetry/Antisymmetry/Encastre"))
		{
			switch (bcData->getSymmetryType())
			{
			case BCEnumType::SymmetryType::XSYMM:
				ui->radioButton_XSYMM->setChecked(true);
				break;
			case BCEnumType::SymmetryType::YSYMM:
				ui->radioButton_YSYMM->setChecked(true);
					break;
			case BCEnumType::SymmetryType::ZSYMM:
				ui->radioButton_ZSYMM->setChecked(true);
					break;
			case BCEnumType::SymmetryType::XASYMM:
				ui->radioButton_XASSYMM->setChecked(true);
					break;
			case BCEnumType::SymmetryType::YASYMM:
				ui->radioButton_YASSYMM->setChecked(true);
					break;
			case BCEnumType::SymmetryType::ZASYMM:
				ui->radioButton_ZASSYMM->setChecked(true);
					break;
			case BCEnumType::SymmetryType::PINNED:
				ui->radioButton_PINNED->setChecked(true);
					break;
			case BCEnumType::SymmetryType::ENCASTRE:
				ui->radioButton_ENCASTRE->setChecked(true);
					break;
			default:
				break;
			}

		}
	}
}

void BCEditWidget::on_pushButton_OK_clicked()
{
	QHash<QString, BCData*>* bcDataHash = _abaqusModel->getBcDataHash();
	BCData* bcData = nullptr;
	QString bcName = ui->label_BCName->text();
	if (bcDataHash->contains(bcName))
	{
		bcData = bcDataHash->value(bcName);
	}
	else
	{
		bcData = new BCData();
		bcDataHash->insert(bcName, bcData);
	}

	bcData->setBCName(ui->label_BCName->text());
	bcData->setStepName(ui->label_StepName->text());
	bcData->setSetName(ui->label_RegionName->text());

	if (ui->label_TypeName->text().contains("Displacement/Rotation")
		)
	{
		bcData->setBcType("Displacement/Rotation");
		DisplacementStruct displacement;
		displacement.bU1 = ui->checkBox_U1->isChecked();
		displacement.bU2 = ui->checkBox_U2->isChecked();
		displacement.bU3 = ui->checkBox_U3->isChecked();
		displacement.bUR1 = ui->checkBox_UR1->isChecked();
		displacement.bUR2 = ui->checkBox_UR2->isChecked();
		displacement.bUR3 = ui->checkBox_UR3->isChecked();
		bcData->setDisplacement(displacement);
	}
	else if (ui->label_TypeName->text().contains("Symmetry/Antisymmetry/Encastre")
		)
	{
		bcData->setBcType("Symmetry/Antisymmetry/Encastre");
		bcData->setSymmetryType(static_cast<BCEnumType::SymmetryType>(_group->checkedId()));
	}
	this->close();
}

void BCEditWidget::on_pushButton_Cancel_clicked()
{
	this->close();
}

