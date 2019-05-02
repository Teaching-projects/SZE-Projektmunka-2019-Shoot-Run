#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "mainwindow.h"
#include "picturelist.h"
#include "eventwindow.h"
#include "addeventdialog.h"

#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <io.h>
#include <QtConcurrentRun>


#include "database.h"
#include "image.h"
#include "image-odb.hxx"
#include "event.h"
#include "event-odb.hxx"
#include "user.h"
#include "user-odb.hxx"
#include "track.h"
#include "track-odb.hxx"
#include "exif.h"

adminwindow::adminwindow(QWidget *parent) : QWidget(parent), ui(new Ui::adminwindow){
    ui->setupUi(this);
    ui->event_list->horizontalHeader()->setVisible(true);
    ui->event_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->stackedWidget->setCurrentIndex(0);

    ui->image_list->setViewMode(QListWidget::IconMode);
    ui->image_list->setResizeMode(QListWidget::Adjust);

    load_events();
    loadfrom_eventpointer();
    set_options();
    if(ui->event_accept->isEnabled())
        ui->event_accept->setEnabled(false);

}

adminwindow::~adminwindow(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    delete ui;
}

void adminwindow::set_options(){
    ui->date_from-> setMaximumDateTime(QDateTime::currentDateTime());
    ui->date_to->   setMaximumDateTime(QDateTime::currentDateTime());
    ui->date_to->   setDateTime(QDateTime::currentDateTime());
    ui->image_both->click();
}

void adminwindow::on_logout_button_clicked(){
    mainwindow* new_login = new mainwindow;
    new_login->show();
    this->close();
}

void adminwindow::on_exit_button_clicked(){
    QCoreApplication::quit();
}

void adminwindow::image_upload_filedialog(){
    QStringList file_names = QFileDialog::getOpenFileNames(this, "Select the picture", QDir::homePath());
    for (int i = 0; i < file_names.size(); ++i){
        image_upload(file_names.at(i),eventpointer_list.at(last_clicked_row)->getId(), &imagepointer_list);
        QPixmap image_;
        image_.load(file_names.at(i));
        ui->image_list->addItem(new QListWidgetItem(QIcon(image_), ""));
    }
}

QList<int> adminwindow::get_selectedevents(){
    QList<int> return_list;
    for(auto iterator: ui->event_list->selectedItems()){
        if(iterator->column()==0)
            return_list << iterator->row();
    }
    qSort(return_list.begin(),return_list.end());
    std::reverse(return_list.begin(), return_list.end());
    return return_list;
}

QList<int> adminwindow::get_selectedimages(){
    QList<int> return_list, return_list_inverse;
    for (auto iterator : ui->image_list->selectedItems())
        if (iterator->isSelected())
            return_list << ui->image_list->row(iterator);
    qSort(return_list.begin(),return_list.end());
    std::reverse(return_list.begin(), return_list.end());
    return return_list;
}

void adminwindow::load_events(){
    if(!eventpointer_list.isEmpty())
        this->eventpointer_list.clear();
    ui->event_list->model()->removeRows(0, ui->event_list->rowCount());
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::result<odbevent> result;
    odb::core::session s;
    odb::core::transaction t(db->begin());
    result r(db->query<odbevent>());
    for (result::iterator iterator(r.begin()); iterator != r.end(); ++iterator)
        eventpointer_list << new odbevent(*iterator);
    t.commit();
}

void adminwindow::load_images(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    ui->image_list->clear();
    ui->image_list->model()->removeRows(0, ui->event_list->rowCount());
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<image>   query;
    typedef odb::result<image>  result;
    odb::core::session s;
    odb::core::transaction t(db->begin());
    result r(db->query<image>((query::event_id == eventpointer_list.at(last_clicked_row)->getId()) + "ORDER BY" + query::image_date + "ASC"));
    for (auto value : r)
        imagepointer_list << new image(value);
    t.commit();
}

void adminwindow::loadfrom_imagepointer(){
    QPixmap imagefrom;
    for (auto iterator : imagepointer_list){
        loadfrom_blob(&imagefrom , iterator->getBlob());
        ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom), ""));
    }
}

void adminwindow::on_event_refresh_clicked(){
    load_events();
    loadfrom_eventpointer();
}

void adminwindow::loadfrom_blob(QPixmap *image, QByteArray blob){
    image->loadFromData(blob);
}

void adminwindow::loadfrom_eventpointer(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<image_per_event>   query;
    typedef odb::result<image_per_event>   result;
    int row=0;
    for (auto iterator : eventpointer_list){
        odb::core::transaction t(db->begin());
        result count (db->query<image_per_event>(query::image::image_accepted == false));
        QString date = iterator->getDate().toString("yyyy-MM-dd");
        ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
        ui->event_list->setItem(row, 0, new QTableWidgetItem(iterator->getName()));
        ui->event_list->setItem(row, 1, new QTableWidgetItem(date));
        for(result::iterator i (count.begin ()); i != count.end (); ++i){
            qDebug() <<iterator->getId() << "\t"<< i->event_id;
            if(iterator->getId() == static_cast<int>(i->event_id))
                ui->event_list->item(row,1)->setText(QString(date.append("\tTo check: ").append(QString::number(static_cast<int>(i->count)))));
        }
        t.commit ();
        row++;
    }
}

void adminwindow::accept_events(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<odbevent> query;
    typedef odb::result<odbevent> result;
    odb::core::transaction t(db->begin());
    int index = 0;
    result event_result(db->query<odbevent>(query::event_id.in_range(selected.begin(),selected.end()) ));
    for (result::iterator event_iterator(event_result.begin()); event_iterator != event_result.end(); ++event_iterator){
        event_iterator->Accept();
        db->update(*event_iterator);
         if(ui->event_notaccepted->isChecked())
            ui->event_list->hideRow(selected.at(index));
         index++;
    }
    t.commit();
}

void adminwindow::delete_events(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    for(auto iterator : selected){
        db->erase(*eventpointer_list.at(iterator));
        ui->event_list->model()->removeRow(iterator);
        delete eventpointer_list.takeAt(iterator);
    }
    t.commit();
}

void adminwindow::filter_events(){
    for(int iterator = 0; iterator < ui->event_list->rowCount(); iterator++)
        ui->event_list->hideRow(iterator);
    QDateTime date_from    =       QDateTime::fromString(ui->date_from->text(),"yyyy. MM. dd.");
    QDateTime date_to      =       QDateTime::fromString(ui->date_to->text(),"yyyy. MM. dd.");
    QString event_name = ui->event_name->text();
    int index = 0;
    if(ui->event_both->isChecked()){
        for(auto iterator : eventpointer_list){
            if(iterator->getName().contains(event_name, Qt::CaseInsensitive) && iterator->getDate() >= date_from && date_to >= iterator->getDate())
                ui->event_list->showRow(index);
            index++;
        }
        if(!ui->event_delete->isEnabled())
            ui->event_delete->setEnabled(true);
        if(ui->event_accept->isEnabled())
            ui->event_accept->setEnabled(false);
    }
    else if(ui->event_accepted->isChecked()){
        for(auto iterator : eventpointer_list){
            if(iterator->getName().contains(event_name, Qt::CaseInsensitive) && iterator->isAccepted() && iterator->getDate() >= date_from && date_to >= iterator->getDate())
                ui->event_list->showRow(index);
            index++;
        }
        if(!ui->event_delete->isEnabled())
            ui->event_delete->setEnabled(true);
        if(ui->event_accept->isEnabled())
            ui->event_accept->setEnabled(false);
    }
    else if(ui->event_notaccepted->isChecked()){
        for(auto iterator : eventpointer_list){
            if(iterator->getName().contains(event_name, Qt::CaseInsensitive) && (!iterator->isAccepted()) && iterator->getDate() >= date_from && date_from >= iterator->getDate())
                ui->event_list->showRow(index);
            index++;
        }
        if(!ui->event_delete->isEnabled())
            ui->event_delete->setEnabled(true);
        if(!ui->event_accept->isEnabled())
            ui->event_accept->setEnabled(true);
    }
}

void adminwindow::filter_images(){
    for(int index = 0; index < ui->image_list->count(); ++index)
            ui->image_list->item(index)->setHidden(true);
    if(ui->image_both->isChecked()){
        for(int index = 0; index < ui->image_list->count(); ++index){
                ui->image_list->item(index)->setHidden(false);
            }
            if(ui->image_accept->isEnabled()){
                ui->image_accept->setEnabled(false);
        }
    }
    else if(ui->image_accepted->isChecked()){
        for(int index = 0; index < ui->image_list->count(); ++index){
                if(imagepointer_list.at(index)->isAccepted())
                    ui->image_list->item(index)->setHidden(false);
            if(ui->image_accept->isEnabled()){
                ui->image_accept->setEnabled(false);
            }
        }
    }
    else if(ui->image_waiting->isChecked()){
        for(int index = 0; index < ui->image_list->count(); ++index){
            if(!imagepointer_list.at(index)->isAccepted())
                ui->image_list->item(index)->setHidden(false);
            if(!ui->image_accept->isEnabled()){
                ui->image_accept->setEnabled(true);
            }
        }
    }
}

void adminwindow::accept_images(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    for(auto iterator : selected){
        imagepointer_list.at(iterator)->Accept();
        db->update(*imagepointer_list.at(iterator));
        if(ui->image_waiting->isChecked())
            ui->image_list->item(iterator)->setHidden(true);
    }
    t.commit();
}

void adminwindow::delete_images(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    for(auto iterator : selected){
        qDebug() << selected;
        db->erase(*imagepointer_list.at(iterator));
        ui->image_list->model()->removeRow(iterator);
        delete imagepointer_list.takeAt(iterator);
    }
    t.commit();
    filter_images();
}

void adminwindow::image_upload(QString filename, int current_event_id,QList<image*>* imagepointer_list){
    QFile qf(filename);
    qf.open(QIODevice::ReadOnly);
    int fd = qf.handle();
    FILE* fp = fdopen(dup(fd), "rb");
    qf.close();
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
        printf("Can't read file.\n");
        delete[] buf;
        return;
    }
    fclose(fp);
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code) {
        printf("Error parsing EXIF: code %d\n", code);
    }
    QDateTime date = QDateTime::fromString(QString::fromStdString(result.DateTime), "yyyy:MM:dd HH:mm:ss");
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    typedef odb::query<user> u_query;
    typedef odb::query<odbevent> e_query;
    QSharedPointer<user>         current_user  = db->query_one<user>(u_query::user_name == "admin");
    QSharedPointer<odbevent>     current_event = db->query_one<odbevent>(e_query::event_id == current_event_id);
    QSharedPointer<image> new_image(new image(filename.toStdString(), current_event, current_user, date, result.GeoLocation.Longitude, result.GeoLocation.Latitude));
    new_image->Accept();
    db->persist(new_image);
    new_image->user(current_user);
    new_image->odbevent(current_event);
    *imagepointer_list << new image(*new_image.data());
    current_user->images().push_back(new_image);
    current_event->images().push_back(new_image);
    db->update(current_event);
    db->update(current_user);
    t.commit();
}

void adminwindow::on_event_accept_clicked(){
    if(get_selectedevents().empty())
        return;
    accept_events(get_selectedevents());
}

void adminwindow::on_event_delete_clicked(){
        if(get_selectedevents().empty())
            return;
    delete_events(get_selectedevents());
}

void adminwindow::on_event_list_itemDoubleClicked(QTableWidgetItem *item){
    last_clicked_row = item->row();
    load_images();
    loadfrom_imagepointer();
    ui->stackedWidget->setCurrentIndex(1);
}

void adminwindow::on_event_name_textChanged(const QString &arg1){filter_events();}
void adminwindow::on_event_both_clicked()                       {filter_events();}
void adminwindow::on_event_notaccepted_clicked()                {filter_events();}
void adminwindow::on_event_accepted_clicked()                   {filter_events();}
void adminwindow::on_date_from_editingFinished()                {filter_events();}
void adminwindow::on_date_to_editingFinished()                  {filter_events();}

void adminwindow::on_image_waiting_clicked()                    {filter_images();}
void adminwindow::on_image_accepted_clicked()                   {filter_images();}
void adminwindow::on_image_both_clicked()                       {filter_images();}

void adminwindow::on_event_add_clicked(){
    addeventdialog* event_dialog = new addeventdialog();
    event_dialog->setModal(true);
    event_dialog->show();
}

void adminwindow::on_event_filterreset_clicked(){
    set_options();
}

void adminwindow::on_back_clicked(){
        ui->stackedWidget->setCurrentIndex(0);
        if(!imagepointer_list.isEmpty())
            this->imagepointer_list.clear();
        ui->image_list->clear();
        ui->image_list->model()->removeRows(0, ui->event_list->rowCount());
}

void adminwindow::on_image_upload_clicked(){
    image_upload_filedialog();
}

void adminwindow::on_image_accept_clicked(){
    if(!get_selectedimages().empty())
        accept_images(get_selectedimages());
}

void adminwindow::on_image_delete_clicked(){
    if(!get_selectedimages().empty())
        delete_images(get_selectedimages());
}



