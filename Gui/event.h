#ifndef EVENT_H
#define EVENT_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;

class Event : public QDialog
{
    Q_OBJECT

public:
    explicit Event(QWidget *parent = nullptr);


private:
    QPushButton *uploadButton;
    QPushButton *backButton;
    QLineEdit *unameLine;


};

#endif // EVENT_H
