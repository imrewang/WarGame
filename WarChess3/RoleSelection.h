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
    QPushButton* moveButton, * attackButton, * skipButton; // ��������������ť
    // ���²���������
    void updateSelectionData(const int localCellx, const int localCelly); // ��������
};

