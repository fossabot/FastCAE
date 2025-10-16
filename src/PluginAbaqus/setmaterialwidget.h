#ifndef SETMATERIALWIDGET_H
#define SETMATERIALWIDGET_H

#include "PluginAbaqusAPI.h"
#include "SelfDefObject/QFDialog.h"

namespace Ui {class SetMaterialWidget;};

namespace ModelData
{
	class AbaqusModel;
}

namespace GUI
{
	class MainWindow;
}

class PLUGINABAQUSAPI SetMaterialWidget : public QFDialog
{
	Q_OBJECT

public:
	SetMaterialWidget(ModelData::AbaqusModel* model, GUI::MainWindow* m);
	~SetMaterialWidget();


protected:
	virtual void showEvent(QShowEvent *)override;

private:
	Ui::SetMaterialWidget *ui;
	ModelData::AbaqusModel* _abaqusModel = nullptr;
	GUI::MainWindow* _mainWindow{};

	void initList();//初始化下来列表

	QString checkData();

	void initData();//初始化数据

private slots:

	void on_pushButton_OK_clicked();
	void on_pushButton_Cancel_clicked();


};

#endif // SETMATERIALWIDGET_H
