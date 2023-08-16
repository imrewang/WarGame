#pragma once

#include "PropertyTag.h"


class RoleProperty : public PropertyTag
{
public:
	explicit RoleProperty(QString name, int maxHp, int maxMove, int attackPoints, int attackRange, int armor, QWidget* parent);

private:
	int maxMove;
	int attackPoints;
	int attackRange;

	QGridLayout m_layout;
	QLabel moveLabel1, moveLabel2,
		attackPointsLabel1, attackPointsLabel2,
		attackRangeLabel1, attackRangeLabel2;

public:
	// 更新属性栏数据
	void updatePropertyData(const int curhp, const int curMove, const int localCellX, const int localCellY) override;

};
