#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventwindow.h"
#include "adminwindow.h"

#include <QMessageBox>
#include <QFormLayout>
#include <QSettings>
#include <QCryptographicHash>
#include <QDebug>



#include <iostream>
#include <odb/transaction.hxx>
#include <memory>



#include "database.h"
#include "event.h"
#include "event-odb.hxx"
#include "user.h"
#include "user-odb.hxx"
#include "tardis.h"
#include "tardis-odb.hxx"

mainwindow::mainwindow(QWidget *parent) : QWidget(parent), ui(new Ui::mainwindow), is_admin(false){
    ui->setupUi(this);
    ui->register_password->setEchoMode(QLineEdit::Password);
    ui->login_password->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentIndex(0);

    QSettings setting("MYDATA", "SNR");
    setting.beginGroup("TEST");
    setting.setValue("current_user", "");
    setting.setValue("current_event", "");
    setting.endGroup();
}

mainwindow::~mainwindow(){
    delete ui;
}

void mainwindow::on_register_back_clicked(){
    ui->register_username->setText("");
    ui->register_password->setText("");
    ui->register_firstname->setText("");
    ui->register_lastname->setText("");
    ui->register_email->setText("");
    ui->stackedWidget->setCurrentIndex(0);
}

void mainwindow::on_register_switch_clicked(){
    ui->login_password->setText("");
    ui->login_username->setText("");
    ui->stackedWidget->setCurrentIndex(1);
}

void mainwindow::on_register_ok_clicked(){
    if(user_registration(ui->register_username->text().toStdString(), ui->register_password->text().toStdString(), ui->register_firstname->text().toStdString(), ui->register_lastname->text().toStdString(), ui->register_email->text().toStdString())){
        QMessageBox::information(this,"Successful registration", "Please log in with your user name and password");
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    QMessageBox::information(this,"Wrong name or email", "User name or email address already taken!");
}

void mainwindow::on_login_ok_clicked(){
    if(user_correct(ui->login_username->text().toStdString(),ui->login_password->text().toStdString())){
        QSettings setting("MYDATA", "SNR");
        setting.beginGroup("TEST");
        setting.setValue("current_user", ui->login_username->text());
        setting.setValue("is_admin", is_admin);
        setting.endGroup();
        if(is_admin){
            adminwindow* admin_window = new adminwindow;
            admin_window->show();
            this->close();
        }
        else{
        eventwindow* event_window = new eventwindow;
        event_window->show();
        this->close();
        }
    }
    else{
    QMessageBox::information(this,"Wrong name or password", "User name or password is incorrect!");
    }
}

int mainwindow::user_correct(std::string user_name, std::string password){
    typedef odb::query<user> query;
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    QSharedPointer<user> exists_name = db->query_one<user>(query::user_name == user_name);
    if (exists_name.get() != nullptr) {
        password_hash(password, exists_name->getRegistretionDate());
        QSharedPointer<user> q = db->query_one<user>(query::user_name == user_name && query::password == password);
        if (q.get() != nullptr) {
            if(q->isadmin())
                is_admin = true;
            return 1;
        }
    }
    t.commit();
    return 0;
}

void mainwindow::password_hash(std::string &password, QDateTime current_date){
        QString Q_date = current_date.toString();
        QString Q_password = QString::fromStdString(password);
        QCryptographicHash::Algorithm algo = QCryptographicHash::Sha512;
        const int rounds = 1000;
        QByteArray hash = (Q_date + Q_password).toUtf8();
        for (int i = 0; i < rounds; ++i) {
            hash = QCryptographicHash::hash(hash, algo);
        }
        QString hashedPass = QString(hash.toBase64());
                password = hashedPass.toStdString();
}

int mainwindow::user_exist(std::string user_name, std::string email){
    typedef odb::query<user> query;
    QSharedPointer<odb::core::database> db = DB::create_database();
    QSharedPointer<user> exists = db->query_one<user>(query::user_name == user_name || query::email == email);
    if (exists.get() == nullptr){
        return 0;
    }
    return 1;
}

int mainwindow::user_registration(std::string user_name, std::string password, std::string first_name, std::string last_name, std::string email){
    QSharedPointer<odb::core::database> db= DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    if (!user_exist(user_name, email)) {
        QDateTime registration_date = QDateTime::fromString(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm");
        password_hash(password, registration_date);
        QSharedPointer<user> new_user(new user(user_name, password, first_name, last_name, email, registration_date));
        db->persist(new_user);
        t.commit();
        ui->register_username->setText("");
        ui->register_password->setText("");
        ui->register_firstname->setText("");
        ui->register_lastname->setText("");
        ui->register_email->setText("");
        return 1;
    }
    return 0;
};

