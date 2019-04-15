#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <guievent.h>
#include <addevent.h>
#include <finddialog.h>

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

    GuiEvent *eventdialog;
    AddEvent *addeventdialog;
    FindDialog *finddialog;

public slots:
    void eventSelect();
    void addEvent();
    void findEvent();
    void deleteEvent();
    void editEvent();
    void logout();

};

#endif // LOGIN_H
