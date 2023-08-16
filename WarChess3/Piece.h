#pragma once

#include <QLabel>
#include <QWidget>
#include "config.h"
#include "HPLabel.h"
#include "PropertyTag.h"



class Piece : public QLabel
{
	Q_OBJECT

public:
	enum PIECESTATE { BEGIN, FIND_PATH, FIND_ENEMIES, FINISH, DEAD };

public:
	Piece(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);

public:
	PIECESTATE pieceState; // 人物状态，见枚举变量
	bool belong;
	int cellX, cellY;
	QVBoxLayout* layout;

	QPixmap icon; // 棋子图标
	QString name; // 棋子名称
	HPLabel* hpLabel; // 血条

	int curHp, maxHp, armor;    //棋子的血量和护甲属性
	PropertyTag* propertyTag;    //棋子属性栏

public:
	// 鼠标进入，弹出属性栏
	void enterEvent(QEvent*)override;
	// 鼠标移出，关闭属性栏
	void leaveEvent(QEvent*)override;

	void bloodLossAnimation(int decreasedHp);

public slots:
	// 被攻击时伤害结算，attrack是被攻击的攻击点数
	virtual void beAttackedSlot(const int attackPoints) = 0;
	// 需要更新数据时，发射数据更新信号
	void updateInfoSlot()const;

signals:
	// 基本信息改变
	void infoChangedSignal()const;
	// 被攻击
	void beAttackedSignal(int attackPoints)const;
	// 重绘主屏幕
	void repaintScreenSignal()const;
};