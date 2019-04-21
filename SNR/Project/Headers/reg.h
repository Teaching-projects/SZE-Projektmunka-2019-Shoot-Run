#ifndef REG_H
#define REG_H

#include <QDialog>

#include "database.h"

//class gui;
class QPushButton;
class QLineEdit;

class Reg : public QDialog, public DB
{
    Q_OBJECT
public:
    explicit Reg(QWidget *parent = nullptr);
private slots:
	void regClicked();
    void cancel();
private:
    QPushButton *regButton;
    QPushButton *cancelButton;
    QLineEdit *nameEdit;
    QLineEdit *passEdit;
    QLineEdit *mailEdit;
	QLineEdit *fnameEdit;
	QLineEdit *lnameEdit;
};

#endif // REG_H
