#pragma once

#include "ClickLabel.h"
#include "gamemap.h"
#include "VariousRoles.h"
#include "config.h"
#include "algorithm.h"
#include "aicontroller.h"
#include "animation.h"
#include "playingmenu.h"
#include "base.h"
#include <QApplication>
#include <QPixmap>
#include <QScreen>

class GameScene : public QDialog
{
    Q_OBJECT

private:
    void interfaceInit();

public:
    enum GAMESTATE { START, NAVIGATE, SEARCH_ENEMIES, AI, END };
    explicit GameScene(const int gameMode, QWidget* parent = nullptr);
    ~GameScene();
protected:
    FindPathAlgorithm moveAl, attrackAl; // 移动可行域和攻击可行域的算法类

    void paintEvent(QPaintEvent*)override; // 绘制函数
    void mouseMoveEvent(QMouseEvent*)override; // 鼠标移动函数
    void mousePressEvent(QMouseEvent*)override; // 鼠标点击函数
    bool eventFilter(QObject*, QEvent*)override; // 对Character事件过滤

    void setScreenMoveTimer();  // 设置屏幕移动判断的QTimer

    void setButtons(); // 设置屏幕左上角四个按钮

    void createRoles(); // 初始创建人物
    void createBases();  //创建双方基地

    void reviveRole(int id); //复活序号为id的人物

    void updateMousePosition(QMouseEvent*);

    void nextRound(const int last); // 到达下一局，进行初始化

    void startAIRound()const; // 启动AI回合
    void invokeAIController(const int id); // 调用aicontroller以完成ai回合

protected:
    GameMap gameMap; // GameMap数据

    int mouseX, mouseY; // 当前鼠标坐标（地图上的像素）
    int mouseGridX, mouseGridY; // 当前鼠标坐标（地图上的格子）

    Role* rolesArray[10], * currentRole; // 储存人物和当前人物
    Base* RedBase, * BlueBase, * EnemyBase;

    int roundNum;  //记录到第几轮游戏
    int waitRevivedRoles[10];
    int totalRolesNum; // 人物总数
    int gameState; // 当前游戏状态，详见GAMESTATE枚举变量

    int aliveNum[2]; // 场上存活人物总数，0、1参考BELONGING枚举变量
    int canMoveNum[2]; // 本局剩余可行人数，0、1参考BELONGING枚举变量

    bool roundBelong; // 本局属于何方，0、1参考BELONGING枚举变量
    bool isAIOpen; // AI是否开启

    ClickLabel* cancelButton, * skipButton, * menuButton, * musicButton; // 屏幕右下角四个按钮
    HintLabel* hintLabel; // 提示框
    AIController* aiController; // AI控制者

    QSound* backgroundMusic, * attackSound, * clickSound; // 各种音乐音效

    MoveAnimation* moveAnimationManager; // 移动动画管理器
    PlayingMenu* playingMenu; // 游戏菜单
    ResultMenu* resultMenu; // 游戏结果菜单

signals:

    void myLossSignal()const; void myWinSignal()const; // 输赢信号

    void restartSignal()const; void exitSignal()const; // 重新开始游戏/退出信号

public slots:
    void redrawRoleSlot()const; // 重绘人物
    void redrawBaseSlot()const; //重绘基地

    void findPathSlot(Role*); // 人物坐标移动
    void findEnemiesSlot(Role*); // 处理人物攻击事件

    void roleEndSlot(Role*); // 处理人物回合结束事件

    void roleDiesSlot(Role*); // 处理人物死亡事件
    void baseDestroyedSlot(Base*); //处理基地死亡事件

    void showHintSlot(const QString str,const bool next)const;// 给出提示框 
    void showHintSlot(QString str);// 给出提示框 
};
