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

	void init();//��ʼ��
	void initConnect();//��ʼ���źŲ�
	void initRadio();//��ʼ����ѡ��ť
	void initMechanical(int stepType);//��ʼ����ѧ
	void initElectrical();//��ʼ������
	void initOther(int stepType);//��ʼ������
	void initStep();//��ʼ��������
	void initSet();//��ʼ�����
	void initList();//��ʼ���б�
	QString checkData();//����У��
	void openEditWidget(QString strBCNanme, QString strStepName, QString strSetName, QString strBCTypeName);//�򿪱༭����

private slots:

	void radioCheck_slot(bool b);
	void bcListDoublcClick_slot(QListWidgetItem *item);

	void on_pushButton_Continue_clicked();
	void on_pushButton_Cancle_clicked();

};

#endif // BCCREATEWIDGET_H
