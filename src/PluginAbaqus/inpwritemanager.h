#ifndef INPWRITEMANAGER_H
#define INPWRITEMANAGER_H


#include "QFile"
#include "QTextStream"
#include "PluginAbaqusAPI.h"

namespace ModelData
{
	class AbaqusModel;
}
class BCData;

class PLUGINABAQUSAPI InpWriteManager
{
public:
	InpWriteManager(ModelData::AbaqusModel* model);
	~InpWriteManager();
	void writeInit(QString fileURL);//根据Abaqus格式生成inp文件
private:

	ModelData::AbaqusModel* _abaqusModel = nullptr;

	void writeHeading(QTextStream* out);
	void writePart(QTextStream* out);
	void writeNode(QTextStream* out);
	void writeElement(QTextStream* out);
	void writeNset(QTextStream* out, QString strSetName, bool isInstance);
	void writeSection(QTextStream* out);
	void writeAssembly(QTextStream* out);
	void writeMaterial(QTextStream* out);
	void writeStep(QTextStream* out);
	void writeBC(QTextStream* out, QString strStepName);
	void writeOutput(QTextStream* out);

	void writeDisplacement(QTextStream* out,BCData* bcData);
	void writeSymmetry(QTextStream* out, BCData* bcData);


};

#endif // INPWRITEMANAGER_H
