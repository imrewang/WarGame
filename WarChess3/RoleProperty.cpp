#include "RoleProperty.h"

RoleProperty::RoleProperty(QString name, int maxHp, int maxMove, int attackPoints, int attackRange, int armor, QWidget* parent)
	:PropertyTag(name,maxHp,armor,parent),
	maxMove(maxMove),
	attackPoints(attackPoints),
	attackRange(attackRange)
{

    moveLabel1.setText("�ж���");
    moveLabel2.setText(QString::number(maxMove) + "/" + QString::number(maxMove));
    attackPointsLabel1.setText("������");
    attackPointsLabel2.setText(QString::number(attackPoints));
    attackRangeLabel1.setText("������Χ");
    attackRangeLabel2.setText(QString::number(attackRange));


    // �����Լ���layout
    propertyLayout.addWidget(&nameLabel, 0, 0);
    propertyLayout.addWidget(&hpLabel1, 1, 0);
    propertyLayout.addWidget(&hpLabel2, 1, 1);
    propertyLayout.addWidget(&moveLabel1, 2, 0);
    propertyLayout.addWidget(&moveLabel2, 2, 1);
    propertyLayout.addWidget(&attackPointsLabel1, 3, 0);
    propertyLayout.addWidget(&attackPointsLabel2, 3, 1);
    propertyLayout.addWidget(&attackRangeLabel1, 4, 0);
    propertyLayout.addWidget(&attackRangeLabel2, 4, 1);
    propertyLayout.addWidget(&armorLabel1, 5, 0);
    propertyLayout.addWidget(&armorLabel2, 5, 1);
    propertyLayout.setVerticalSpacing(0);
    setLayout(&propertyLayout);
}

void RoleProperty::updatePropertyData(const int curHp, const int curMove, const int localCellX, const int localCellY)
{
    // Ѱ����������ʾλ��
    int x;
    if ((localCellX - 1) * CELL_SIZE - CELL_SIZE * 3 >= 0) {
        x = (localCellX - 1) * CELL_SIZE - CELL_SIZE * 3;
    }
    else {
        x = (localCellX - 1) * CELL_SIZE + 32;
    }
    move(x, (localCellY - 1) * CELL_SIZE);
    moveLabel2.setText(QString::number(curMove) + "/" + QString::number(maxMove));

    // ����HP����
    hpLabel2.setText(QString::number(curHp) + "/" + QString::number(maxHp));

    if (isHidden()) {
        hide();
    }
    else {
        show();
    }
}

