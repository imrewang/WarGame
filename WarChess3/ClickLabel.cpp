#include "ClickLabel.h"
#include "config.h"
#include <QFontMetrics>

/*  
 *  ClickLabel����enterʱ͸������������źŵȹ���
 */



/////////////////////////////////////////////////////////////////////////////////////////////////
//// �������������ģʽ��һ��enterʱ��͸����һ�ֲ���
//ClickLabel::ClickLabel(const int w, const int h, const QPixmap map, QWidget* parent, const int t_style, const QString str)
//    : QLabel(parent)
//{
//    setFixedSize(w, h);
//    m_pic = map.scaled(w, h);
//    m_enter = false;
//    m_style = t_style;
//
//    //��ť����ʾ������
//    QLabel* label = new QLabel;
//    label->setParent(this);
//    label->setFixedSize(w, h);
//    QFont font;
//    font.setFamily("�����п�");
//    font.setPointSize(50);
//    label->setFont(font);
//    label->setText(str);
//    //����label�ϵ����ֶ��뷽ʽ ˮƽ���� �ʹ�ֱ����
//    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    //����¼���͸
//    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
//
//}
//// ���ʱ���ͱ�����ź�
//void ClickLabel::mousePressEvent(QMouseEvent* event)
//{
//	emit clicked();
//            QLabel::mousePressEvent(event);
//}
//// ����ʱ�ػ�
//void ClickLabel::enterEvent(QEvent*)
//{
//    m_enter = true;
//    repaint();
//}
//// �뿪ʱ�ػ�
//void ClickLabel::leaveEvent(QEvent*)
//{
//    m_enter = false;
//    repaint();
//}
//void ClickLabel::paintEvent(QPaintEvent* eve)
//{
//    QLabel::paintEvent(eve);
//    QPainter painter(this);
//    // �����͸��style�������͸����
//    if (m_style == TRANSPARENTSTYLE)
//    {
//        if (m_enter) {
//            painter.setOpacity(0.6);
//        }
//    }
//    painter.drawPixmap(0, 0, m_pic);
//}
//// ����ͼƬ
//void ClickLabel::setPixmap(const QPixmap t_pic)
//{
//    m_pic = t_pic;//������Ҫʹ�ã���bug�������Сû������
//}
//
