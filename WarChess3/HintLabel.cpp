#include "HintLabel.h"
#include "config.h"
#include <QFontMetrics>

/*
HintLabel��������Ϸ���浯����ʾ��
*/

//
//
//// ��ʾ���캯��
//HintLabel::HintLabel(QWidget* parent, int x, int y) :
//    QLabel(parent)
//{
//    qDebug() << "HintLabel(QWidget* parent, int x, int y)" << endl;
//    bluehint = QPixmap(HINT_BLUE_PATH);
//    bluehint = bluehint.scaled(bluehint.width() / 2, bluehint.height() / 2);
//
//    redhint = QPixmap(HINT_RED_PATH);
//    redhint = redhint.scaled(bluehint.width(), bluehint.height());
//
//    hint = QPixmap(HINT_PATH);
//    hint = hint.scaled(bluehint.width(), bluehint.height());
//
//    setGeometry(WINDOW_WIDTH / 2 - x / 2 + 30, y / 2, x, y);
//    //setPixmap(bluehint);
//    qDebug() << width() << height() << endl;
//}
//HintLabel::HintLabel(QString t_str, QWidget* parent, int x, int y) :
//    QLabel(parent), m_str(t_str)
//{
//    qDebug() << "HintLabel(QString t_str, QWidget* parent, int x, int y)" << endl;
//    setGeometry(x, y, width(), height());
//    setPixmap(QPixmap("pic/EuropeanWar/Olga.webp"));
//    setAttribute(Qt::WA_DeleteOnClose);
//
//    setFixedSize(650, 150);
//    update();
//    show();
//    raise();
//}
//// Ϊ��ʾ����������
//void HintLabel::setText(QString t_str, const int nexth)
//{
//    m_str = t_str;
//    //����¼���͸
//    setAttribute(Qt::WA_TransparentForMouseEvents, true);
//
//
//    if (nexth == BLUE) {
//        setPixmap(bluehint);
//    }
//    else if (nexth == RED) {
//        setPixmap(redhint);
//    }
//    else {
//        setPixmap(hint);
//    }
//}
//// ��ӡ��ʾ��
//void HintLabel::paintEvent(QPaintEvent* ev)
//{
//    QLabel::paintEvent(ev);
//    QPainter painter(this);
//    QFont font("������κ", 40, 50, false);
//    QFontMetrics fontMetrics(font);
//    painter.setFont(font);
//    painter.setPen(QPen(QColor(120, 120, 120)));
//    QString title(m_str);
//    int widthOfTitle = fontMetrics.horizontalAdvance(title);//�ַ�����ʾ�����ش�С������
//    painter.drawText(this->width() / 2 - widthOfTitle / 2, 90, title);
//    //qDebug() << width() << height() << endl;
//}