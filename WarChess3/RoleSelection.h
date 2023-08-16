#pragma once

#include <QLabel>
#include "config.h"

class RoleSelection : public QLabel
{
    Q_OBJECT
public:
    explicit RoleSelection(QWidget* parent = nullptr);
public:
    QVBoxLayout* selectionLayout;
    QPushButton* moveButton, * attackButton, * skipButton; // 操作栏上三个按钮
    // 更新操作栏数据
    void updateSelectionData(const int localCellx, const int localCelly); // 更新数据
};

