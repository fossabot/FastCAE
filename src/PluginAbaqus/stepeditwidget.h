#ifndef STEPEDITWIDGET_H
#define STEPEDITWIDGET_H

#include <QDialog>
namespace Ui {class StepEditWidget;};

namespace ModelData
{
	class AbaqusModel;
}

class StepData;

class StepEditWidget : public QDialog
{
	Q_OBJECT

public:
	StepEditWidget(ModelData::AbaqusModel* model, QDialog *parent = 0);
	~StepEditWidget();

	void SetStepNameAndType(QString strName,QString strType,int index);

	void SetStepNameAndType(QString strName, int index);


private:
	Ui::StepEditWidget *ui;
	ModelData::AbaqusModel* _abaqusModel = nullptr;
	StepData* _stepData = nullptr;
	int _StepIndex = 0;

	void initStepNameAndType(QString strName);//��ʼ������������������
	void initBasic();//��ʼ����������
	void initOther();//��ʼ����������
	void init();
private slots:
	void on_pushButton_OK_clicked();//��������
	void on_pushButton_Cancel_clicked();//ȡ��
	void radioButtonClicked_slot(int);//��ѡ�źŲ�
	void checkButtonClicked_slot();//��ѡ�źŲ�

};

#endif // STEPEDITWIDGET_H
