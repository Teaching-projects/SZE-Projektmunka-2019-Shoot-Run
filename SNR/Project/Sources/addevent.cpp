#include "addevent.h"
#include <QtWidgets>

AddEvent::AddEvent(QWidget *parent) :
    QDialog(parent)
{
    QLabel *nameLabel=new QLabel(tr("Name:"));
    nameLine=new QLineEdit;
    QLabel *dateLabel=new QLabel(tr("Date:"));
    dateLine = new QDateEdit;

    addButton = new QPushButton(tr("&Add"));
    addButton->setEnabled(true);

    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->setEnabled(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameLine,0,1);
    layout->addWidget(dateLabel,1,0);
    layout->addWidget(dateLine,1,1);
    layout->addWidget(addButton, 2,0);
    layout->addWidget(cancelButton, 2,1);

    setLayout(layout);
    setWindowTitle(tr("Add Event"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
}

void AddEvent::cancel(){
    AddEvent::close();
}


void AddEvent::add() {
	addEvent(nameLine->text().toStdString(), QDateTime(dateLine->date()));
}


int AddEvent::addEvent(std::string name, QDateTime date)
{
	DB TODO;
	QSharedPointer<odb::core::database> db = TODO.create_database();
	typedef odb::query<class::event> query;
	typedef odb::result<class::event> result;
	odb::session s;
	odb::core::transaction t(db->begin());
	result r(db->query<class::event>(query::event_name == name));
	if (!r.empty()) {
		QMessageBox::information(this, tr("Error"), tr("Event name already used"));
		return 0;
	}
	else {
		class::event new_event(name, date);
		//new_event->user(); TODO
		db->persist(new_event);
		t.commit();
		return 1;
	}
}


