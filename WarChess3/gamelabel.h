﻿#pragma once

#include <QLabel>

class HintLabel : public QLabel
{
    Q_OBJECT
public:
    HintLabel(QWidget* parent = nullptr, const int x = 650, const int y = 150);
    HintLabel(const QString t_str, QWidget* parent = nullptr, const int x = 650, const int y = 150);
    void setText(QString t_str , const int nexth = 2); // 设置显示的字符串
protected:
    QString m_str; // 显示的字符串
    QPixmap bluehint, redhint,hint;
    void paintEvent(QPaintEvent*)override;
};

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    enum STYLE { NOSTYLE, TRANSPARENTSTYLE };
protected:
    QPixmap m_pic; // 显示的图片
    bool m_enter; // 是否已经enter
    int m_style; // 见STYLE枚举值
    void mousePressEvent(QMouseEvent* event)override; // 被点击后emit clicked
    void enterEvent(QEvent*)override; // 进入更新enterOrNot
    void leaveEvent(QEvent*)override; // 离开后更新enterOrNotR
    void paintEvent(QPaintEvent*)override; // 绘制
public:
    explicit ClickLabel(const int w, const int h, const QPixmap map, QWidget* parent = nullptr, const int style = NOSTYLE, const QString str = "");
    void setPixmap(QPixmap t_pic); // 重置图片
signals:
    void clicked()const; // 点击信号
};
