#pragma once

#include "Piece.h"
#include "animation.h"
#include "RoleProperty.h"
#include "RoleSelection.h"

class Role : public Piece
{
    Q_OBJECT

public:
    Role(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);

public:
    MoveAnimation* moveAnimation; // 移动动画播放器
    AttrackAnimation* attackAnimation; // 攻击动画播放器
    RoleSelection* selection; // 人物操作选择栏

    int  curMove, maxMove, attackPoints, attackRange; // 人物各项属性
public:
    // 给予路径，调动MoveAnimation播放移动的动画
    void movePos(const int steps, const std::vector<int>& path);
public slots:
    // 被攻击时伤害结算，attrack是被攻击的攻击点数
    void beAttackedSlot(const int attackPoints) override;
    // 人物需要移动，连接到GameScene的寻路显示上
    void roleMoveSlot();
    // 人物需要攻击，连接到GameScene的攻击显示上
    void roleAttackSlot();
    // 跳过选择，向GameScene说明有人结束
    void roleSkipSlot();
signals:
    // 人物移动
    void roleMoveSignal(Role*)const;
    // 人物进攻
    void roleAttackSignal(Role*)const;
    // 人物结束当前回合
    void roleSkipSignal(Role*)const;
    // 棋子死亡
    void killRoleSignal(Role*)const;
    // 需要发送HintLabel
    void displayHintLabelSignal(QString)const;
    // 隐藏“取消”键
    void hideCancelButtonSignal()const;
};
