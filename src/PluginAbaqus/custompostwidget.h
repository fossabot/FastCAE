#ifndef CUSTOMPOSTWIDGET_H
#define CUSTOMPOSTWIDGET_H

#include <QWidget>
#include "PostWidgets/PostWindowBase.h"
#include "PluginAbaqusAPI.h"

namespace Ui {class CustomPostWidget;};

namespace Post
{
	class Post3DWindow;
}
namespace ModelData
{
	class AbaqusModel;
}

class PLUGINABAQUSAPI CustomPostWidget : public Post::PostWindowBase
{
	Q_OBJECT

public:
	CustomPostWidget
		(GUI::MainWindow* mainwindow, ModelData::AbaqusModel* model, int projectid);
	~CustomPostWidget();

	void drawImage(QString fileName);

private:
	Ui::CustomPostWidget *ui;
	Post::Post3DWindow * _post3DWindow = nullptr;
	ModelData::AbaqusModel* _model = nullptr;
	int _projectID = 0;

	void initPost3D();

};

#endif // CUSTOMPOSTWIDGET_H
