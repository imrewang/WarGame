#pragma once


#include <QLabel>
#include "config.h"


class HPLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HPLabel(const int maxHp, const bool belong, const int size, QWidget* parent = nullptr);
private:
    int size;
    int curHp, maxHp, belong; // 血量值

public:
    void resetHp(const int curHp); //重置血量值

private:
    void paintEvent(QPaintEvent*)override; // 绘制
};