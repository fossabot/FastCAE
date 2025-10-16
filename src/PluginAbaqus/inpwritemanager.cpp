#include "inpwritemanager.h"
#include "meshData\meshSingleton.h"
#include "meshData\meshSet.h"
#include "vtkDataSet.h"
#include "vtkCell.h"
#include "meshData\setMember.h"
#include "Material\MaterialSingletion.h"
#include "Material\Material.h"
#include "abaqusmodel.h"
#include "meshData\meshKernal.h"

InpWriteManager::InpWriteManager(ModelData::AbaqusModel* model)
	: _abaqusModel(model)
{

}

InpWriteManager::~InpWriteManager()
{

}

void InpWriteManager::writeInit(QString fileURL)
{
	QFile  myfile(fileURL);
	if (myfile.open(QFile::WriteOnly | QFile::Truncate))
	{
		QTextStream out(&myfile);
		writeHeading(&out);
		writePart(&out);
		writeAssembly(&out);
		writeMaterial(&out);
		writeStep(&out);
	}
	myfile.close();
}

void InpWriteManager::writeHeading(QTextStream* out)
{
	*out << "*Heading" << "\r\n";
	*out << " Frequency analysis of a coupling" << "\r\n";
	*out << "*Preprint, echo=NO, model=NO, history=NO, contact=NO" << "\r\n";
}

void InpWriteManager::writePart(QTextStream* out)
{
	*out << "*Part, name=" << _abaqusModel->getName()<< "\r\n";
	writeNode(out);
	writeElement(out);

	MaterialStruct* materialStruct = _abaqusModel->getMaterialStruct();
	writeNset(out, materialStruct->strSetName, false);
	writeSection(out);

	*out << "*End Part" << "\r\n";
}

void InpWriteManager::writeNode(QTextStream* out)
{
	MeshData::MeshData* md = MeshData::MeshData::getInstance();
	if (md->getKernalCount() == 0)
	{
		return;
	}
	MeshData::MeshKernal* kernal= md->getKernalAt(0);
	if (kernal != nullptr)
	{
		*out << "*Node" << "\r\n";
		int count = kernal->getPointCount();
		for (int i = 0; i < count; i++)
		{
			double* coor = kernal->getPointAt(i);

			int pointIndex = i;
			QString strCoor0 = QString::number(coor[0], 'f', 11);
			QString strCoor1 = QString::number(coor[1], 'f', 11);
			QString strCoor2 = QString::number(coor[2], 'f', 11);

			QString s = QString("%1,%2,%3,%4")
				.arg(pointIndex + 1, 7, 10, QLatin1Char(' '))
				.arg(strCoor0, 17, QLatin1Char(' '))
				.arg(strCoor1, 17, QLatin1Char(' '))
				.arg(strCoor2, 17, QLatin1Char(' '));

			*out << s << "\r\n";
		}
	}
}

void InpWriteManager::writeElement(QTextStream* out)
{
	MeshData::MeshData* md = MeshData::MeshData::getInstance();
	if (md->getKernalCount() == 0)
	{
		return;
	}
	MeshData::MeshKernal* kernal = md->getKernalAt(0);
	if (kernal != nullptr)
	{

		*out << "*Element, type=C3D4" << "\r\n";
		int iCellCount = kernal->getCellCount();

		for (int i = 0; i < iCellCount; i++)
		{
			vtkCell* cell = kernal->getCellAt(i);
			vtkIdList* ids = cell->GetPointIds();
			const int n = ids->GetNumberOfIds();

			QString strTmp = "";
			strTmp.append(QString("%1").arg(i + 1, 7, 10, QLatin1Char(' ')));
			for (int j = 0; j < n; ++j)
			{
				int id = ids->GetId(j);
				strTmp.append(QString(",%1").arg(id+1, 7, 10, QLatin1Char(' ')));
			}
			*out << strTmp << "\r\n";
		}
	}
}

void InpWriteManager::writeNset(QTextStream* out, QString strSetName , bool isInstance)
{
	QList<int> setList = _abaqusModel->getMeshSetList();
	int iCount = setList.count();
	MeshData::MeshData* md = MeshData::MeshData::getInstance();

	MeshData::MeshSet* msNSet = nullptr;
	MeshData::MeshSet* msElset = nullptr;

	for (int i = 0; i < iCount; i++)
	{
		int index = setList.at(i);
		MeshData::MeshSet* ms = md->getMeshSetByID(index);
		if (ms->getName() == strSetName && ms->getSetType() == MeshData::SetType::Node)
		{
			msNSet = ms;
		}
		if (ms->getName() == strSetName && ms->getSetType() == MeshData::SetType::Element)
		{
			msElset = ms;
		}
	}

	if (msNSet != nullptr)
	{
		//vtkIdTypeArray* memids = msNSet->getIDList();
		int listvalue = msNSet->getKernals().at(0);
		QList<int> listKernals = msNSet->getKernalMembers(listvalue);

		const int n = listKernals.count();
		if (isInstance)
		{
			*out << "*Nset, nset=" << msNSet->getName() << " , instance=coupling-1" << "\r\n";
			QString str;
			for (int i = 0; i < n; ++i)
			{
				int id = listKernals.at(i);
				if ((i + 1) % 16 == 0)
				{
					str.append("\r\n");
				}
				else if (str != "")
				{
					str.append(",");
				}
				str.append(QString("%1").arg(id + 1));
			}
			*out << str << "\r\n";

		}
		else 
		{
			*out << "*Nset, nset=" << msNSet->getName() << " , generate " << "\r\n";
			int idStart = listKernals.at(0) + 1;
			int idEnd = listKernals.at(n - 1) + 1;
			if (idStart > idEnd)
			{
				int itemp = idStart;
				idStart = idEnd;
				idEnd = itemp;
			}

			*out << QString("%1,%2,1").arg(idStart).arg(idEnd) << "\r\n";
		}


	}
	if (msElset != nullptr)
	{
		//vtkIdTypeArray* memids = msElset->getIDList();
		//const int n = memids->GetNumberOfValues();

		int listvalue = msElset->getKernals().at(0);
		QList<int> listKernals = msElset->getKernalMembers(listvalue);
		const int n = listKernals.count();


		if (isInstance)
		{
			*out << "*Elset, elset=" << msElset->getName() << ", instance=coupling-1" << "\r\n";
			QString str;
			for (int i = 0; i < n; ++i)
			{
				int id = listKernals.at(i);
				if ((i + 1) % 16 == 0)
				{
					str.append("\r\n");
				}
				else if (str != "")
				{
					str.append(",");
				}
				str.append(QString("%1").arg(id + 1));
			}
			*out << str << "\r\n";
		}
		else
		{
			*out << "*Elset, elset=" << msElset->getName() << " , generate " << "\r\n";


			int idStart = listKernals.at(0) + 1;
			int idEnd = listKernals.at(n - 1) + 1;
			if (idStart > idEnd)
			{
				int itemp = idStart;
				idStart = idEnd;
				idEnd = itemp;
			}

			*out << QString("%1,%2,1").arg(idStart).arg(idEnd) << "\r\n";
		}

	}
}

void InpWriteManager::writeSection(QTextStream* out)
{
	MaterialStruct* materialStruct = _abaqusModel->getMaterialStruct();
	*out << "** Section: Section-coupling" <<"\r\n";
	*out << "*Solid Section , elset=" << 
		materialStruct->strSetName
		<< ", material= "<< materialStruct->strMaterialName
		<<		
		"\r\n";
	*out << "," << "\r\n";

}

void InpWriteManager::writeAssembly(QTextStream* out)
{

	*out << "** " << "\r\n";
	*out << "** " << "\r\n";
	*out << "** ASSEMBLY" << "\r\n";
	*out << "** " << "\r\n";
	*out << "*Assembly, name=Assembly" << "\r\n";
	*out << "**  " << "\r\n";
	*out << "*Instance, name=coupling-1, part=" << _abaqusModel->getName() << "\r\n";
	*out << "*End Instance " << "\r\n";
	*out << "** " << "\r\n";

	QHash<QString, BCData*>* bcDataHash = _abaqusModel->getBcDataHash();
	QList<BCData*> list = bcDataHash->values();
	int count = list.count();
	for (int i = 0; i < count;i++)
	{
		BCData* bcData = list.at(i);
		writeNset(out, bcData->getSetName(),true);
	}
	*out << "*End Assembly" << "\r\n";


}

void InpWriteManager::writeMaterial(QTextStream* out)
{

	MaterialStruct* materialStruct = _abaqusModel->getMaterialStruct();

	*out << "** " << "\r\n";
	*out << "** MATERIALS" << "\r\n";
	*out << "** " << "\r\n";
	*out << "*Material, name=" << materialStruct->strMaterialName << "\r\n";
	*out << "*Density " << "\r\n";
	*out << materialStruct->strDensity <<" , "<< "\r\n";
	*out << "*Elastic " << "\r\n";
	*out << materialStruct->strModulus << "," << materialStruct->strRatio << "\r\n";

}

void InpWriteManager::writeStep(QTextStream* out)
{
	*out << "** ----------------------------------------------------------------" << "\r\n";

	QHash<QString, StepData*>* stepDataHash = _abaqusModel->getStepDataHash();
	QList<StepData*> list = stepDataHash->values();
	int count = list.count();
	for (int i = 0; i < count; i++)
	{
		StepData* stepData = list.at(i);

		if (stepData->getStepTypeName().contains("Frequency"))
		{
			*out << "** " << "\r\n";
			*out << "** STEP: " << stepData->getStepName() <<"\r\n";
			*out << "** " << "\r\n";
			*out << "*Step, name=" << stepData->getStepName() 
				<< ", nlgeom=NO, perturbation " << "\r\n";
			
			StepBasicStruct stepBasicStruct = stepData->getStepBasic();
			StepOtherStruct stepOtherStruct = stepData->getStepOther();

			*out << stepBasicStruct.value_description << "\r\n";

			QString strEigensolver;
			switch (stepBasicStruct.radio_Eigensolver)
			{
			case StepEnumType::EigensolverType::Lanczos:
				strEigensolver = "Lanczos";
				break;
			case StepEnumType::EigensolverType::Subspace:
				strEigensolver = "Subspace";
				break;
			case StepEnumType::EigensolverType::AMS:
				strEigensolver = "AMS";
				break;
			default:
				break;
			}

			*out << "*Frequency, eigensolver=" << strEigensolver
				<<", sim, acoustic coupling=on,"
				<<" normalization=mass " << "\r\n";
			*out <<  stepBasicStruct.value_Eigenvalues << "," 
				<< stepBasicStruct.value_FrequencyShift << ","
				<< stepBasicStruct.value_MinFrequency << ","
				<< stepBasicStruct.value_MaxFrequency << ","
				<< stepBasicStruct.value_BlockSize << ","
				<< stepBasicStruct.value_MaxBlockLanczos
				<< "\r\n";
			writeBC(out, "Initial");
			writeOutput(out);
		}

	}

}

void InpWriteManager::writeBC(QTextStream* out,QString stepName)
{
	*out << "** " << "\r\n";
	*out << "** BOUNDARY CONDITIONS" << "\r\n";
	*out << "** " << "\r\n";

	QHash<QString, BCData*>* bcDataHash = _abaqusModel->getBcDataHash();

	QList<BCData*> list = bcDataHash->values();
	int count = list.count();

	for (int i = 0; i <count; i++)
	{
		BCData* bcData = list.at(i);
		QString strBCName = bcData->getBCName();
		QString strBCType = bcData->getBcType();
		QString strStepName = bcData->getStepName();
		if (strStepName.contains(stepName))
		{
			*out << "** Name: " << strBCName
				<< " Type: " << strBCType << "\r\n";
			*out << "*Boundary" << "\r\n";
			if (strBCType.contains("Displacement/Rotation"))
			{
				writeDisplacement(out, bcData);
			}
			else if (strBCType.contains("Symmetry/Antisymmetry/Encastre"))
			{
				writeSymmetry(out, bcData);
			}
		}
	}

}

void InpWriteManager::writeOutput(QTextStream* out)
{
	*out << "** " << "\r\n";
	*out << "** OUTPUT REQUESTS" << "\r\n";
	*out << "** " << "\r\n";
	*out << "*Restart, write, frequency=0" << "\r\n";
	*out << "** " << "\r\n";
	*out << "** FIELD OUTPUT: F-Output-1" << "\r\n";
	*out << "** " << "\r\n";
	*out << "*Output, field, variable=PRESELECT" << "\r\n";
	*out << "*End Step" << "\r\n";

}

void InpWriteManager::writeDisplacement(QTextStream* out, BCData* bcData)
{
	DisplacementStruct disStruct = bcData->getDisplacement();
	QString strSetName = bcData->getSetName();
	if (disStruct.bU1)
	{
		*out << strSetName << ", 1, 1" << "\r\n";
	}
	if (disStruct.bU2)
	{
		*out << strSetName << ", 2, 2" << "\r\n";
	}
	if (disStruct.bU3)
	{
		*out << strSetName << ", 3, 3" << "\r\n";
	}
	if (disStruct.bUR1)
	{
		*out << strSetName << ", 4, 4" << "\r\n";
	}
	if (disStruct.bUR2)
	{
		*out << strSetName << ", 5, 5" << "\r\n";
	}
	if (disStruct.bUR3)
	{
		*out << strSetName << ", 6, 6" << "\r\n";
	}
}

void InpWriteManager::writeSymmetry(QTextStream* out, BCData* bcData)
{
	BCEnumType::SymmetryType symmetryType = bcData->getSymmetryType();
	QString strSetName = bcData->getSetName();
	switch (symmetryType)
	{
	case BCEnumType::XSYMM:
		*out << strSetName << ", XSYMM" << "\r\n";
		break;
	case BCEnumType::YSYMM:
		*out << strSetName << ", YSYMM" << "\r\n";
		break;
	case BCEnumType::ZSYMM:
		*out << strSetName << ", ZSYMM" << "\r\n";
		break;
	case BCEnumType::XASYMM:
		*out << strSetName << ", XASYMM" << "\r\n";
		break;
	case BCEnumType::YASYMM:
		*out << strSetName << ", YASYMM" << "\r\n";
		break;
	case BCEnumType::ZASYMM:
		*out << strSetName << ", ZASYMM" << "\r\n";
		break;
	case BCEnumType::PINNED:
		*out << strSetName << ", PINNED" << "\r\n";
		break;
	case BCEnumType::ENCASTRE:
		*out << strSetName << ", ENCASTRE" << "\r\n";
		break;
	default:
		break;
	}

}


