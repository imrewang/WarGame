#include"BaseProperty.h"

BaseProperty::BaseProperty(QString name, int maxHp, int armor, int cellX, int cellY, QWidget* parent)
	:PropertyTag(name, maxHp, armor, parent)
{
	// 将属性加入layout
	propertyLayout.addWidget(&nameLabel, 0, 0);
	propertyLayout.addWidget(&hpLabel1, 1, 0);
	propertyLayout.addWidget(&hpLabel2, 1, 1);
	propertyLayout.addWidget(&armorLabel1, 2, 0);
	propertyLayout.addWidget(&armorLabel2, 2, 1);
	propertyLayout.setVerticalSpacing(0);
	setLayout(&propertyLayout);

	move((cellX - 4) * CELL_SIZE, (cellY - 1) * CELL_SIZE);
}

void BaseProperty::updatePropertyData(const int curhp, const int curMove, const int localCellX, const int localCellY)
{
	// 更新数据
	hpLabel2.setText(QString::number(curhp) + "/" + QString::number(maxHp));
}
