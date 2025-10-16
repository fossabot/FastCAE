#include "abaqusmodel.h"
#include "stepdata.h"
#include <QDomElement>


ModelData::AbaqusModel::AbaqusModel(ProjectTreeType t)
	:ModelDataBaseExtend(t)
{
	_stepNameList = new QList<QString>();
	_bcDataHash = new QHash<QString, BCData*>();
	_stepDataHash = new QHash<QString, StepData*>();
	_materialStruct = new MaterialStruct();
}

ModelData::AbaqusModel::~AbaqusModel()
{
	if (_bcDataHash)
	{
		clearStepDataHash();
		delete _bcDataHash;
		_bcDataHash = nullptr;
	}

	if (_stepDataHash)
	{
		clearBCDataHash();
		delete _stepDataHash;
		_stepDataHash = nullptr;
	}
	if (_stepNameList)
	{
		_stepNameList->clear();
		delete _stepNameList;
		_stepNameList = nullptr;
	}


}


QDomElement& ModelData::AbaqusModel::writeToProjectFile(QDomDocument* doc, QDomElement* ele)
{
	QDomElement elem = ModelDataBaseExtend::writeToProjectFile(doc, ele);
	writeStepNameList(doc, &elem);
	writeMaterialStruct(doc, &elem);
	writeStepDataHash(doc, &elem);
	writeBCDataHash(doc, &elem);

	return elem;
}

void ModelData::AbaqusModel::readDataFromProjectFile(QDomElement* e)
{
	ModelDataBaseExtend::readDataFromProjectFile(e);

	QDomNodeList domStepList = e->elementsByTagName("Step");
	_stepNameList->clear();
	for (int i = 0; i < domStepList.size(); ++i)
	{
		QDomElement ele = domStepList.at(i).toElement();
		QString strName = ele.attribute("name");
		_stepNameList->append(strName);
	}

	QDomNodeList domMaterialStruct = e->elementsByTagName("MaterialStruct");
	if (domMaterialStruct.count() == 1)
	{
		QDomElement ele = domMaterialStruct.at(0).toElement();
		_materialStruct->strDensity = ele.attribute("Density");
		_materialStruct->strRatio = ele.attribute("Ratio");
		_materialStruct->strModulus = ele.attribute("Modulus");
		_materialStruct->strSetName = ele.attribute("SetName");
		_materialStruct->strMaterialName = ele.attribute("MaterialName");
	}

	clearStepDataHash();
	QDomNodeList domStepDataHash = e->elementsByTagName("StepData");

	for (int i = 0; i < domStepDataHash.size(); i++)
	{
		QDomElement ele = domStepDataHash.at(i).toElement();
		StepData* stepData = new StepData();
		stepData->readDataFromProjectFile(&ele);
		_stepDataHash->insert(stepData->getStepName(), stepData);
	}

	clearBCDataHash();
	QDomNodeList domBCDataHash = e->elementsByTagName("BCData");

	for (int i = 0; i < domBCDataHash.size();i++)
	{
		QDomElement ele = domBCDataHash.at(i).toElement();
		BCData* bcData = new BCData();
		bcData->readDataFromProjectFile(&ele);
		_bcDataHash->insert(bcData->getBCName(), bcData);
	}

}

void ModelData::AbaqusModel::writeStepNameList(QDomDocument* doc, QDomElement* ele)
{
	if (_stepNameList)
	{
		QDomElement eleStepList = doc->createElement("StepList");
		for (QString strStep : *_stepNameList)
		{
			QDomElement eleStep = doc->createElement("Step");
			eleStep.setAttribute("name", strStep);
			eleStepList.appendChild(eleStep);
		}
		ele->appendChild(eleStepList);
	}
}

void ModelData::AbaqusModel::writeMaterialStruct(QDomDocument* doc, QDomElement* ele)
{
	if (_materialStruct)
	{
		QDomElement eleMaterialStruct = doc->createElement("MaterialStruct");

		eleMaterialStruct.setAttribute("MaterialName", _materialStruct->strMaterialName);
		eleMaterialStruct.setAttribute("SetName", _materialStruct->strSetName);
		eleMaterialStruct.setAttribute("Density", _materialStruct->strDensity);
		eleMaterialStruct.setAttribute("Modulus", _materialStruct->strModulus);
		eleMaterialStruct.setAttribute("Ratio", _materialStruct->strRatio);

		ele->appendChild(eleMaterialStruct);
	}
}

void ModelData::AbaqusModel::writeStepDataHash(QDomDocument* doc, QDomElement* ele)
{
	if (_stepDataHash)
	{

		QDomElement eleStepDataHash = doc->createElement("StepDataHash");

		QList<QString> listKey = _stepDataHash->keys();
		for (QString strKey : listKey)
		{
			StepData* stepData = _stepDataHash->value(strKey);
			stepData->writeToProjectFile(doc, &eleStepDataHash);
		}

		ele->appendChild(eleStepDataHash);
	}
}

void ModelData::AbaqusModel::writeBCDataHash(QDomDocument* doc, QDomElement* ele)
{
	if (_bcDataHash)
	{
		QDomElement eleBCDataHash = doc->createElement("BCDataHash");

		QList<QString> listKey = _bcDataHash->keys();
		for (QString strKey : listKey)
		{
			BCData* bcData = _bcDataHash->value(strKey);
			bcData->writeToProjectFile(doc, &eleBCDataHash);
		}

		ele->appendChild(eleBCDataHash);
	}
}

void ModelData::AbaqusModel::clearStepDataHash()
{
	if (_bcDataHash)
	{
		QHash<QString, BCData*>::const_iterator i;
		for (i = _bcDataHash->constBegin(); i != _bcDataHash->constEnd(); i++)
		{
			if (i.value())
			{
				delete i.value();
			}
		}
		_bcDataHash->clear();
	}
}

void ModelData::AbaqusModel::clearBCDataHash()
{
	if (_bcDataHash)
	{
		QHash<QString, BCData*>::const_iterator i;
		for (i = _bcDataHash->constBegin(); i != _bcDataHash->constEnd(); i++)
		{
			if (i.value())
			{
				delete i.value();
			}
		}
		_bcDataHash->clear();
	}
}

