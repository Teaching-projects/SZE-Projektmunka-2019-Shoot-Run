#ifndef REG_H
#define REG_H

#include <QDialog>

class QPushButton;
class QLineEdit;

class Reg : public QDialog
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = nullptr);

private slots:
    void regClicked();

private:
    QPushButton *regButton;
    QPushButton *cancelButton;
    QLineEdit *nameEdit;
    QLineEdit *passEdit;
    QLineEdit *mailEdit;
};

#endif // REG_H
