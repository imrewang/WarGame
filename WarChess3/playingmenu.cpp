 #include "playingmenu.h"

/* 此文件包含PlayingMenu和ResultMenu两个类
 * PlayingMenu显示游戏进行中的菜单
 * ResultMenu显示游戏结束后的菜单
 */

PlayingMenu::PlayingMenu(QWidget* parent) : QWidget(parent)
{
    // 设置默认值
    setWindowFlags(Qt::WindowCloseButtonHint);
    //setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    m_shadowDlg = new QWidget(this);

    QString str("QWidget{background-color:rgba(0,0,0,0.6);}");
    m_shadowDlg->setStyleSheet(str);
    m_shadowDlg->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 设置三个按钮
    QPixmap button_pixmap = QPixmap("pic/EW/but2.png");

    m_button[0] = new ClickLabel(350, 140, button_pixmap, this, ClickLabel::TRANSPARENTSTYLE,"返回游戏");
    m_button[1] = new ClickLabel(350, 140, button_pixmap, this, ClickLabel::TRANSPARENTSTYLE,"重新开始");
    m_button[2] = new ClickLabel(350, 140, button_pixmap, this, ClickLabel::TRANSPARENTSTYLE,"回到主页");

    for (int i = 0; i < 3; i++)
    {
        //m_button[i]->setGeometry(650, 200 + 200 * i, 300, 120);
        m_button[i]->move(650, 200 + 200 * i);
        m_button[i]->raise();
    }

    // 按下第一个按钮：继续游戏
    connect(m_button[0], &ClickLabel::clickedSignal, this, &PlayingMenu::hide, Qt::UniqueConnection);
    // 按下第二个按钮：发送重新开始游戏信号
    connect(m_button[1], &ClickLabel::clickedSignal, this, [=]() {emit restartGame(); }, Qt::UniqueConnection);
    // 按下第三个按钮：发送退出游戏信号
    connect(m_button[2], &ClickLabel::clickedSignal, this, [=]() {emit exitGame(); }, Qt::UniqueConnection);
}

////////////////////////////////////////////////////////////////////////////////////////

ResultMenu::ResultMenu(QWidget* parent) :
    QWidget(parent)
{
    // 设置三个按钮
    QPixmap TPixmap = QPixmap(MAIN_SCENE_BUTTON_PATH);
    QPixmap exitPixmap = QPixmap("/pic/exit_game.png");

    m_button[0] = new ClickLabel(400, 150, TPixmap, this, ClickLabel::TRANSPARENTSTYLE,"重新开始");
    m_button[1] = new ClickLabel(400, 150, TPixmap, this, ClickLabel::TRANSPARENTSTYLE,"回到主页");

    for (int i = 0; i < 2; i++)
    {
        //m_button[i]->setGeometry(700, 500 + 150 * i, 200, 80);
        m_button[i]->move(600, 300 + 300 * i);
        m_button[i]->raise();
    }
    // 按下第一个按钮：重新开始游戏
    connect(m_button[0], &ClickLabel::clickedSignal, this, [=]() {emit restartGame(); }, Qt::UniqueConnection);
    // 按下第二个按钮：退出游戏
    connect(m_button[1], &ClickLabel::clickedSignal, this, [=]() {emit exitGame(); }, Qt::UniqueConnection);

}
// 显示结果
void ResultMenu::setResult(const bool blueWinOrNot, const bool AIOpenOrNot)
{
    //setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // 加阴影遮罩
    m_shadowDlg = new QWidget(this);
    QString str("QWidget{background-color:rgba(0,0,0,0.6);}");
    m_shadowDlg->setStyleSheet(str);
    m_shadowDlg->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    //m_shadowDlg->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    m_resultLabel = new HintLabel(this);

    // 显示按钮
    for (int i = 0; i < 2; i++) {
        m_button[i]->raise();
    }
    // 显示提示框
    if (AIOpenOrNot)
    {
        if (blueWinOrNot) {
            m_resultLabel->setText("您获胜了！");
        }
        else {
            m_resultLabel->setText("您失败了！");
        }
    }
    else
    {
        if (blueWinOrNot) {
            m_resultLabel->setText("蓝方获胜");
        }
        else {
            m_resultLabel->setText("红方获胜");
        }
    }
    m_resultLabel->show();
}
