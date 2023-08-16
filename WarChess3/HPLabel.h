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
    int curHp, maxHp, belong; // Ѫ��ֵ

public:
    void resetHp(const int curHp); //����Ѫ��ֵ

private:
    void paintEvent(QPaintEvent*)override; // ����
};