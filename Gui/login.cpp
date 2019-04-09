#include "login.h"
#include <QtWidgets>

login::login(QWidget *parent) :
    QDialog(parent)
{
    selectButton = new QPushButton(tr("&Select"));
    selectButton->setEnabled(true);

    addButton = new QPushButton(tr("&Add"));
    addButton->setEnabled(true);

    deleteButton = new QPushButton(tr("&Delete"));
    deleteButton->setEnabled(true);

    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(true);

    searchButton = new QPushButton(tr("&Search"));
    searchButton->setEnabled(true);

    logoutButton = new QPushButton(tr("&Logout"));
    logoutButton->setEnabled(true);

    eventdialog=new Event(this);
    addeventdialog=new AddEvent(this);

    listWidget=new QListWidget(this);
    new QListWidgetItem(tr("100m"), listWidget);
    new QListWidgetItem(tr("Marathon"), listWidget);
    new QListWidgetItem(tr("Tájfutás"), listWidget);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(selectButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(logoutButton);

    QGridLayout *layout = new QGridLayout;
   /* layout->addWidget(selectButton, 0,1);
    layout->addWidget(addButton, 1,1);
    layout->addWidget(deleteButton, 2,1);
    layout->addWidget(editButton, 3,1);
    layout->addWidget(searchButton, 4,1);
    layout->addWidget(logoutButton, 5,1);*/
    layout->addWidget(listWidget, 0,0);
    layout->addLayout(buttonLayout, 0,1);

    setLayout(layout);
    setWindowTitle(tr("Login"));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addEvent()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(selectClicked()));

}

void login::selectClicked(){
    listWidget->currentItem();
    QListWidgetItem *itm=listWidget->currentItem();
    eventSelect();
    itm->setTextColor(Qt::red);
}

void login::eventSelect(){
    eventdialog->show();
}

void login::addEvent(){
    addeventdialog->show();
}


