#ifndef BCCREATEWIDGET_H
#define BCCREATEWIDGET_H

#include "PluginAbaqusAPI.h"
#include "SelfDefObject/QFDialog.h"

namespace Ui {class BCCreateWidget;};


namespace ModelData
{
	class AbaqusModel;
}

class QListWidgetItem;

namespace GUI
{
	class MainWindow;
}


class PLUGINABAQUSAPI BCCreateWidget : public QFDialog
{
	Q_OBJECT

public:
	BCCreateWidget(ModelData::AbaqusModel* model,GUI::MainWindow* m);
	~BCCreateWidget();

protected:
	virtual void showEvent(QShowEvent *)override;

private:
	Ui::BCCreateWidget *ui;
	ModelData::AbaqusModel* _abaqusModel = nullptr;
	GUI::MainWindow* _mainWindow{};

	void init();//初始化
	void initConnect();//初始化信号槽
	void initRadio();//初始化单选按钮
	void initMechanical(int stepType);//初始化力学
	void initElectrical();//初始化电气
	void initOther(int stepType);//初始化其他
	void initStep();//初始化分析步
	void initSet();//初始化组件
	void initList();//初始化列表
	QString checkData();//数据校验
	void openEditWidget(QString strBCNanme, QString strStepName, QString strSetName, QString strBCTypeName);//打开编辑界面

private slots:

	void radioCheck_slot(bool b);
	void bcListDoublcClick_slot(QListWidgetItem *item);

	void on_pushButton_Continue_clicked();
	void on_pushButton_Cancle_clicked();

};

#endif // BCCREATEWIDGET_H
