/********************************************************************************
** Form generated from reading UI file 'addevent.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEVENT_H
#define UI_ADDEVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AddEvent
{
public:

    void setupUi(QDialog *AddEvent)
    {
        if (AddEvent->objectName().isEmpty())
            AddEvent->setObjectName(QString::fromUtf8("AddEvent"));
        AddEvent->resize(400, 300);

        retranslateUi(AddEvent);

        QMetaObject::connectSlotsByName(AddEvent);
    } // setupUi

    void retranslateUi(QDialog *AddEvent)
    {
        AddEvent->setWindowTitle(QApplication::translate("AddEvent", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddEvent: public Ui_AddEvent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEVENT_H
