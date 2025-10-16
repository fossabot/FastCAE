#ifndef PLUGINABAQUS_H
#define PLUGINABAQUS_H

#include "PluginAbaqusAPI.h"
#include "PluginManager\pluginBase.h"
#include <QObject>

namespace GUI
{
	class MainWindow;
}

namespace ProjectTree
{
	class ProjectTreeBase;
}

namespace ModelData
{
	class ModelDataBase;
}

namespace Plugins
{

	class PLUGINABAQUSAPI PluginAbaqus : public PluginBase
	{
		Q_OBJECT
	public:
		PluginAbaqus(GUI::MainWindow* m);
		~PluginAbaqus();

		//���ز��
		bool install() override;
		//ж�ز��
		bool uninstall() override;
		//����
		void reTranslate(QString lang) override;
	private:
		GUI::MainWindow* _mainwindow{};

	};
}

extern "C"
{
	//���ע��
	void PLUGINABAQUSAPI Register
		(GUI::MainWindow* m, QList<Plugins::PluginBase*>* plugs);

	//����������
	bool PLUGINABAQUSAPI CreateModel(int t, QPair<int, ModelData::ModelDataBase*>* );

	//������
	bool PLUGINABAQUSAPI CreateTree
		(int, GUI::MainWindow* m, QPair<int, ProjectTree::ProjectTreeBase*>*);

	//������ļ�д��
	bool PLUGINABAQUSAPI WriteOut(QString path, ModelData::ModelDataBase* d);

	//�����뷽��  
	bool PLUGINABAQUSAPI importMeshFun(QString filename);
}


#endif // PLUGINABAQUS_H
