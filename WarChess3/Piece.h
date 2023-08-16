#pragma once

#include <QLabel>
#include <QWidget>
#include "config.h"
#include "HPLabel.h"
#include "PropertyTag.h"



class Piece : public QLabel
{
	Q_OBJECT

public:
	enum PIECESTATE { BEGIN, FIND_PATH, FIND_ENEMIES, FINISH, DEAD };

public:
	Piece(const int cellX, const int cellY, const bool belong, QWidget* parent = nullptr);

public:
	PIECESTATE pieceState; // ����״̬����ö�ٱ���
	bool belong;
	int cellX, cellY;
	QVBoxLayout* layout;

	QPixmap icon; // ����ͼ��
	QString name; // ��������
	HPLabel* hpLabel; // Ѫ��

	int curHp, maxHp, armor;    //���ӵ�Ѫ���ͻ�������
	PropertyTag* propertyTag;    //����������

public:
	// �����룬����������
	void enterEvent(QEvent*)override;
	// ����Ƴ����ر�������
	void leaveEvent(QEvent*)override;

	void bloodLossAnimation(int decreasedHp);

public slots:
	// ������ʱ�˺����㣬attrack�Ǳ������Ĺ�������
	virtual void beAttackedSlot(const int attackPoints) = 0;
	// ��Ҫ��������ʱ���������ݸ����ź�
	void updateInfoSlot()const;

signals:
	// ������Ϣ�ı�
	void infoChangedSignal()const;
	// ������
	void beAttackedSignal(int attackPoints)const;
	// �ػ�����Ļ
	void repaintScreenSignal()const;
};