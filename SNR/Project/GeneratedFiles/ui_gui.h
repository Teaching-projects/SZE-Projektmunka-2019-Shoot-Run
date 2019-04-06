/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guiClass
{
public:

    void setupUi(QWidget *guiClass)
    {
        if (guiClass->objectName().isEmpty())
            guiClass->setObjectName(QString::fromUtf8("guiClass"));
        guiClass->resize(600, 400);

        retranslateUi(guiClass);

        QMetaObject::connectSlotsByName(guiClass);
    } // setupUi

    void retranslateUi(QWidget *guiClass)
    {
        guiClass->setWindowTitle(QApplication::translate("guiClass", "gui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guiClass: public Ui_guiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
