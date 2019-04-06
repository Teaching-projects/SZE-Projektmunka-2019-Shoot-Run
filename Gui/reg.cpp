#include "reg.h"
#include <QtWidgets>


Reg::Reg(QWidget *parent) :
    QDialog(parent)
{
    QLabel *nameLabel = new QLabel(tr("Username:"));
    nameEdit = new QLineEdit;

    QLabel *passLabel = new QLabel(tr("Password:"));
    passEdit = new QLineEdit;
    passEdit->setEchoMode(QLineEdit::Password);

    QLabel *mailLabel = new QLabel(tr("E-mail:"));
    mailEdit = new QLineEdit;

    regButton = new QPushButton(tr("&Register"));
    regButton->setEnabled(true);

    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->setEnabled(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(passLabel, 1, 0);
    layout->addWidget(mailLabel, 2, 0);
    layout->addWidget(nameEdit, 0, 1);
    layout->addWidget(passEdit, 1, 1);
    layout->addWidget(mailEdit, 2, 1);
    layout->addWidget(regButton, 0, 2);
    layout->addWidget(cancelButton, 1, 2);

    setLayout(layout);
    setWindowTitle(tr("Register"));
    connect(regButton, SIGNAL(clicked()), this, SLOT(regClicked()));
    connect(regButton, SIGNAL(clicked()), this, SLOT(accept()));
}

void Reg::regClicked()
{
   /* QString nametext = nameEdit->text();
    QString passtext = passEdit->text();
    QString mailtext = mailEdit->text();*/
}
