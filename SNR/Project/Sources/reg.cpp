#include "reg.h"
#include <QtWidgets>
#include "gui.h"

Reg::Reg(QWidget *parent) :
    QDialog(parent)
{
	QLabel *fnameLabel = new QLabel(tr("Firstname:"));
	fnameEdit = new QLineEdit;
	QLabel *lnameLabel = new QLabel(tr("Lastname:"));
	lnameEdit = new QLineEdit;
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
	layout->addWidget(fnameLabel, 0, 0);
	layout->addWidget(fnameEdit, 0, 1);
	layout->addWidget(lnameLabel, 1, 0);
	layout->addWidget(lnameEdit, 1, 1);
	layout->addWidget(nameLabel, 2, 0);
	layout->addWidget(passLabel, 3, 0);
	layout->addWidget(mailLabel, 4, 0);
	layout->addWidget(nameEdit, 2, 1);
	layout->addWidget(passEdit, 3, 1);
	layout->addWidget(mailEdit, 4, 1);
	layout->addWidget(regButton, 0, 2);
	layout->addWidget(cancelButton, 1, 2);
    setLayout(layout);
    setWindowTitle(tr("Register"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(regButton, SIGNAL(clicked()), this, SLOT(regClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void Reg::regClicked(){
	if (user_registration(nameEdit->text().toStdString(), passEdit->text().toStdString(), fnameEdit->text().toStdString(), lnameEdit->text().toStdString(), mailEdit->text().toStdString()))
	{
		cancel();
	}
	else
	{
		QMessageBox::information(this, tr("Error"), tr("Foglalt"));
	}

}

void Reg::cancel(){
    close();
}
