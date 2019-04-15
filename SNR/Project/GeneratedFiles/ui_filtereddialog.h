/********************************************************************************
** Form generated from reading UI file 'filtereddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTEREDDIALOG_H
#define UI_FILTEREDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_FilteredDialog
{
public:

    void setupUi(QDialog *FilteredDialog)
    {
        if (FilteredDialog->objectName().isEmpty())
            FilteredDialog->setObjectName(QString::fromUtf8("FilteredDialog"));
        FilteredDialog->resize(640, 480);

        retranslateUi(FilteredDialog);

        QMetaObject::connectSlotsByName(FilteredDialog);
    } // setupUi

    void retranslateUi(QDialog *FilteredDialog)
    {
        FilteredDialog->setWindowTitle(QApplication::translate("FilteredDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilteredDialog: public Ui_FilteredDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTEREDDIALOG_H
