#include "addeventdialog.h"
#include "ui_addeventdialog.h"

#include <QMessageBox>
#include <QSettings>

#include "event.h"
#include "event-odb.hxx"
#include "user.h"
#include "user-odb.hxx"
#include "database.h"

addeventdialog::addeventdialog(QWidget *parent) : QDialog(parent), ui(new Ui::addeventdialog){
    ui->setupUi(this);
    ui->addevent_ok->setFocus();
    ui->addevent_datetime->setMaximumDate(QDate::currentDate());
    ui->addevent_datetime->setSelectedDate(QDate::currentDate());
}

addeventdialog::~addeventdialog(){
    delete ui;
}

void addeventdialog::on_addevent_back_clicked(){
    this->close();
}

void addeventdialog::on_addevent_ok_clicked(){
    QSharedPointer<odb::core::database> db = DB::create_database();
        typedef odb::query<odbevent> query;
        typedef odb::result<odbevent> result;
        odb::session s;
        odb::core::transaction t(db->begin());
        result r(db->query<odbevent>(query::event_name == ui->addevent_name->text().toStdString()));
        if (!r.empty()) {
            QMessageBox::information(this, "Error!", "Event name already used");
        }
        else {
            QSharedPointer<odbevent> new_event(new odbevent(ui->addevent_name->text().toStdString(),QDateTime(ui->addevent_datetime->selectedDate())));

            QSettings setting("MYDATA", "SNR");
            setting.beginGroup("TEST");
            std::string current_user_string = setting.value("current_user").toString().toStdString();
            bool is_admin = setting.value("is_admin").toBool();
            typedef odb::query<user> query;
            QSharedPointer<user> current_user = db->query_one<user>(query::user_name == current_user_string);
            new_event->user(current_user);
            if(is_admin)
                new_event->Accept();
            db->persist(new_event);
            t.commit();
        }
        QString success_info = "The registered event:\nName:\t";
        success_info.append(ui->addevent_name->text());
        success_info.append("\nDate:\t");
        success_info.append(QDateTime(ui->addevent_datetime->selectedDate()).toString("yyyy:MM:dd"));
        QMessageBox::information(this,"Event info!", success_info);
        this->close();
}

