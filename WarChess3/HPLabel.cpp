#include "HPLabel.h"

// ����Ѫ������������������
HPLabel::HPLabel( const int maxHp, const bool belong, const int size, QWidget* parent)
    :QLabel(parent), 
    size(size), 
    curHp(maxHp),
    maxHp(maxHp),
    belong(belong)
{
}
// ����Ѫ��
void HPLabel::resetHp(const int curHp)
{
    if (curHp < 0) {
        this->curHp = 0;
    }
    else if (curHp > maxHp) {
        this->curHp = maxHp;
    }
    else {
        this->curHp = curHp;
    }
}
// ����Ѫ��
void HPLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if (belong == BLUE) {// ������Ѫ
        painter.setBrush(QColor(36, 169, 255));
    }
    else { // �췽��Ѫ
        painter.setBrush(QColor(117, 27, 19));//QColor(36, 169, 255)
    }
    painter.drawRect(0, 0, (1.0 * curHp / maxHp) * size, HP_HEIGHT); // Ѫ������
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, size, HP_HEIGHT); // Ѫ�۱߿�
    painter.setPen(Qt::NoPen);
}