#include "HPLabel.h"

// 人物血条：依附于人物身上
HPLabel::HPLabel( const int maxHp, const bool belong, const int size, QWidget* parent)
    :QLabel(parent), 
    size(size), 
    curHp(maxHp),
    maxHp(maxHp),
    belong(belong)
{
}
// 更新血量
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
// 绘制血量
void HPLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if (belong == BLUE) {// 蓝方蓝血
        painter.setBrush(QColor(36, 169, 255));
    }
    else { // 红方红血
        painter.setBrush(QColor(117, 27, 19));//QColor(36, 169, 255)
    }
    painter.drawRect(0, 0, (1.0 * curHp / maxHp) * size, HP_HEIGHT); // 血槽内容
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, size, HP_HEIGHT); // 血槽边框
    painter.setPen(Qt::NoPen);
}