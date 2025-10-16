#ifndef ABAQUSTREE_H
#define ABAQUSTREE_H

#include "ProjectTree/ProjectTreeWithBasicNode.h"
#include "PluginAbaqusAPI.h"


namespace GUI
{
	class MainWindow;
}

class CustomPostWidget;

namespace ProjectTree
{

	enum TreeCustomItemType
	{
		none,
		StepCreate,
		MaterialWidget,
		BCCreate,
		CustomVector,
		PostWindow,
	};


	class PLUGINABAQUSAPI AbaqusTree : public ProjectTreeWithBasicNode
	{
		Q_OBJECT
	public:
		AbaqusTree(GUI::MainWindow* m);
		~AbaqusTree();

	protected:

		virtual void initBasicNode(QTreeWidgetItem* root) override;

		//鼠标右键事件
		virtual void contextMenu(QMenu* menu) override;
		//鼠标左键单击事件
		virtual void singleClicked() override;
		//鼠标左键双击事件
		virtual void doubleClicked() override;
		//创建树
		virtual void createTree(QTreeWidgetItem* root, GUI::MainWindow* mainwindow) override;
		//更新网格子树
		virtual void updateMeshSubTree() override;

		virtual void reTranslate() override;

		virtual void updateTree() override;
	private:

		void disableItems();

		CustomPostWidget* _customPostWidget = nullptr;
		QTreeWidgetItem* _customVectortitem{};
	private slots:
		void refresh_slot();
		void close3DPostWindow(Post::PostWindowBase*);


	};
}
#endif // ABAQUSTREE_H
