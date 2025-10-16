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

		//加载插件
		bool install() override;
		//卸载插件
		bool uninstall() override;
		//翻译
		void reTranslate(QString lang) override;
	private:
		GUI::MainWindow* _mainwindow{};

	};
}

extern "C"
{
	//插件注册
	void PLUGINABAQUSAPI Register
		(GUI::MainWindow* m, QList<Plugins::PluginBase*>* plugs);

	//创建数据类
	bool PLUGINABAQUSAPI CreateModel(int t, QPair<int, ModelData::ModelDataBase*>* );

	//创建树
	bool PLUGINABAQUSAPI CreateTree
		(int, GUI::MainWindow* m, QPair<int, ProjectTree::ProjectTreeBase*>*);

	//求解器文件写出
	bool PLUGINABAQUSAPI WriteOut(QString path, ModelData::ModelDataBase* d);

	//网格导入方法  
	bool PLUGINABAQUSAPI importMeshFun(QString filename);
}


#endif // PLUGINABAQUS_H
