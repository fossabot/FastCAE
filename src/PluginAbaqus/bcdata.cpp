#include "bcdata.h"

BCData::BCData()
{

}

BCData::~BCData()
{

}

void BCData::writeToProjectFile(QDomDocument* doc, QDomElement* ele)
{
	QDomElement eleBCData = doc->createElement("BCData");

	eleBCData.setAttribute("BCName", strBCName);
	eleBCData.setAttribute("StepName", strStepName);
	eleBCData.setAttribute("SetName", strSetName);
	eleBCData.setAttribute("BcType", strBCType);
	if (strBCType == "Displacement/Rotation")
	{
		QDomElement eleDisplacement = doc->createElement("Displacement");

		eleDisplacement.setAttribute("bU1", displacement.bU1);
		eleDisplacement.setAttribute("bU2", displacement.bU2);
		eleDisplacement.setAttribute("bU3", displacement.bU3);
		eleDisplacement.setAttribute("bUR1", displacement.bUR1);
		eleDisplacement.setAttribute("bUR2", displacement.bUR2);
		eleDisplacement.setAttribute("bUR3", displacement.bUR3);
		eleBCData.appendChild(eleDisplacement);
	}
	else if (strBCType == "Symmetry/Antisymmetry/Encastre")
	{
		eleBCData.setAttribute("SymmetryType", symmetryType);
	}
	ele->appendChild(eleBCData);
}

void BCData::readDataFromProjectFile(QDomElement* ele)
{
	strBCName = ele->attribute("BCName");
	strStepName = ele->attribute("StepName");
	strSetName = ele->attribute("SetName");
	strBCType = ele->attribute("BcType");

	if (strBCType == "Displacement/Rotation")
	{
		QDomNodeList domBCDataHash = ele->elementsByTagName("Displacement");
		if (domBCDataHash.count() == 1)
		{
			QDomElement eledis = domBCDataHash.at(0).toElement();
			displacement.bU1 = eledis.attribute("bU1").toInt();
			displacement.bU2 = eledis.attribute("bU2").toInt();
			displacement.bU3 = eledis.attribute("bU3").toInt();
			displacement.bUR1 = eledis.attribute("bUR1").toInt();
			displacement.bUR2 = eledis.attribute("bUR2").toInt();
			displacement.bUR3 = eledis.attribute("bUR3").toInt();
		}
	}
	else if (strBCType == "Symmetry/Antisymmetry/Encastre")
	{
		symmetryType = BCEnumType::SymmetryType(ele->attribute("SymmetryType").toInt());
	}

}
