#include "stepdata.h"

StepData::StepData()
{

}

StepData::~StepData()
{

}

void StepData::writeToProjectFile(QDomDocument* doc, QDomElement* ele)
{
		QDomElement eleStepData = doc->createElement("StepData");
		eleStepData.setAttribute("StepName", stepName);
		eleStepData.setAttribute("TypeName", stepTypeName);
		writeStepBasic(doc, &eleStepData);
		writeStepOther(doc, &eleStepData);

		ele->appendChild(eleStepData);
}

void StepData::readDataFromProjectFile(QDomElement* e)
{

	stepName = e->attribute("StepName");

	stepTypeName = e->attribute("TypeName");


	QDomNodeList domStepDataHashChild = e->childNodes();

	for (int index = 0; index < domStepDataHashChild.size(); index++)
	{
		QDomElement eleChild = domStepDataHashChild.at(index).toElement();

		QString strChildName = eleChild.nodeName();
		if (strChildName == "StepBasic")
		{
			stepBasic.check_FrequencyShift = eleChild.attribute("Check_FrequencyShift").toInt();
			stepBasic.check_MinFrequency = eleChild.attribute("Check_MinFrequency").toInt();
			stepBasic.check_MaxFrequency = eleChild.attribute("Check_MaxFrequency").toInt();
			stepBasic.check_IncludeAcoustic = eleChild.attribute("Check_IncludeAcoustic").toInt();
			stepBasic.check_UseSIMBased = eleChild.attribute("Check_UseSIMBased").toInt();
			stepBasic.check_IncludeResidual = eleChild.attribute("Check_IncludeResidual").toInt();

			stepBasic.radio_Eigensolver = StepEnumType::EigensolverType(eleChild.attribute("Radio_Eigensolver").toInt());
			stepBasic.radio_Eigenvalues = StepEnumType::EigenvaluesType(eleChild.attribute("Radio_Eigenvalues").toInt());
			stepBasic.radio_BlockSize = StepEnumType::BlockSizeType(eleChild.attribute("Radio_BlockSize").toInt());
			stepBasic.radio_MaxBlockLanczos = StepEnumType::BlockSizeType(eleChild.attribute("Radio_MaxBlockLanczos").toInt());

			stepBasic.value_description = eleChild.attribute("Value_description");
			stepBasic.value_Eigenvalues = eleChild.attribute("Value_Eigenvalues");
			stepBasic.value_FrequencyShift = eleChild.attribute("Value_FrequencyShift");
			stepBasic.value_MinFrequency = eleChild.attribute("Value_MinFrequency");
			stepBasic.value_MaxFrequency = eleChild.attribute("Value_MaxFrequency");
			stepBasic.value_BlockSize = eleChild.attribute("Value_BlockSize");
			stepBasic.value_MaxBlockLanczos = eleChild.attribute("Value_MaxBlockLanczos");

		}
		else if (strChildName == "StepOther")
		{
			stepOther.radio_Normalize = StepEnumType::NormalizeType(eleChild.attribute("radio_Normalize").toInt());
			stepOther.check_Evaluate = eleChild.attribute("check_Evaluate").toInt();
			stepOther.value_Evaluate = eleChild.attribute("value_Evaluate").toDouble();

		}
	}

}

void StepData::writeStepBasic(QDomDocument* doc, QDomElement* ele)
{

	QDomElement eleStepBasic = doc->createElement("StepBasic");
	eleStepBasic.setAttribute("Value_description", stepBasic.value_description);
	eleStepBasic.setAttribute("Value_Eigenvalues", stepBasic.value_Eigenvalues);
	eleStepBasic.setAttribute("Value_FrequencyShift", stepBasic.value_FrequencyShift);
	eleStepBasic.setAttribute("Value_MinFrequency", stepBasic.value_MinFrequency);
	eleStepBasic.setAttribute("Value_MaxFrequency", stepBasic.value_MaxFrequency);
	eleStepBasic.setAttribute("Value_BlockSize", stepBasic.value_BlockSize);
	eleStepBasic.setAttribute("Value_MaxBlockLanczos", stepBasic.value_MaxBlockLanczos);

	eleStepBasic.setAttribute("Radio_Eigensolver", stepBasic.radio_Eigensolver);
	eleStepBasic.setAttribute("Radio_Eigenvalues", stepBasic.radio_Eigenvalues);
	eleStepBasic.setAttribute("Radio_BlockSize", stepBasic.radio_BlockSize);
	eleStepBasic.setAttribute("Radio_MaxBlockLanczos", stepBasic.radio_MaxBlockLanczos);

	eleStepBasic.setAttribute("Check_FrequencyShift", stepBasic.check_FrequencyShift);
	eleStepBasic.setAttribute("Check_MinFrequency", stepBasic.check_MinFrequency);
	eleStepBasic.setAttribute("Check_MaxFrequency", stepBasic.check_MaxFrequency);
	eleStepBasic.setAttribute("Check_IncludeAcoustic", stepBasic.check_IncludeAcoustic);
	eleStepBasic.setAttribute("Check_UseSIMBased", stepBasic.check_UseSIMBased);
	eleStepBasic.setAttribute("Check_IncludeResidual", stepBasic.check_IncludeResidual);
	ele->appendChild(eleStepBasic);
}

void StepData::writeStepOther(QDomDocument* doc, QDomElement* ele)
{
	QDomElement eleStepOther = doc->createElement("StepOther");
	eleStepOther.setAttribute("radio_Normalize", stepOther.radio_Normalize);

	eleStepOther.setAttribute("check_Evaluate", stepOther.check_Evaluate);
	eleStepOther.setAttribute("value_Evaluate", stepOther.value_Evaluate);

	ele->appendChild(eleStepOther);
}
