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

		//����Ҽ��¼�
		virtual void contextMenu(QMenu* menu) override;
		//�����������¼�
		virtual void singleClicked() override;
		//������˫���¼�
		virtual void doubleClicked() override;
		//������
		virtual void createTree(QTreeWidgetItem* root, GUI::MainWindow* mainwindow) override;
		//������������
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
