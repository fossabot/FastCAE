#ifndef STEPCREATEWIDGET_H
#define STEPCREATEWIDGET_H

#include "PluginAbaqusAPI.h"
#include "SelfDefObject/QFDialog.h"

namespace Ui {class StepCreateWidget;};

namespace ModelData
{
	class AbaqusModel;
}

namespace GUI
{
	class MainWindow;
}

class QListWidgetItem;

class PLUGINABAQUSAPI StepCreateWidget : public QFDialog
{
	Q_OBJECT

public:
	StepCreateWidget(ModelData::AbaqusModel* model, GUI::MainWindow* m);
	~StepCreateWidget();


protected:
	virtual void showEvent(QShowEvent *)override;

private:
	Ui::StepCreateWidget *ui;
	ModelData::AbaqusModel * _abaqusModel = nullptr;
	GUI::MainWindow* _mainWindow{};

	void init();
	void initStepList();//初始化分析步列表
	void initProcedure();//初始化下拉框列表
	void initGeneral();//初始化通用类型列表
	void initLinearPerturbation();//初始化线性摄动列表
	void initConnect();//初始化信号槽

	QString checkDataValue();

private slots:

	void comboBoxTypeChange_slot(const QString&);
	void bcListDoublcClick_slot(QListWidgetItem *item);


	void on_pushButton_Continue_clicked();
	void on_pushButton_Cancel_clicked();

};

#endif // STEPCREATEWIDGET_H
