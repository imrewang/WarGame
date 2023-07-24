#include "gamelabel.h"
#include "config.h"
#include <QFontMetrics>

/*  此文件包含与游戏相关的两个派生自QLabel的类：HintLabel和ClickLabel
 *  HintLabel可以在游戏界面弹出提示框
 *  ClickLabel具有enter时透明、点击发送信号等功能
 */

 // 提示框构造函数
HintLabel::HintLabel(QWidget* parent, int x, int y) :
    QLabel(parent)
{
    qDebug() << "HintLabel(QWidget* parent, int x, int y)" << endl;
    bluehint = QPixmap(HINT_BLUE_PATH);
    bluehint = bluehint.scaled(bluehint.width()/2, bluehint.height() / 2);

    redhint = QPixmap(HINT_RED_PATH);
    redhint = redhint.scaled(bluehint.width(), bluehint.height() );

    hint = QPixmap(HINT_PATH);
    hint = hint.scaled(bluehint.width(), bluehint.height());

    setGeometry(WINDOW_WIDTH / 2 - x / 2 + 30, y/2, x, y);
    //setPixmap(bluehint);
    qDebug() << width()<< height() << endl;
}
HintLabel::HintLabel(QString t_str, QWidget* parent, int x, int y) :
    QLabel(parent), m_str(t_str)
{
    qDebug() << "HintLabel(QString t_str, QWidget* parent, int x, int y)" << endl;
    setGeometry(x, y, width(), height());
    setPixmap(QPixmap("pic/EuropeanWar/Olga.webp"));
    setAttribute(Qt::WA_DeleteOnClose);
  
    setFixedSize(650, 150);
    update();
    show();
    raise();
}
// 为提示框设置文字
void HintLabel::setText(QString t_str,const int nexth)
{
    m_str = t_str;
    //鼠标事件穿透
    setAttribute(Qt::WA_TransparentForMouseEvents, true);


    if (nexth == BLUE) {
        setPixmap(bluehint);
    }
    else if(nexth == RED){
        setPixmap(redhint);
    }
    else {
        setPixmap(hint);
    }
}
// 打印提示框
void HintLabel::paintEvent(QPaintEvent* ev)
{
    QLabel::paintEvent(ev);
    QPainter painter(this);
    QFont font("华文新魏", 40, 50, false);
    QFontMetrics fontMetrics(font);
    painter.setFont(font);
    painter.setPen(QPen(QColor(120, 120, 120)));
    QString title(m_str);
    int widthOfTitle = fontMetrics.horizontalAdvance(title);//字符串显示的像素大小，居中
    painter.drawText(this->width() / 2 - widthOfTitle / 2, 90, title);
    //qDebug() << width() << height() << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// 点击按键，两种模式，一种enter时变透明，一种不变
ClickLabel::ClickLabel(const int w, const int h, const QPixmap map, QWidget* parent, const int t_style, const QString str) 
    : QLabel(parent)
{
    setFixedSize(w, h);
    m_pic = map.scaled(w, h);
    m_enter = false;
    m_style = t_style;

    //按钮上显示的文字
    QLabel* label = new QLabel;
    label->setParent(this);
    label->setFixedSize(w, h);
    QFont font;
    font.setFamily("华文行楷");
    font.setPointSize(50);
    label->setFont(font);
    label->setText(str);
    //设置label上的文字对齐方式 水平居中 和垂直居中
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //鼠标事件穿透
    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);

}
// 点击时发送被点击信号
void ClickLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
    QLabel::mousePressEvent(event);
}
// 进入时重绘
void ClickLabel::enterEvent(QEvent*)
{
    m_enter = true;
    repaint();
}
// 离开时重绘
void ClickLabel::leaveEvent(QEvent*)
{
    m_enter = false;
    repaint();
}
void ClickLabel::paintEvent(QPaintEvent* eve)
{
    QLabel::paintEvent(eve);
    QPainter painter(this);
    // 如果是透明style，则更新透明度
    if (m_style == TRANSPARENTSTYLE)
    {
        if (m_enter) {
            painter.setOpacity(0.6);
        }
    }
    painter.drawPixmap(0, 0, m_pic);
}
// 重设图片
void ClickLabel::setPixmap(const QPixmap t_pic)
{
    m_pic = t_pic;//尽量不要使用，有bug，这个大小没法调节
}

