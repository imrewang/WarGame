#include "RoleSelection.h"

RoleSelection::RoleSelection(QWidget* parent)
    : QLabel(parent)
{
    // Ϊ����������������layout
    selectionLayout = new QVBoxLayout;

    moveButton = new QPushButton;
    attackButton = new QPushButton;
    skipButton = new QPushButton;

    setFixedSize(90, 90);

    // ��������
    moveButton->setText("�ƶ�");
    attackButton->setText("����");
    skipButton->setText("����");
    selectionLayout->addWidget(moveButton);
    selectionLayout->addWidget(attackButton);
    selectionLayout->addWidget(skipButton);
    selectionLayout->setSpacing(0);

    setLayout(selectionLayout);
}

// ���������������Ϣ��Ҳ��������ʾλ��
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
