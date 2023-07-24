/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainSceneClass
{
public:

    void setupUi(QWidget *MainSceneClass)
    {
        if (MainSceneClass->objectName().isEmpty())
            MainSceneClass->setObjectName(QString::fromUtf8("MainSceneClass"));
        MainSceneClass->resize(600, 400);

        retranslateUi(MainSceneClass);

        QMetaObject::connectSlotsByName(MainSceneClass);
    } // setupUi

    void retranslateUi(QWidget *MainSceneClass)
    {
        MainSceneClass->setWindowTitle(QCoreApplication::translate("MainSceneClass", "MainScene", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainSceneClass: public Ui_MainSceneClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H
