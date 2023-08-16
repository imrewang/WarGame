#include "PropertyTag.h"

PropertyTag::PropertyTag(QString name, int maxHp, int armor, QWidget* parent) :
    QLabel(parent),
    name(name),
    maxHp(maxHp),
    armor(armor)
{
    // ��ʼ�趨
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setMouseTracking(true);
    setFixedSize(CELL_SIZE * 3, CELL_SIZE * 2);
    QPixmap t_pixmap = QPixmap(DLG_PATH).scaled(CELL_SIZE * 3, CELL_SIZE * 3);
    setPixmap(t_pixmap);

    // ��������
    nameLabel.setText(name);
    hpLabel1.setText("Ѫ��");       
    hpLabel2.setText(QString::number(maxHp) + "/" + QString::number(maxHp));
    armorLabel1.setText("����");    
    armorLabel2.setText(QString::number(armor));
}
