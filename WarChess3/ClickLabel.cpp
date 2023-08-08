#include "ClickLabel.h"
#include "config.h"
#include <QFontMetrics>

/*  
 *  ClickLabel具有enter时透明、点击发送信号等功能
 */



/////////////////////////////////////////////////////////////////////////////////////////////////
//// 点击按键，两种模式，一种enter时变透明，一种不变
//ClickLabel::ClickLabel(const int w, const int h, const QPixmap map, QWidget* parent, const int t_style, const QString str)
//    : QLabel(parent)
//{
//    setFixedSize(w, h);
//    m_pic = map.scaled(w, h);
//    m_enter = false;
//    m_style = t_style;
//
//    //按钮上显示的文字
//    QLabel* label = new QLabel;
//    label->setParent(this);
//    label->setFixedSize(w, h);
//    QFont font;
//    font.setFamily("华文行楷");
//    font.setPointSize(50);
//    label->setFont(font);
//    label->setText(str);
//    //设置label上的文字对齐方式 水平居中 和垂直居中
//    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    //鼠标事件穿透
//    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
//
//}
//// 点击时发送被点击信号
//void ClickLabel::mousePressEvent(QMouseEvent* event)
//{
//	emit clicked();
//            QLabel::mousePressEvent(event);
//}
//// 进入时重绘
//void ClickLabel::enterEvent(QEvent*)
//{
//    m_enter = true;
//    repaint();
//}
//// 离开时重绘
//void ClickLabel::leaveEvent(QEvent*)
//{
//    m_enter = false;
//    repaint();
//}
//void ClickLabel::paintEvent(QPaintEvent* eve)
//{
//    QLabel::paintEvent(eve);
//    QPainter painter(this);
//    // 如果是透明style，则更新透明度
//    if (m_style == TRANSPARENTSTYLE)
//    {
//        if (m_enter) {
//            painter.setOpacity(0.6);
//        }
//    }
//    painter.drawPixmap(0, 0, m_pic);
//}
//// 重设图片
//void ClickLabel::setPixmap(const QPixmap t_pic)
//{
//    m_pic = t_pic;//尽量不要使用，有bug，这个大小没法调节
//}
//
