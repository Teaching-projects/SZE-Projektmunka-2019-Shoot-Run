#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QMap>
#include "finddialog.h"
#include <QDateEdit>
#include <QDate>
#include <QLocale>

class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;

class Event : public QWidget
{
    Q_OBJECT

public:
    Event(QWidget *parent = 0);
    enum Mode { NavigationMode, AddingMode, EditingMode };

public slots:
    void addContact();
    void editContact();
    void submitContact();
    void cancel();
    void removeContact();
    void findContact();
    void next();
    void previous();
    void saveToFile();
    void loadFromFile();

private:
    void updateInterface(Mode mode);

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QLineEdit *nameLine;
    QDateEdit *dateLine;

    QMap<QString, QDate> contacts;
    FindDialog *dialog;
    QString oldName;
    QDate oldDate;
    Mode currentMode;
};

#endif
