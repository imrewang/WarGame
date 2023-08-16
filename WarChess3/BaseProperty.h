#pragma once

#include "PropertyTag.h"

class BaseProperty : public PropertyTag
{
public:
	explicit BaseProperty(QString name, int maxHp, int armor, int cellX, int cellY, QWidget* parent);


public:
	void updatePropertyData(const int curhp, const int curMove , const int localCellX, const int localCellY ) override;
};