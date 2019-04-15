/********************************************************************************
** Form generated from reading UI file 'event.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENT_H
#define UI_EVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Event
{
public:

    void setupUi(QDialog *Event)
    {
        if (Event->objectName().isEmpty())
            Event->setObjectName(QString::fromUtf8("Event"));
        Event->resize(400, 300);

        retranslateUi(Event);

        QMetaObject::connectSlotsByName(Event);
    } // setupUi

    void retranslateUi(QDialog *Event)
    {
        Event->setWindowTitle(QApplication::translate("Event", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Event: public Ui_Event {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENT_H
