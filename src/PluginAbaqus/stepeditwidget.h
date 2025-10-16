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

	void initStepNameAndType(QString strName);//初始化分析步骤名称类型
	void initBasic();//初始化基础界面
	void initOther();//初始化其他界面
	void init();
private slots:
	void on_pushButton_OK_clicked();//保存数据
	void on_pushButton_Cancel_clicked();//取消
	void radioButtonClicked_slot(int);//单选信号槽
	void checkButtonClicked_slot();//复选信号槽

};

#endif // STEPEDITWIDGET_H
