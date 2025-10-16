#ifndef ABAQUSMODEL_H
#define ABAQUSMODEL_H

#include "PluginAbaqusAPI.h"
#include "ModelData/modelDataBaseExtend.h"
#include "stepdata.h"
#include "bcdata.h"

struct MaterialStruct
{
	QString strMaterialName = "";
	QString strSetName = "";
	QString strDensity = "";
	QString strModulus = "";
	QString strRatio = "";
};

namespace ModelData
{



	class PLUGINABAQUSAPI AbaqusModel :public ModelDataBaseExtend
	{
	public:
		AbaqusModel(ProjectTreeType t);
		~AbaqusModel();

		QHash<QString, StepData*>* getStepDataHash() const { return _stepDataHash; }
		QHash<QString, BCData*>* getBcDataHash() const { return _bcDataHash; }
		QList<QString>* getStepNameList() const { return _stepNameList; }
		MaterialStruct* getMaterialStruct() const { return _materialStruct; }
	private:
		QList<QString>* _stepNameList = nullptr;
		QHash<QString, StepData*>* _stepDataHash = nullptr;
		QHash<QString, BCData*>* _bcDataHash = nullptr;
		MaterialStruct* _materialStruct = nullptr;

	protected:
		QDomElement& writeToProjectFile(QDomDocument* doc, QDomElement* ele) override;
		void readDataFromProjectFile(QDomElement* e) override;
	private:
		void writeStepNameList(QDomDocument* doc, QDomElement* ele);
		void writeMaterialStruct(QDomDocument* doc, QDomElement* ele);
		void writeStepDataHash(QDomDocument* doc, QDomElement* ele);
		void writeBCDataHash(QDomDocument* doc, QDomElement* ele);

		void clearStepDataHash();
		void clearBCDataHash();



	};
}
#endif // ABAQUSMODEL_H
