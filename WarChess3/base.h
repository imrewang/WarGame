#pragma once

#include "BaseProperty.h"
#include "Piece.h"

class Base : public Piece
{
    Q_OBJECT
public:
    Base(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);
public slots:
    // 被攻击时伤害结算，attrack是被攻击的攻击点数
    void beAttackedSlot(const int attackPoints) override;
signals:
    // 棋子死亡
    void killBaseSignal(Base*)const;
};
