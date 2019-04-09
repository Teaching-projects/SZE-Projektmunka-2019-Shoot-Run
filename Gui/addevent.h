#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>
#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QDateEdit;

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit AddEvent(QWidget *parent = nullptr);


private:
    QPushButton *addButton;
    QPushButton *cancelButton;
    QLineEdit *nameLine;
    QDateEdit *dateLine;


};

#endif // ADDEVENT_H
