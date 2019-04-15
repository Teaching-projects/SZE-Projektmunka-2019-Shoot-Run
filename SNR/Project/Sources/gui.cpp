#include "gui.h"
#include <QtWidgets>


gui::gui(QWidget *parent) : QWidget(parent)
{
    QLabel *unameLabel=new QLabel(tr("Username:"));
    unameLine=new QLineEdit;
    QLabel *passLabel = new QLabel(tr("Password:"));
    passLine = new QLineEdit;
    passLine->setEchoMode(QLineEdit::Password);
    regButton = new QPushButton(tr("&Register"));
    regButton->setEnabled(true);
    logButton = new QPushButton(tr("&Login"));
    logButton->setEnabled(true);
    regdialog=new Reg(this);
    logdialog=new login(this);
     connect(regButton, SIGNAL(clicked()), this, SLOT(regUser()));
	 connect(logButton, SIGNAL(clicked()), this, SLOT(logUser()));
     QVBoxLayout *buttonLayout1 = new QVBoxLayout;
     buttonLayout1->addWidget(regButton);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(unameLabel, 0, 0);
    mainLayout->addWidget(unameLine, 0, 1);
    mainLayout->addWidget(passLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(passLine, 1, 1);
    mainLayout->addWidget(logButton, 0, 2);
    mainLayout->addWidget(regButton, 1, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("Shoot&Run"));
}


void gui::logUser()
{
	if(!user_login(unameLine->text().toStdString(), passLine->text().toStdString()))
		QMessageBox::information(this, tr("Error"), tr("Please enter a valid data."));
	else
    logdialog->show();
}


void gui::regUser()
{
    regdialog->show();
}



