#include "Tutorial.h"


/*  GuideScene是关于教程页面 的类*/

Tutorial::Tutorial(QWidget* parent) :
    QDialog(parent)
{
    // 初始化
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle(QString("欧陆战争"));

    pageNum = 0;

    pagePic[0] = QPixmap(GUIDE1_PATH).scaled(WINDOW_WIDTH, WINDOW_HEIGHT);
    pagePic[1] = QPixmap(GUIDE2_PATH).scaled(WINDOW_WIDTH, WINDOW_HEIGHT);
    pagePic[2] = QPixmap(GUIDE3_PATH).scaled(WINDOW_WIDTH, WINDOW_HEIGHT);
    pagePic[3] = QPixmap(GUIDE4_PATH).scaled(WINDOW_WIDTH, WINDOW_HEIGHT);
    pagePic[4] = QPixmap(GUIDE5_PATH).scaled(WINDOW_WIDTH, WINDOW_HEIGHT);
    pagePic[5] = QPixmap(GUIDE6_PATH).scaled(WINDOW_WIDTH, WINDOW_HEIGHT);

}
void Tutorial::mousePressEvent(QMouseEvent*)
{
    // 点击翻页
    pageNum++;
    repaint();
}
void Tutorial::paintEvent(QPaintEvent*)
{
    // 如果到达尾页则退回游戏首页，否则显示
    QPainter painter(this);
    if (pageNum == 6) {
        pageNum = 0;

        parentWidget()->show();

        QTime delayTime = QTime::currentTime().addMSecs(300);//延时300毫秒
        while (QTime::currentTime() < delayTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        
        this->hide();
        return;
    }
    painter.drawPixmap(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, pagePic[pageNum]);
}
