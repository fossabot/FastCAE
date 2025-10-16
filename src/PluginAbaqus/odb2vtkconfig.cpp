#include "odb2vtkconfig.h"
#include "abaqusmodel.h"


ODB2VTKConfig::ODB2VTKConfig(ModelData::AbaqusModel* model)
	:_abaqusModel(model)
{

}

ODB2VTKConfig::~ODB2VTKConfig()
{

}

void ODB2VTKConfig::writeConfig(QString fileUrl)
{
	QFile  myfile(fileUrl);
	if (myfile.open(QFile::WriteOnly | QFile::Truncate))
	{
		QTextStream out(&myfile);
		initPath(&out);
		initMesh(&out);
		initPartition(&out);
		initSetting(&out);
		initOutput(&out);
		initMultiprocessing(&out);
		initScale(&out);
	}
	myfile.close();
}

void ODB2VTKConfig::initPath(QTextStream* out)
{
	QString strOdbPath = _abaqusModel->getPath();
	QString strVtkPath = strOdbPath + "/vtk";

	*out << "------------input and output path------------" << "\r\n";
	*out << QString("odb_path = '%1'").arg(strOdbPath) << "\r\n";
	*out << "odb_name = 'input'" << "\r\n";
	*out << QString("vtk_path = '%1'").arg(strVtkPath) << "\r\n";

}

void ODB2VTKConfig::initMesh(QTextStream* out)
{
	*out << "----------------type of mesh-----------------" << "\r\n";
	*out << "mesh_type = 'Tetrahedron'" << "\r\n";
}

void ODB2VTKConfig::initPartition(QTextStream* out)
{
	*out << "---------------partition type----------------" << "\r\n";
	*out << "partition_method = 'Regular'" << "\r\n";
	*out << "-------------partition parameter-------------" << "\r\n";
	*out << "partition_parameter = '1,1,1'" << "\r\n";
}

void ODB2VTKConfig::initSetting(QTextStream* out)
{
	*out << "------setting frame, step and instance-------" << "\r\n";
	*out << "frame = '0-30'" << "\r\n";
	*out << "step = '0'" << "\r\n";
	*out << "instance = '0'" << "\r\n";
}

void ODB2VTKConfig::initOutput(QTextStream* out)
{
	*out << "---------------Output variables--------------" << "\r\n";
	*out << "scalar = ' '" << "\r\n";
	*out << "vector = 'U'" << "\r\n";
	*out << "tensor = ' '" << "\r\n";
}

void ODB2VTKConfig::initMultiprocessing(QTextStream* out)
{
	*out << "-----------multiprocessing setting-----------" << "\r\n";
	*out << "parallel partition = 'FALSE'" << "\r\n";
	*out << "processing number = '1'" << "\r\n";
	*out << "parallel read variable and write vtk= 'FALSE'" << "\r\n";
	*out << "processing number = '1'" << "\r\n";
}

void ODB2VTKConfig::initScale(QTextStream* out)
{
	*out << "---------------------------------------------" << "\r\n";
	*out << "scale_zoom = '100'" << "\r\n";
}
