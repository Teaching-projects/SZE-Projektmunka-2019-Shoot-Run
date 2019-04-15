/********************************************************************************
** Form generated from reading UI file 'uploadpic.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADPIC_H
#define UI_UPLOADPIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_UploadPic
{
public:

    void setupUi(QDialog *UploadPic)
    {
        if (UploadPic->objectName().isEmpty())
            UploadPic->setObjectName(QString::fromUtf8("UploadPic"));
        UploadPic->resize(400, 300);

        retranslateUi(UploadPic);

        QMetaObject::connectSlotsByName(UploadPic);
    } // setupUi

    void retranslateUi(QDialog *UploadPic)
    {
        UploadPic->setWindowTitle(QApplication::translate("UploadPic", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UploadPic: public Ui_UploadPic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADPIC_H
