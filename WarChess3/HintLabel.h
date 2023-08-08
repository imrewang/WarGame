#pragma once

#include <QLabel>

class HintLabel : public QLabel
{
    Q_OBJECT
public:
    HintLabel(QWidget* parent = nullptr, const int x = 650, const int y = 150);
    HintLabel(const QString t_str, QWidget* parent = nullptr, const int x = 650, const int y = 150);
    void setText(QString t_str, const int nexth = 2); // 设置显示的字符串
protected:
    QString m_str; // 显示的字符串
    QPixmap bluehint, redhint, hint;
    void paintEvent(QPaintEvent*)override;
};