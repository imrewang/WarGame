#pragma once

#include <QLabel>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    enum STYLE { NOSTYLE, TRANSPARENTSTYLE };
protected:
    QPixmap m_pic; // ��ʾ��ͼƬ
    bool m_enter; // �Ƿ��Ѿ�enter
    int m_style; // ��STYLEö��ֵ
    void mousePressEvent(QMouseEvent* event)override; // �������emit clicked
    void enterEvent(QEvent*)override; // �������enterOrNot
    void leaveEvent(QEvent*)override; // �뿪�����enterOrNotR
    void paintEvent(QPaintEvent*)override; // ����
public:
    explicit ClickLabel(const int w, const int h, const QPixmap map, QWidget* parent = nullptr, const int style = NOSTYLE, const QString str = "");
    void setPixmap(QPixmap t_pic); // ����ͼƬ
signals:
    void clicked()const; // ����ź�
};