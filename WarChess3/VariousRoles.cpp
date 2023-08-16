#include "VariousRoles.h"

Sultan::Sultan(const int cellX, const int cellY, const bool belong, QWidget* parent) :
	Role(cellX, cellY, belong, parent)
{
	curHp = maxHp = 390;
	curMove = maxMove = 9;
	attackPoints = 105;
	armor = 95;
	attackRange = 1;
	name = "苏丹亲卫1";

	icon.load(WARRIOR_PATH);
	icon = icon.scaled(CELL_SIZE, CELL_SIZE);
	setPixmap(icon);

	hpLabel = new HPLabel(maxHp, belong, CELL_SIZE, this);

	propertyTag = new RoleProperty(name, maxHp, maxMove, attackPoints, attackRange, armor, parent);
	propertyTag->hide();
}

Teutonic::Teutonic(const int cellX, const int cellY, const bool belong, QWidget* parent) :
	Role(cellX, cellY, belong, parent)
{
	curHp = maxHp = 380;
	curMove = maxMove = 8;
	attackPoints = 110;
	armor = 90;
	attackRange = 2;
	name = "条顿骑士2";

	icon.load(ASSASSIN_PATH);
	icon = icon.scaled(CELL_SIZE, CELL_SIZE);
	setPixmap(icon);

	hpLabel = new HPLabel(maxHp, belong, CELL_SIZE, this);

	propertyTag = new RoleProperty(name, maxHp, maxMove, attackPoints, attackRange, armor, parent);
	propertyTag->hide();
}

Hussars::Hussars(const int cellX, const int cellY, const bool belong, QWidget* parent) :
	Role(cellX, cellY, belong, parent)
{
	curHp = maxHp = 370;
	curMove = maxMove = 7;
	attackPoints = 115;
	armor = 85;
	attackRange = 3;
	name = "翼骑兵3";

	icon.load(SHOOTER_PATH);
	icon = icon.scaled(CELL_SIZE, CELL_SIZE);
	setPixmap(icon);

	hpLabel = new HPLabel(maxHp, belong, CELL_SIZE, this);

	propertyTag = new RoleProperty(name, maxHp, maxMove, attackPoints, attackRange, armor, parent);
	propertyTag->hide();
}


Dragoon::Dragoon(const int cellX, const int t_celly, const bool belong, QWidget* parent) :
	Role(cellX, t_celly, belong, parent)
{
	curHp = maxHp = 360;
	curMove = maxMove = 6;
	attackPoints = 120;
	armor = 80;
	attackRange = 4;
	name = "龙骑兵4";

	icon.load(MASTER_PATH);
	icon = icon.scaled(CELL_SIZE, CELL_SIZE);
	setPixmap(icon);

	hpLabel = new HPLabel(maxHp, belong, CELL_SIZE, this);

	propertyTag = new RoleProperty(name, maxHp, maxMove, attackPoints, attackRange, armor, parent);
	propertyTag->hide();
}


Mamluk::Mamluk(const int cellX, const int cellY, const bool belong, QWidget* parent) :
	Role(cellX, cellY, belong, parent)
{
	curHp = maxHp = 350;
	curMove = maxMove = 5;
	attackPoints = 135;
	armor = 75;
	attackRange = 5;
	name = "马穆鲁克5";

	icon.load(TANK_PATH);
	icon = icon.scaled(CELL_SIZE, CELL_SIZE);
	setPixmap(icon);

	hpLabel = new HPLabel(maxHp, belong, CELL_SIZE, this);

	propertyTag = new RoleProperty(name, maxHp, maxMove, attackPoints, attackRange, armor, parent);
	propertyTag->hide();
}