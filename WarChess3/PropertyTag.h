#pragma once

#include <QLabel>
#include "config.h"


class PropertyTag : public QLabel
{
	Q_OBJECT
public:
	explicit PropertyTag(QString name, int maxHp, int armor, QWidget* parent);

protected:
	QString name;
	int maxHp;
	int armor;

	QGridLayout propertyLayout;
	QLabel nameLabel, hpLabel1, hpLabel2,
		armorLabel1, armorLabel2;

public:
	virtual void updatePropertyData(const int curhp, const int curMove = 0, const int localCellX = 0, const int localCellY = 0) = 0;
};