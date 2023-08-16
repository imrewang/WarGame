#include "RoleSelection.h"

RoleSelection::RoleSelection(QWidget* parent)
    : QLabel(parent)
{
    // 为三个操作按键设置layout
    selectionLayout = new QVBoxLayout;

    moveButton = new QPushButton;
    attackButton = new QPushButton;
    skipButton = new QPushButton;

    setFixedSize(90, 90);

    // 设置文字
    moveButton->setText("移动");
    attackButton->setText("攻击");
    skipButton->setText("跳过");
    selectionLayout->addWidget(moveButton);
    selectionLayout->addWidget(attackButton);
    selectionLayout->addWidget(skipButton);
    selectionLayout->setSpacing(0);

    setLayout(selectionLayout);
}

// 更新人物操作栏信息，也即更新显示位置
void RoleSelection::updateSelectionData(const int localCellx, const int localCelly)
{
    move(localCellx * CELL_SIZE - 10, (localCelly - 1) * CELL_SIZE - 10);
    if (isHidden()) {
        hide();
    }
    else
    {
        show();
        raise();
    }
}
