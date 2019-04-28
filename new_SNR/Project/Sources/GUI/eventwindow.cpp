#include "eventwindow.h"
#include "ui_eventwindow.h"
#include "addeventdialog.h"
#include "mainwindow.h"
#include "picturelist.h"

#include <QMessageBox>
#include <QSettings>

#include "database.h"
#include "event.h"
#include "event-odb.hxx"
#include "user.h"
#include "user-odb.hxx"

eventwindow::eventwindow(QWidget *parent) : QWidget(parent), ui(new Ui::eventwindow){
    ui->setupUi(this);
    ui->event_list->setColumnCount(3);
    show_eventlist();
	ui->event_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

eventwindow::~eventwindow(){
    delete ui;
}

void eventwindow::on_event_list_cellClicked(int row, int column){
    last_clicked_row = row;
}

void eventwindow::on_add_button_clicked(){
    addeventdialog* event_dialog = new addeventdialog();
    event_dialog->setModal(true);
    event_dialog->show();
}

void eventwindow::on_logout_button_clicked(){
    mainwindow* new_login = new mainwindow;
    new_login->show();
    this->close();
}

void eventwindow::on_exit_button_clicked(){
    QCoreApplication::quit();
}

void eventwindow::on_search_buton_clicked(){
    ui->event_list->setRowCount(0);
    ui->event_list->clearContents();
    search_word();
}

void eventwindow::search_word(){
    ui->event_list->model()->removeRows(0, ui->event_list->rowCount());
    int row=0;
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<odbevent> query;
    typedef odb::result<odbevent> result;
    odb::core::transaction t(db->begin());
    std::string search_condition("%");
    search_condition.append(ui->search_name->text().toStdString().append("%"));
    result r(db->query<odbevent>(query::event_name.like (search_condition) && query::event_accepted == true));
    if(!r.empty()){
        for (result::iterator i(r.begin()); i != r.end(); ++i){
            ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
            ui->event_list->setItem(row, 0, new QTableWidgetItem(i->getname()));
            ui->event_list->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
            ui->event_list->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
            row++;
        }
        t.commit();
    }
    else{
        QMessageBox::information(this,"Error!", "There is no event with this name!");
        result r(db->query<odbevent>(query::event_accepted == 1));
        for (result::iterator i(r.begin()); i != r.end(); ++i){
            ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
                 ui->event_list->setItem(row, 0, new QTableWidgetItem(i->getname()));
                 ui->event_list->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
                 ui->event_list->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
                 row+=1;
        }
        t.commit();
    }
}

void eventwindow::show_eventlist(){
        QSharedPointer<odb::core::database> db = DB::create_database();
        typedef odb::query<odbevent> query;
        typedef odb::result<odbevent> result;
        odb::core::transaction t(db->begin());
        result r(db->query<odbevent>(query::event_accepted == 1));
        int row=0;
        for (result::iterator i(r.begin()); i != r.end(); ++i){
            ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
                 ui->event_list->setItem(row, 0, new QTableWidgetItem(i->getname()));
                 ui->event_list->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
                 ui->event_list->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
                 row++;
        }
        t.commit();
}

void eventwindow::on_select_button_clicked(){
    QSettings setting("MYDATA", "SNR");
    setting.beginGroup("TEST");
    setting.setValue("current_event", ui->event_list->item(last_clicked_row,2)->text());
    setting.endGroup();

    picturelist* picture_window = new picturelist;
    picture_window->setWindowModality(Qt::ApplicationModal);
    picture_window->show();
    show_eventlist();
}

void eventwindow::on_search_reset_clicked(){
    show_eventlist();
}
