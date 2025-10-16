#ifndef ODB2VTKCONFIG_H
#define ODB2VTKCONFIG_H

#include "QFile"
#include "QTextStream"
#include "PluginAbaqusAPI.h"

namespace ModelData
{
	class AbaqusModel;
}


class PLUGINABAQUSAPI ODB2VTKConfig
{
public:
	ODB2VTKConfig(ModelData::AbaqusModel* model);
	~ODB2VTKConfig();

	void writeConfig(QString fileUrl);

private:
	
	ModelData::AbaqusModel* _abaqusModel = nullptr;


	void initPath(QTextStream* out);
	void initMesh(QTextStream* out);
	void initPartition(QTextStream* out);
	void initSetting(QTextStream* out);
	void initOutput(QTextStream* out);
	void initMultiprocessing(QTextStream* out);
	void initScale(QTextStream* out);

};

#endif // ODB2VTKCONFIG_H
