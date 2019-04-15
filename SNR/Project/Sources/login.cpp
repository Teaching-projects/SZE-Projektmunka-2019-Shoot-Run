#include "login.h"
#include <QtWidgets>



void feltolt(QListWidget* listWidget) {
	typedef odb::query<event> query;
	typedef odb::result<event> result;

	QSharedPointer<odb::core::database> db = create_database();
	odb::session s;
	odb::core::transaction t(db->begin());

	result r(db->query<event>());

	for (result::iterator i(r.begin()); i != r.end(); ++i)
	{
		new QListWidgetItem(i->getname().append(i->getdate().toString()), listWidget);
	}
}
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

    eventdialog=new GuiEvent(this);
    addeventdialog=new AddEvent(this);
    finddialog=new FindDialog(this);


	
    listWidget=new QListWidget(this);
	feltolt(listWidget);
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
    layout->addWidget(listWidget, 0,0);
    layout->addLayout(buttonLayout, 0,1);

    setLayout(layout);
    setWindowTitle(tr("Events"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(addButton, SIGNAL(clicked()), this, SLOT(addEvent()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(selectClicked()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(findEvent()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteEvent()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editEvent()));
    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));

}

void login::selectClicked(){
    listWidget->currentItem();
   // QListWidgetItem *itm=listWidget->currentItem();
    eventSelect();
    //itm->setTextColor(Qt::red);
  //  int index=listWidget->currentIndex().row(); // megadja hányadik lett kiválasztva
    //külön esemény tömb
}

void login::eventSelect(){
    eventdialog->show();
}

void login::addEvent(){
    addeventdialog->show();
}

void login::findEvent(){
    finddialog->show();
    if (finddialog->exec() == 1) {
            QString eventName = finddialog->getFindText();
        }
}

void login::deleteEvent()
{
}

void login::editEvent(){

}

void login::logout(){
    login::close();
}
