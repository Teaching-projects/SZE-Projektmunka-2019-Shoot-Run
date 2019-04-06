#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QListWidget;

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);

private slots:
    void logClicked();
    void selectClicked();

private:
    QPushButton *selectButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *searchButton;
    QPushButton *logoutButton;
    QListWidget *listWidget;



};

#endif // LOGIN_H
