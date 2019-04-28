#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class mainwindow;
}

class mainwindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
    int user_correct(std::string, std::string);
    void password_hash(std::string&, QDateTime);
    int user_exist(std::string, std::string);
    int user_registration(std::string, std::string password, std::string first_name, std::string last_name, std::string email);
private slots:
    void on_register_switch_clicked();
    void on_register_ok_clicked();
    void on_login_ok_clicked();
    void on_register_back_clicked();
private:
    Ui::mainwindow *ui;
    bool is_admin;
};

#endif // MAINWINDOW_H
