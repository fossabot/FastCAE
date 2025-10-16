#include "stepeditwidget.h"
#include "ui_stepeditwidget.h"
#include "abaqusmodel.h"
#include "stepdata.h"


StepEditWidget::StepEditWidget(ModelData::AbaqusModel* model, QDialog *parent /*= 0*/)
{
	ui = new Ui::StepEditWidget();
	ui->setupUi(this);
	_abaqusModel = model;
	init();
}

StepEditWidget::~StepEditWidget()
{
	delete ui;
}

void StepEditWidget::SetStepNameAndType(QString strName, QString strType, int index)
{
	initStepNameAndType(strName); 
	ui->label_StepType->setText(strType);
	_StepIndex = index;
}


void StepEditWidget::SetStepNameAndType(QString strName, int index)
{
	_StepIndex = index;
	initStepNameAndType(strName);
}

void StepEditWidget::initStepNameAndType(QString strName)
{
	ui->label_StepName->setText(strName);
	QHash<QString, StepData*>* stepDataHash = _abaqusModel->getStepDataHash();
	if (stepDataHash->contains(strName))
	{
		_stepData = stepDataHash->value(strName);
		ui->label_StepType->setText(_stepData->getStepTypeName());
	}

	initBasic();
	initOther();
}

void StepEditWidget::initBasic()
{
	if (_stepData == nullptr)
	{
		ui->lineEdit_FrequencyShift->setEnabled(false);
		ui->lineEdit_MinFreqency->setEnabled(false);
		ui->lineEdit_MaxFrequency->setEnabled(false);
		ui->lineEdit_BlockSizeValue->setEnabled(false);
		ui->lineEdit_MaxBlockLanczos->setEnabled(false);
	}
	else
	{
		StepBasicStruct basicStruct = _stepData->getStepBasic();

		QString strDescription = basicStruct.value_description;
		ui->lineEdit_Description->setText(strDescription);

		switch (basicStruct.radio_Eigensolver)
		{
		case StepEnumType::EigensolverType::Lanczos:
			ui->radioButton_Lanczos->setChecked(true);
			break;
		case StepEnumType::EigensolverType::Subspace:
			ui->radioButton_Subspace->setChecked(true);
			break;
		case StepEnumType::EigensolverType::AMS:
			ui->radioButton_AMS->setChecked(true);
			break;
		default:
			break;
		}

		switch (basicStruct.radio_Eigenvalues)
		{
		case StepEnumType::EigenvaluesType::AllinFrequencyRange:
			ui->radioButton_AllInFrequency->setChecked(true);
			break;
		case StepEnumType::EigenvaluesType::Value:
			ui->radioButton_Eigenvalues->setChecked(true);
			ui->lineEdit_Eigenvalues->setText(basicStruct.value_Eigenvalues);
			break;
		default:
			break;
		}

		bool ischeck = basicStruct.check_FrequencyShift;
		ui->checkBox_FrequencyShift->setChecked(ischeck);
		if (ischeck)
		{
			QString strFrequencyShift = basicStruct.value_FrequencyShift;
			ui->lineEdit_FrequencyShift->setText(strFrequencyShift);
		}

		ischeck = basicStruct.check_MinFrequency;
		ui->checkBox_MinFrequency->setChecked(ischeck);
		if (ischeck)
		{
			QString strMinFrequency = basicStruct.value_MinFrequency;
			ui->lineEdit_MinFreqency->setText(strMinFrequency);
		}

		ischeck = basicStruct.check_MaxFrequency;
		ui->checkBox_MaxFrequency->setChecked(ischeck);
		if (ischeck)
		{
			QString strMaxFrequency = basicStruct.value_MaxFrequency;
			ui->checkBox_MaxFrequency->setText(strMaxFrequency);
		}

		ischeck = basicStruct.check_IncludeAcoustic;
		ui->checkBox_IncludeAcoustic->setChecked(ischeck);

		
		switch (basicStruct.radio_BlockSize)
		{

		case StepEnumType::BlockSizeType::Default:
			ui->radioButton_BlockSizeDefault->setChecked(true);
			break;

		case StepEnumType::BlockSizeType::ValueSize:
			ui->radioButton_BlockSizeValue->setChecked(true);
			ui->lineEdit_BlockSizeValue->setText(basicStruct.value_BlockSize);
			break;
		default:
			break;
		}

		switch (basicStruct.radio_MaxBlockLanczos)
		{
		case StepEnumType::BlockSizeType::Default:
			ui->radioButton_MaxBlockLanczosDefault->setChecked(true);
			break;
		case StepEnumType::BlockSizeType::ValueSize:
			ui->radioButton_MaxBlockLanczos->setChecked(true);
			ui->lineEdit_MaxBlockLanczos->setText(basicStruct.value_MaxBlockLanczos);
			break;
		default:
			break;
		}

		ischeck = basicStruct.check_UseSIMBased;
		ui->checkBox_UseSIMbased->setChecked(ischeck);

		ischeck = basicStruct.check_IncludeResidual;
		ui->checkBox_IncludeResidual->setChecked(ischeck);

	}



}

void StepEditWidget::initOther()
{
	ui->radioButton_7->setEnabled(false);
	ui->radioButton_8->setEnabled(false);
	ui->label_28->setEnabled(false);
	ui->label_19->setEnabled(false);
	ui->lineEdit_Evaluate->setEnabled(false);

	if (nullptr == _stepData)
	{
		return;
	}

	StepOtherStruct otherStruct = _stepData->getStepOther();

	switch (otherStruct.radio_Normalize)
	{
	case StepEnumType::NormalizeType::Displacement:
		ui->radioButton_Displacement->setChecked(true);
		break;
	case StepEnumType::NormalizeType::Mass:
		ui->radioButton_Mass->setChecked(true);
		break;
	default:
		break;
	}

	bool ischeck = otherStruct.check_Evaluate;
	ui->checkBox_Evaluate->setChecked(ischeck);
	ui->lineEdit_Evaluate->setEnabled(ischeck);
	if (ischeck)
	{
		QString strEvaluate = QString ::number(otherStruct.value_Evaluate);
		ui->lineEdit_Evaluate->setText(strEvaluate);
	}
}

void StepEditWidget::init()
{
	QButtonGroup* btnGroup_1 = new QButtonGroup(this);
	btnGroup_1->setObjectName("EigensolverTypeGourp");
	btnGroup_1->addButton(ui->radioButton_Lanczos, StepEnumType::EigensolverType::Lanczos);
	btnGroup_1->addButton(ui->radioButton_Subspace, StepEnumType::EigensolverType::Subspace);
	btnGroup_1->addButton(ui->radioButton_AMS, StepEnumType::EigensolverType::AMS);
	ui->radioButton_Lanczos->setChecked(true);

	connect(btnGroup_1, SIGNAL(buttonClicked(int)), this, SLOT(radioButtonClicked_slot(int)));

	btnGroup_1 = new QButtonGroup(this);
	btnGroup_1->setObjectName("EigenvaluesTypeGourp");
	btnGroup_1->addButton(ui->radioButton_AllInFrequency, StepEnumType::EigenvaluesType::AllinFrequencyRange);
	btnGroup_1->addButton(ui->radioButton_Eigenvalues, StepEnumType::EigenvaluesType::Value);
	ui->radioButton_AllInFrequency->setChecked(true);
	connect(btnGroup_1, SIGNAL(buttonClicked(int)), this, SLOT(radioButtonClicked_slot(int)));

	btnGroup_1 = new QButtonGroup(this);
	btnGroup_1->setObjectName("BlockSizeTypeGourp");
	btnGroup_1->addButton(ui->radioButton_BlockSizeDefault, StepEnumType::BlockSizeType::Default);
	btnGroup_1->addButton(ui->radioButton_BlockSizeValue, StepEnumType::BlockSizeType::ValueSize);
	ui->radioButton_BlockSizeDefault->setChecked(true);
	connect(btnGroup_1, SIGNAL(buttonClicked(int)), this, SLOT(radioButtonClicked_slot(int)));

	btnGroup_1 = new QButtonGroup(this);
	btnGroup_1->setObjectName("BlockSizeGourp");
	btnGroup_1->addButton(ui->radioButton_MaxBlockLanczosDefault, StepEnumType::BlockSizeType::Default);
	btnGroup_1->addButton(ui->radioButton_MaxBlockLanczos, StepEnumType::BlockSizeType::ValueSize);
	ui->radioButton_MaxBlockLanczosDefault->setChecked(true);
	connect(btnGroup_1, SIGNAL(buttonClicked(int)), this, SLOT(radioButtonClicked_slot(int)));

	btnGroup_1 = new QButtonGroup(this);
	btnGroup_1->setObjectName("NormalizeGourp");
	btnGroup_1->addButton(ui->radioButton_Displacement, StepEnumType::NormalizeType::Displacement);
	btnGroup_1->addButton(ui->radioButton_Mass, StepEnumType::NormalizeType::Mass);
	ui->radioButton_Displacement->setChecked(true);

	connect(ui->checkBox_FrequencyShift, SIGNAL(stateChanged(int)), this, SLOT(checkButtonClicked_slot()));
	connect(ui->checkBox_MaxFrequency, SIGNAL(stateChanged(int)), this, SLOT(checkButtonClicked_slot()));
	connect(ui->checkBox_MinFrequency, SIGNAL(stateChanged(int)), this, SLOT(checkButtonClicked_slot()));
	connect(ui->checkBox_Evaluate, SIGNAL(stateChanged(int)), this, SLOT(checkButtonClicked_slot()));

}

void StepEditWidget::on_pushButton_OK_clicked()
{
	StepData* stepData = new StepData();
	stepData->setStepName(ui->label_StepName->text());
	stepData->setStepTypeName(ui->label_StepType->text());


	StepBasicStruct basicStruct;
	basicStruct.value_description = ui->lineEdit_Description->text();

	if (ui->radioButton_Lanczos->isChecked())
	{
		basicStruct.radio_Eigensolver = StepEnumType::EigensolverType::Lanczos;
	}
	else if (ui->radioButton_Subspace->isChecked())
	{
		basicStruct.radio_Eigensolver = StepEnumType::EigensolverType::Subspace;
	}
	else if (ui->radioButton_AMS->isChecked())
	{
		basicStruct.radio_Eigensolver = StepEnumType::EigensolverType::AMS;
	}

	if (ui->radioButton_AllInFrequency->isChecked())
	{
		basicStruct.radio_Eigenvalues = StepEnumType::EigenvaluesType::AllinFrequencyRange;
	}
	else if (ui->radioButton_Eigenvalues->isChecked())
	{
		basicStruct.radio_Eigenvalues = StepEnumType::EigenvaluesType::Value;
	}

	basicStruct.value_Eigenvalues = ui->lineEdit_Eigenvalues->text();

	basicStruct.check_FrequencyShift = ui->checkBox_FrequencyShift->isChecked();
	basicStruct.value_FrequencyShift = ui->lineEdit_FrequencyShift->text();

	basicStruct.check_MinFrequency = ui->checkBox_MinFrequency->isChecked();
	basicStruct.value_MinFrequency = ui->lineEdit_MinFreqency->text();

	basicStruct.check_MaxFrequency = ui->checkBox_MaxFrequency->isChecked();
	basicStruct.value_MaxFrequency = ui->lineEdit_MaxFrequency->text();

	basicStruct.check_IncludeAcoustic = ui->checkBox_IncludeAcoustic->isChecked();
	
	if (ui->radioButton_BlockSizeDefault->isChecked())
	{
		basicStruct.radio_BlockSize = StepEnumType::BlockSizeType::Default;

	} 
	else if (ui->radioButton_BlockSizeValue->isChecked())
	{
		basicStruct.radio_BlockSize = StepEnumType::BlockSizeType::ValueSize;
	}

	basicStruct.value_BlockSize = ui->lineEdit_BlockSizeValue->text();
	
	if (ui->radioButton_MaxBlockLanczosDefault->isChecked() )
	{
		basicStruct.radio_MaxBlockLanczos = StepEnumType::BlockSizeType::Default;

	}
	else if (ui->radioButton_MaxBlockLanczos->isChecked())
	{
		basicStruct.radio_MaxBlockLanczos = StepEnumType::BlockSizeType::ValueSize;
	}

	basicStruct.value_MaxBlockLanczos = ui->lineEdit_MaxBlockLanczos->text();

	basicStruct.check_UseSIMBased = ui->checkBox_UseSIMbased->isChecked();
	basicStruct.check_IncludeResidual = ui->checkBox_IncludeResidual->isChecked();

	StepOtherStruct otherStruct;

	if (ui->radioButton_Displacement->isChecked())
	{
		otherStruct.radio_Normalize = StepEnumType::NormalizeType::Displacement;
	}
	else if (ui->radioButton_Mass ->isChecked())
	{
		otherStruct.radio_Normalize = StepEnumType::NormalizeType::Mass;
	}

	otherStruct.check_Evaluate = ui->checkBox_Evaluate->isChecked();
	otherStruct.value_Evaluate = ui->lineEdit_Evaluate->text().toDouble();

	stepData->setStepBasic(basicStruct);
	stepData->setStepOther(otherStruct);

	QList<QString>* listStepName = _abaqusModel->getStepNameList();
	if (!listStepName->contains(stepData->getStepName()))
	{
		int count = listStepName->count();
		if (_StepIndex >= count)
		{
			listStepName->append(stepData->getStepName());
		}
		else
		{
			listStepName->insert(_StepIndex, stepData->getStepName());
		}
	}

	QHash<QString, StepData*>* stepDataHash = _abaqusModel->getStepDataHash();
	stepDataHash->insert(stepData->getStepName(), stepData);

	this->close();
}

void StepEditWidget::on_pushButton_Cancel_clicked()
{
	this->close();
}

void StepEditWidget::radioButtonClicked_slot(int id)
{
	QButtonGroup* group = static_cast<QButtonGroup*>(sender());
	QString name = group->objectName();
	if (name.contains("EigensolverTypeGourp"))
	{
	}
	else if (name.contains("EigenvaluesTypeGourp"))
	{
		bool ischeck = id == StepEnumType::EigenvaluesType::Value;
		ui->lineEdit_Eigenvalues->setEnabled(ischeck);
	}
	else if (name.contains("BlockSizeTypeGourp"))
	{
		bool ischeck = id == StepEnumType::BlockSizeType::ValueSize;
		ui->lineEdit_BlockSizeValue->setEnabled(ischeck);
	}
	else if (name.contains("BlockSizeGourp"))
	{
		bool ischeck = id == StepEnumType::BlockSizeType::ValueSize;
		ui->lineEdit_MaxBlockLanczos->setEnabled(ischeck);
	}

}

void StepEditWidget::checkButtonClicked_slot()
{
	QCheckBox* checkBox = static_cast<QCheckBox*>(sender());
	QString strName = checkBox->objectName();
	bool ischeck = checkBox->isChecked();
	if (strName.contains("checkBox_FrequencyShift"))
	{
		ui->lineEdit_FrequencyShift->setEnabled(ischeck);
	}
	else if (strName.contains("checkBox_MinFrequency"))
	{
		ui->lineEdit_MinFreqency->setEnabled(ischeck);
	}
	else if (strName.contains("checkBox_MaxFrequency"))
	{
		ui->lineEdit_MaxFrequency->setEnabled(ischeck);
	}
	else if (strName.contains("checkBox_Evaluate"))
	{
		ui->lineEdit_Evaluate->setEnabled(ischeck);
	}
}

