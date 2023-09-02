#include "Role.h"
#include "algorithm.h"

/* 此文件包含与人物角色有关的方法
 * 包含人物各种活动和控制三种人物面板（characterlabel.h）等过程
 */

Role::Role(const int cellX, const int cellY, const bool belong, QWidget* parent)
	: Piece(cellX, cellY, belong, parent)
{
	// 关于移动、攻击动画的信号和槽
	moveAnimation = new MoveAnimation();
	attackAnimation = new AttrackAnimation();
	connect(moveAnimation, &MoveAnimation::widgetDown, this, [=]() {this->cellY++; }, Qt::UniqueConnection);
	connect(moveAnimation, &MoveAnimation::widgetUp, this, [=]() {this->cellY--; }, Qt::UniqueConnection);
	connect(moveAnimation, &MoveAnimation::widgetRight, this, [=]() {this->cellX++; }, Qt::UniqueConnection);
	connect(moveAnimation, &MoveAnimation::widgetLeft, this, [=]() {this->cellX--; }, Qt::UniqueConnection);

	connect(moveAnimation, &MoveAnimation::animationFinished, this, [=]() {emit infoChangedSignal(); }, Qt::UniqueConnection);

	// 操作选择框
	selection = new RoleSelection(parent);
	selection->hide();

	// 当人物信息改变时，血条、人物属性和操作选择框的所有信息都要改变
	connect(this, &Role::infoChangedSignal, this,[=]() {
		// 按顺序，raise有次序
		if (pieceState == DEAD)
		{
			propertyTag->close();
			selection->close();
			hide();
		}
		propertyTag->updatePropertyData(curHp, curMove, this->cellX, this->cellY);
		selection->updateSelectionData(this->cellX, this->cellY);

		hpLabel->resetHp(curHp);
		hpLabel->repaint();
		}, Qt::UniqueConnection);

	// 操作选择框的各个操作按钮
	connect(selection->moveButton, &QPushButton::clicked, this, &Role::roleMoveSlot, Qt::UniqueConnection);
	connect(selection->attackButton, &QPushButton::clicked, this, &Role::roleAttackSlot, Qt::UniqueConnection);
	connect(selection->skipButton, &QPushButton::clicked, this, &Role::roleSkipSlot, Qt::UniqueConnection);
}


// 人物需要移动，连接到GameScene的寻路显示上
void Role::beAttackedSlot(const int attackPoints)
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
		emit killRoleSignal(this);
		qDebug() << "emit killRoleSignal(this);" << endl;
	}
	bloodLossAnimation(decreasedHp);
}

// 人物需要移动，连接到GameScene的寻路显示上
void Role::roleMoveSlot()
{
	if (selection->isHidden() == false) {
		selection->hide();
	}
	pieceState = FIND_PATH;
	emit roleMoveSignal(this);
}
// 人物需要攻击，连接到GameScene的攻击显示上
void Role::roleAttackSlot()
{
	if (curMove <= 0)
	{
		emit displayHintLabelSignal("行动力为0");
		emit hideCancelButtonSignal();
		return;
	}
	selection->hide();
	pieceState = FIND_ENEMIES;
	emit roleAttackSignal(this);
}


// 跳过选择，向GameScene说明有人结束
void Role::roleSkipSlot()
{
	pieceState = FINISH;
	selection->hide();
	emit roleSkipSignal(this);
}

// 给予路径，调动MoveAnimation播放移动的动画
void Role::movePos(const int steps, const std::vector<int>& path)
{
	selection->hide();
	curMove -= steps;
	moveAnimation->moveAlongPath(this, path);
	//infoChangedSignal();
}
