/********************************************************************************
** Form generated from reading UI file 'guievent.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIEVENT_H
#define UI_GUIEVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_guievent
{
public:

    void setupUi(QDialog *guievent)
    {
        if (guievent->objectName().isEmpty())
            guievent->setObjectName(QString::fromUtf8("guievent"));
        guievent->resize(640, 480);

        retranslateUi(guievent);

        QMetaObject::connectSlotsByName(guievent);
    } // setupUi

    void retranslateUi(QDialog *guievent)
    {
        guievent->setWindowTitle(QApplication::translate("guievent", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guievent: public Ui_guievent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIEVENT_H
