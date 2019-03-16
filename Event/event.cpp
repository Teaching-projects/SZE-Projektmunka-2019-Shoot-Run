#include <QtWidgets>
#include "event.h"

Event::Event(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);

    QLabel *dateLabel = new QLabel(tr("Date:"));
    dateLine = new QDateEdit;
    dateLine->setReadOnly(true);

    addButton = new QPushButton(tr("&Add"));

    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();

    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);

    loadButton = new QPushButton(tr("&Load..."));
    loadButton->setToolTip(tr("Load contacts from a file"));
    saveButton = new QPushButton(tr("&Save..."));
    saveButton->setToolTip(tr("Save contacts to a file"));
    saveButton->setEnabled(false);

    dialog = new FindDialog(this);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitContact()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editContact()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findContact()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(previous()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(saveButton);
    buttonLayout1->addStretch();

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(dateLabel, 1, 0);
    mainLayout->addWidget(dateLine, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 2, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("Events"));
}

void Event::addContact()
{
    oldName = nameLine->text();
    oldDate = dateLine->date();

    nameLine->clear();


    updateInterface(AddingMode);
}

void Event::editContact()
{
    oldName = nameLine->text();
    oldDate = dateLine->date();

    updateInterface(EditingMode);
}

void Event::submitContact()
{
    QString name = nameLine->text();
    QDate date = dateLine->date();

    if (name.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a name and date."));
        return;
    }

    if (currentMode == AddingMode) {

        if (!contacts.contains(name)) {
            contacts.insert(name, date);
            QMessageBox::information(this, tr("Add Successful"),
                tr("\"%1\" has been added to your address book.").arg(name));
        } else {
            QMessageBox::information(this, tr("Add Unsuccessful"),
                tr("Sorry, \"%1\" is already in your address book.").arg(name));
        }
    } else if (currentMode == EditingMode) {

        if (oldName != name) {
            if (!contacts.contains(name)) {
                QMessageBox::information(this, tr("Edit Successful"),
                    tr("\"%1\" has been edited in your address book.").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name, date);
            } else {
                QMessageBox::information(this, tr("Edit Unsuccessful"),
                    tr("Sorry, \"%1\" is already in your address book.").arg(name));
            }
        } else if (oldDate != date) {
            QMessageBox::information(this, tr("Edit Successful"),
                tr("\"%1\" has been edited in your address book.").arg(name));
            contacts[name] = date;
        }
    }

    updateInterface(NavigationMode);
}

void Event::cancel()
{
    nameLine->setText(oldName);
    dateLine->setDate(oldDate);
    updateInterface(NavigationMode);
}

void Event::removeContact()
{
    QString name = nameLine->text();
    QDate date = dateLine->date();

    if (contacts.contains(name)) {

        int button = QMessageBox::question(this,
            tr("Confirm Remove"),
            tr("Are you sure you want to remove \"%1\"?").arg(name),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {

            previous();
            contacts.remove(name);

            QMessageBox::information(this, tr("Remove Successful"),
                tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }

    updateInterface(NavigationMode);
}

void Event::next()
{
    QString name = nameLine->text();
    QMap<QString, QDate>::iterator i = contacts.find(name);

    if (i != contacts.end())
        i++;

    if (i == contacts.end())
        i = contacts.begin();

    nameLine->setText(i.key());
    dateLine->setDate(i.value());
}

void Event::previous()
{
    QString name = nameLine->text();
    QMap<QString, QDate>::iterator i = contacts.find(name);

    if (i == contacts.end()) {
        nameLine->clear();

        return;
    }

    if (i == contacts.begin())
        i = contacts.end();

    i--;
    nameLine->setText(i.key());
    dateLine->setDate(i.value());
}

void Event::findContact()
{
    dialog->show();

    if (dialog->exec() == 1) {
        QString contactName = dialog->getFindText();

        if (contacts.contains(contactName)) {
            nameLine->setText(contactName);
            dateLine->setDate(contacts.value(contactName));
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
            return;
        }
    }

    updateInterface(NavigationMode);
}

void Event::updateInterface(Mode mode)
{
    currentMode = mode;

    switch (currentMode) {

    case AddingMode:
    case EditingMode:

        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        dateLine->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);

        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();

        loadButton->setEnabled(false);
        saveButton->setEnabled(false);
        break;

    case NavigationMode:

        if (contacts.isEmpty()) {
            nameLine->clear();

        }

        nameLine->setReadOnly(true);
        dateLine->setReadOnly(true);
        addButton->setEnabled(true);

        int number = contacts.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        findButton->setEnabled(number > 2);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number > 1);

        submitButton->hide();
        cancelButton->hide();

        loadButton->setEnabled(true);
        saveButton->setEnabled(number >= 1);
        break;
    }
}

void Event::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Events"), "",
        tr("Address Book (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream out(&file);
        for(auto e : contacts.keys())
        {
          out << e << " " << contacts.value(e).toString("yyyy.MM.dd")<<'\n';
        }
    }
}

void Event::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream in(&file);
        contacts.clear();
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(" ");
            QDate Date = QDate::fromString(fields.at(1),"yyyy.MM.dd");
            contacts.insert(fields.at(0),Date);
        }
        QMap<QString, QDate>::iterator i = contacts.begin();
        nameLine->setText(i.key());
        dateLine->setDate(i.value());
    }

    updateInterface(NavigationMode);
}
