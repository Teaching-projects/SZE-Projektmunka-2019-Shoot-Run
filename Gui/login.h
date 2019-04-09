#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <event.h>
#include <addevent.h>

class QPushButton;
class QLineEdit;
class QListWidget;

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);

private slots:
    void selectClicked();

private:
    QPushButton *selectButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *searchButton;
    QPushButton *logoutButton;
    QListWidget *listWidget;

    Event *eventdialog;
    AddEvent *addeventdialog;

public slots:
    void eventSelect();
    void addEvent();

};

#endif // LOGIN_H
