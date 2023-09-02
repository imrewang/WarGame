#pragma once

#include "GameScene.h"
#include "config.h"
#include <QTime>
#include <QSharedPointer>
#include "Tutorial.h"
#include <QWidget>

class HomePage :public QDialog
{
   
public:
    enum GAMEMODE { SINGLE_PLAYER = 1, TWO_PLAYER = 0 };

    explicit HomePage(QWidget* parent = nullptr);
protected:
    GameScene* gameScene;
    Tutorial* tutorial; // 教程场景
    QPixmap background; // 主页图片

    ClickLabel* homeButton[3]; // 主页上三个选择案件

    GAMEMODE gameMode;
    QSound* homeBGM;
protected:
    void paintEvent(QPaintEvent*)override;
    void createGameScene(const int gameMode);
};
