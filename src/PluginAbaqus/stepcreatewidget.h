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
	void initStepList();//��ʼ���������б�
	void initProcedure();//��ʼ���������б�
	void initGeneral();//��ʼ��ͨ�������б�
	void initLinearPerturbation();//��ʼ�������㶯�б�
	void initConnect();//��ʼ���źŲ�

	QString checkDataValue();

private slots:

	void comboBoxTypeChange_slot(const QString&);
	void bcListDoublcClick_slot(QListWidgetItem *item);


	void on_pushButton_Continue_clicked();
	void on_pushButton_Cancel_clicked();

};

#endif // STEPCREATEWIDGET_H
