﻿#pragma once

#include "Role.h"
#include "algorithm.h"
#include "config.h"

class GameAI : public QObject
{
    Q_OBJECT
protected:
    FindPathAlgorithm m_Al;
    int m_attrackid, m_minDist; // 要攻击的对象和没移动前距离对方棋子所有距离的最小值
    Role* m_nowCharacter; // 当前要移动的角色
    int id;
    Role** m_character; // 场上的角色的头指针
    int characterNum;
public:
    GameAI();
    void AIRound(Role* character[], int characterNum);
    // 移动某角色，传入所有角色和行动的角色
    void moveCharacter(const int id, Role* t_character[], const int CharacterNum);
protected:
    // 进行攻击操作
    void attrackCharacter() const;
    // 等待攻击结束后发送ai执行完毕指令
    void waitFunc() const;

    //int 
signals:
    void thisCharacterFinished() const; // AI移动一个棋子结束
    void oneAttackOverSignal()const;
};
