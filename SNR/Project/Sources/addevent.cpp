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

}

void AddEvent::cancel(){
    AddEvent::close();
}
