#include "Base.h"


Base::Base(const int cellX, const int cellY, const bool belong, QWidget* parent)
	: Piece(cellX, cellY, belong, parent)
{
	curHp = maxHp = 500;
	armor = 90;
	name = "神之守护";

	icon.load(EGG_PATH);
	icon = icon.scaled(CELL_SIZE, CELL_SIZE);
	setPixmap(icon);

	hpLabel = new HPLabel(maxHp, belong, CELL_SIZE, this);

	propertyTag = new BaseProperty(name, maxHp, armor, cellX, cellY, parent);
	propertyTag->hide();

	// 当人物信息改变时，血条、人物属性和操作选择框的所有信息都要改变
	connect(this, &Base::infoChangedSignal, [=]() {
		// 按顺序，raise有次序
		if (pieceState == DEAD)
		{
			propertyTag->close();
			hide();
		}
		propertyTag->updatePropertyData(curHp);
		hpLabel->resetHp(curHp);
		hpLabel->repaint();
		});

}

void Base::beAttackedSlot(const int attackPoints)
{
	int decreasedHp;
	if (attackPoints <= 20) {
		decreasedHp = attackPoints;
	}
	else {
		decreasedHp = attackPoints - armor;
	}
	// 扣血
	curHp -= int(decreasedHp);
	curHp = min(curHp, maxHp);
	// 扣血
	//m_hp -= int(m_armor / 100.0 * attrack);

	// 判断是否死亡
	if (curHp <= 0)
	{
		pieceState = DEAD;
		hide();
		emit killBaseSignal(this);
	}
	bloodLossAnimation(decreasedHp);
}
