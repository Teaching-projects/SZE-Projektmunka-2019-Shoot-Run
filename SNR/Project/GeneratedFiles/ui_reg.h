/********************************************************************************
** Form generated from reading UI file 'reg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REG_H
#define UI_REG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Reg
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *regButton;

    void setupUi(QDialog *Reg)
    {
        if (Reg->objectName().isEmpty())
            Reg->setObjectName(QString::fromUtf8("Reg"));
        Reg->resize(400, 300);
        buttonBox = new QDialogButtonBox(Reg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        regButton = new QPushButton(Reg);
        regButton->setObjectName(QString::fromUtf8("regButton"));
        regButton->setGeometry(QRect(70, 200, 75, 23));

        retranslateUi(Reg);
        QObject::connect(buttonBox, SIGNAL(accepted()), Reg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Reg, SLOT(reject()));

        QMetaObject::connectSlotsByName(Reg);
    } // setupUi

    void retranslateUi(QDialog *Reg)
    {
        Reg->setWindowTitle(QApplication::translate("Reg", "Dialog", nullptr));
        regButton->setText(QApplication::translate("Reg", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Reg: public Ui_Reg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_H
