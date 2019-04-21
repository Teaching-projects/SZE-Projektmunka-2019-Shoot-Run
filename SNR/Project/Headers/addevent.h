#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>
#include <QWidget>
#include "database.h"
#include "event-odb.hxx"

class event;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QDateEdit;

class AddEvent : public QDialog, public DB
{
    Q_OBJECT

public:
    explicit AddEvent(QWidget *parent = nullptr);
	int addEvent(std::string, QDateTime);
private:
    QPushButton *addButton;
    QPushButton *cancelButton;
    QLineEdit *nameLine;
    QDateEdit *dateLine;

public slots:
    void cancel();
	void add();
};

#endif // ADDEVENT_H
