#ifndef STEPDATA_H
#define STEPDATA_H

#include "PluginAbaqusAPI.h"
#include "QString"
#include <QDomElement>

	namespace StepEnumType
	{
		enum NlgeomType
		{
			Off,
			On,
		};

		enum EigensolverType
		{
			Lanczos,
			Subspace,
			AMS,
		};

		enum EigenvaluesType
		{
			AllinFrequencyRange,
			Value,
		};

		enum BlockSizeType
		{
			Default,
			ValueSize,
		};

		enum NormalizeType
		{
			Displacement,
			Mass,
		};

	}

	struct StepBasicStruct
	{

		//Basic
		QString value_description = "";
		
		StepEnumType::EigensolverType radio_Eigensolver = StepEnumType::EigensolverType::Lanczos;
		
		StepEnumType::EigenvaluesType radio_Eigenvalues = StepEnumType::EigenvaluesType::AllinFrequencyRange;
		QString value_Eigenvalues = " ";

		bool check_FrequencyShift = false;
		QString value_FrequencyShift = " ";
		
		bool check_MinFrequency = false;
		QString value_MinFrequency = " ";
		
		bool check_MaxFrequency = false;
		QString value_MaxFrequency = " ";

		bool check_IncludeAcoustic = false;

		StepEnumType::BlockSizeType radio_BlockSize = StepEnumType::BlockSizeType::Default;
		QString value_BlockSize = " ";

		StepEnumType::BlockSizeType radio_MaxBlockLanczos = StepEnumType::BlockSizeType::Default;
		QString value_MaxBlockLanczos = " ";

		bool check_UseSIMBased = false;
		bool check_IncludeResidual = false;

	};

	struct StepOtherStruct
	{
		StepEnumType::NormalizeType radio_Normalize = StepEnumType::NormalizeType::Displacement;

		bool check_Evaluate = false;
		double value_Evaluate = 0.0f;
	};

	class StepData
	{
	public:
		StepData();
		~StepData();
		StepBasicStruct getStepBasic() const { return stepBasic; }
		void setStepBasic(StepBasicStruct val) { stepBasic = val; }
		StepOtherStruct getStepOther() const { return stepOther; }
		void setStepOther(StepOtherStruct val) { stepOther = val; }
		QString getStepName() const { return stepName; }
		void setStepName(QString val) { stepName = val; }
		QString getStepTypeName() const { return stepTypeName; }
		void setStepTypeName(QString val) { stepTypeName = val; }

		void writeToProjectFile(QDomDocument* doc, QDomElement* ele);
		void readDataFromProjectFile(QDomElement* e);
	protected:


	private:
		void writeStepBasic(QDomDocument* doc, QDomElement* ele);
		void writeStepOther(QDomDocument* doc, QDomElement* ele);



	private:
		StepBasicStruct stepBasic;//分析步基础数据
		StepOtherStruct stepOther;//分析步其他数据
		QString stepName;//分析步名称
		QString stepTypeName;//分析步类型名称
		 
	};

#endif // STEPDATA_H
