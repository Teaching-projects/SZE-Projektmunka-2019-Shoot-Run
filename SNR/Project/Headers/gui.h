#ifndef GUI_H
#define GUI_H

#include <QMap>
#include <QWidget>
#include "reg.h"
#include "login.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;

class gui : public QWidget
{
    Q_OBJECT
public:
    explicit gui(QWidget *parent = nullptr);
private:
    QPushButton *logButton;
    QPushButton *regButton;
    QPushButton *cancelButton;
    QLineEdit *unameLine;
    QLineEdit *passLine;
    Reg *regdialog;
    login *logdialog;
signals:

public slots:
	void regUser();
	void logUser();
};

#endif // GUI_H
