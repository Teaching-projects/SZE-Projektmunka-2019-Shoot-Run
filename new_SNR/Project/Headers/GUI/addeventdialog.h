#ifndef ADDEVENTDIALOG_H
#define ADDEVENTDIALOG_H

#include <QDialog>

namespace Ui {
class addeventdialog;
}

class addeventdialog : public QDialog{
    Q_OBJECT
public:
    explicit addeventdialog(QWidget *parent = nullptr);
    ~addeventdialog();
private slots:
    void on_addevent_back_clicked();
    void on_addevent_ok_clicked();
private:
    Ui::addeventdialog *ui;
};

#endif // ADDEVENTDIALOG_H
