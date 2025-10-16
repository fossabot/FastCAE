#ifndef BCDATA_H
#define BCDATA_H

#include "PluginAbaqusAPI.h"
#include "QString"
#include <QDomElement>



namespace BCEnumType
{

	enum SymmetryType
	{
		XSYMM,
		YSYMM,
		ZSYMM,
		XASYMM,
		YASYMM,
		ZASYMM,
		PINNED,
		ENCASTRE,
	};
}


struct DisplacementStruct
{
	bool bU1 =false;
	bool bU2 =false;
	bool bU3 = false;
	bool bUR1 = false;
	bool bUR2 = false;
	bool bUR3 = false;
};


class PLUGINABAQUSAPI BCData
{
public:
	BCData();
	~BCData();

	QString getBCName() const { return strBCName; }
	void setBCName(QString val) { strBCName = val; }


	QString getStepName() const { return strStepName; }
	void setStepName(QString val) { strStepName = val; }

	QString getSetName() const { return strSetName; }
	void setSetName(QString val) { strSetName = val; }

	DisplacementStruct getDisplacement() const { return displacement; }
	void setDisplacement(DisplacementStruct val) { displacement = val; }

	BCEnumType::SymmetryType getSymmetryType() const { return symmetryType; }
	void setSymmetryType(BCEnumType::SymmetryType val) { symmetryType = val; }

	QString getBcType() const { return strBCType; }
	void setBcType(QString val) { strBCType = val; }


	void writeToProjectFile(QDomDocument* doc, QDomElement* ele);
	void readDataFromProjectFile(QDomElement* ele);
private:


	QString strBCName;//边界名称
	QString strBCType;//边界类型
	QString strStepName;//分析步名称
	QString strSetName;//组件名称

	DisplacementStruct displacement;
	BCEnumType::SymmetryType symmetryType;
};

#endif // BCDATA_H
