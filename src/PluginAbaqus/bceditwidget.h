#ifndef BCEDITWIDGET_H
#define BCEDITWIDGET_H

#include <QDialog>

namespace Ui {class BCEditWidget;};

namespace ModelData
{
	class AbaqusModel;
}

class QButtonGroup;

class BCEditWidget : public QDialog
{
	Q_OBJECT

public:
	BCEditWidget(ModelData::AbaqusModel* model, QDialog *parent = 0);
	~BCEditWidget();

	void initDataValue(QString strBCNanme,QString strStepName,QString strSetName,QString strBCTypeName);

private:
	Ui::BCEditWidget *ui;
	ModelData::AbaqusModel* _abaqusModel = nullptr;
	QButtonGroup* _group = nullptr;


	void init();//��ʼ��
	void initRadioGroup();//��ʼ����Ԫ��
	void initModelData();//��ʼ������
private slots:
	void on_pushButton_OK_clicked();
	void on_pushButton_Cancel_clicked();

};

#endif // BCEDITWIDGET_H
