#pragma once

#include <QDialog>
#include "config.h"
#include<QTime>
#include<QCoreApplication>

class Tutorial : public QDialog
{
	Q_OBJECT
protected:
	int pageNum; // 记录页数
	QPixmap pagePic[6]; // 记每页图片
public:
	explicit Tutorial(QWidget* parent = nullptr);
protected:
	void mousePressEvent(QMouseEvent*)override;
	void paintEvent(QPaintEvent*)override;
};
