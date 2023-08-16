#include "Piece.h"


Piece::Piece(const int cellX, const int cellY, const bool belong, QWidget* parent) :
    QLabel(parent), belong(belong),
    cellX(cellX), cellY(cellY),
    pieceState(BEGIN)
{
    // ��ʼ�趨
    setAttribute(Qt::WA_MouseNoMask, true);

    layout = new QVBoxLayout(this);

    connect(this, &Piece::beAttackedSignal, this, &Piece::beAttackedSlot);
}
// �����룬��������������
void Piece::enterEvent(QEvent*)
{
    if (propertyTag->isHidden() == true)
    {
        propertyTag->show();
        propertyTag->raise();
        // ��ʱ�ر�
        QTimer::singleShot(1500, this, [=]() {
            propertyTag->hide();
            });
    }
}
// ����Ƴ����ر�����������
void Piece::leaveEvent(QEvent*)
{
    if (propertyTag->isHidden() == false) {
        propertyTag->hide();
    }
}

void Piece::bloodLossAnimation(int decreasedHp)
{
    // ��Ѫ��
    QLabel* deductLabel = new QLabel(parentWidget());
    deductLabel->setAttribute(Qt::WA_DeleteOnClose);
    //tempLabel->setStyleSheet("color:rgb(255,40,0); font:bold; font-size:20px;");
    if (decreasedHp > 0) {
        deductLabel->setStyleSheet("color:rgb(227, 23, 13); font:bold; font-size:20px;");
        deductLabel->setText(QString("-%1").arg(decreasedHp));
    }
    else {
        deductLabel->setStyleSheet("color:rgb(0, 201, 87); font:bold; font-size:20px;");
        deductLabel->setText(QString("+%1").arg(-decreasedHp));
    }
    //tempLabel->setText(QString("-%1").arg(attrack));
    deductLabel->show();
    deductLabel->raise();
    // ��Ѫ���ϸ���ͣ���Ķ���
    QPropertyAnimation* animation = new QPropertyAnimation(deductLabel, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect((cellX - 1) * CELL_SIZE + CELL_SIZE / 4, (cellY - 1) * CELL_SIZE - 30,
        deductLabel->width(), deductLabel->height()));
    animation->setEndValue(QRect((cellX - 1) * CELL_SIZE + CELL_SIZE / 4, (cellY - 1) * CELL_SIZE - 30 - 30,
        deductLabel->width(), deductLabel->height()));
    animation->start();

    emit infoChangedSignal();
    QTimer::singleShot(1500, this, [=]() {deductLabel->close(); });
}


// ��Ҫ��������ʱ���������ݸ����ź�
void Piece::updateInfoSlot() const
{
    emit infoChangedSignal();
}



