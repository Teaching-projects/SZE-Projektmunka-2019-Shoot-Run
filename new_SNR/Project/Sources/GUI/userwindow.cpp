#include "userwindow.h"
#include "ui_userwindow.h"
#include "mainwindow.h"
#include "addeventdialog.h"

#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <io.h>
#include <QtConcurrentRun>
#include <QXmlStreamReader>


#include "database.h"
#include "image.h"
#include "image-odb.hxx"
#include "event.h"
#include "event-odb.hxx"
#include "user.h"
#include "user-odb.hxx"
#include "track.h"
#include "track-odb.hxx"
#include "tardis.h"
#include "tardis-odb.hxx"
#include "exif.h"

userwindow::userwindow(QWidget *parent) : QWidget(parent), ui(new Ui::userwindow){
    ui->setupUi(this);
    QSettings setting("MYDATA", "SNR");
    setting.beginGroup("TEST");
    current_user_string = setting.value("current_user").toString().toStdString();
    current_user_int = setting.value("current_user_id").toString().toInt();
    setting.endGroup();
    ui->event_list->horizontalHeader()->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
    load_events();
    loadfrom_eventpointer();
    set_options();
}

userwindow::~userwindow(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    if(!eventpointer_list.isEmpty())
        this->eventpointer_list.clear();
    if(!tardispointer_list.isEmpty())
        this->tardispointer_list.clear();
    delete ui;
}

void userwindow::on_exit_button_clicked(){
    QCoreApplication::quit();
}

void userwindow::on_logout_button_clicked(){
    mainwindow* new_login = new mainwindow;
    new_login->show();
    this->close();
}

void userwindow::on_back_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    ui->image_list->clear();
    ui->image_list->model()->removeRows(0, ui->event_list->rowCount());
}

void userwindow::on_event_filterreset_clicked(){
    set_options();
    ui->event_name->setText("");
    filter_events();
}

void userwindow::on_event_add_clicked(){
    addeventdialog* event_dialog = new addeventdialog();
    event_dialog->setModal(true);
    event_dialog->show();
}

void userwindow::on_image_upload_clicked(){
    image_upload_filedialog();
}

void userwindow::on_image_track_upload_clicked(){
    open_track_filedialog();
}

void userwindow::on_image_search_clicked(){
    if(ui->label->text() != "Track available")
        return;
    for(int iterator = 0; iterator < ui->image_list->model()->rowCount(); iterator++)
        ui->image_list->item(iterator)->setHidden(true);
    int time = ui->slider_time->value();
    double distance_ = ui->slider_distance->value();
    for(int i=0, j=0; j<imagepointer_list.size() && i<tardispointer_list.size();){
        if((tardispointer_list[i]->getDate() >= imagepointer_list[j]->getDate().addSecs((time * -1))) && (tardispointer_list[i]->getDate() <= imagepointer_list[j]->getDate().addSecs(time))){
            if(distance(imagepointer_list[j],tardispointer_list[i]) < distance_){
                if(ui->image_list->item(j)->isHidden())
                    ui->image_list->item(j)->setHidden(false);
                if(tardispointer_list[i]->getDate()>imagepointer_list[j]->getDate())
                    j++;
                else if(tardispointer_list[i]->getDate()<imagepointer_list[j]->getDate())
                    i++;
                else
                    i++;
            }
            else{
                if(tardispointer_list[i]->getDate()>imagepointer_list[j]->getDate())
                    j++;
                else if(tardispointer_list[i]->getDate()<imagepointer_list[j]->getDate())
                    i++;
                else
                    i++;
            }
        }
    else if(tardispointer_list[i]->getDate()<imagepointer_list[j]->getDate())
        i++;
    else if(tardispointer_list[i]->getDate()>imagepointer_list[j]->getDate())
        j++;
    }
}

void userwindow::on_event_list_itemDoubleClicked(QTableWidgetItem *item){
     last_clicked_row = item->row();
     if(!eventpointer_list.at(last_clicked_row)->isAccepted())
         return;
     load_images();
     loadfrom_imagepointer();
     if(isthereatrack()){
         ui->label->setText("Track available");
         load_track();
     }
     else
         ui->label->setText("No track available");
     ui->stackedWidget->setCurrentIndex(1);
}

void userwindow::image_upload_filedialog(){
    QStringList file_names = QFileDialog::getOpenFileNames(this, "Select the picture", QDir::homePath(),tr("Images (*.png *.jpg)"));
    for (int i = 0; i < file_names.size(); ++i){
        image_upload(file_names.at(i),eventpointer_list.at(last_clicked_row)->getId(),current_user_string, &imagepointer_list);
        QPixmap image_;
        image_.load(file_names.at(i));
        ui->image_list->addItem(new QListWidgetItem(QIcon(image_), "Waiting for validation"));
    }
}

QList<int> userwindow::get_selectedimages(){
    QList<int> return_list, return_list_inverse;
    for (auto iterator : ui->image_list->selectedItems())
        if (iterator->isSelected())
            return_list << ui->image_list->row(iterator);
    qSort(return_list.begin(),return_list.end());
    std::reverse(return_list.begin(), return_list.end());
    return return_list;
}

void userwindow::load_events(){
    if(!eventpointer_list.isEmpty())
        this->eventpointer_list.clear();
    ui->event_list->model()->removeRows(0, ui->event_list->rowCount());
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<odbevent> query;
    typedef odb::result<odbevent> result;
    odb::core::session s;
    odb::core::transaction t(db->begin());
    result r(db->query<odbevent>(query::event_accepted == true || query::submitter_id == current_user_int));
    for (result::iterator iterator(r.begin()); iterator != r.end(); ++iterator)
        eventpointer_list << new odbevent(*iterator);
    t.commit();
}

void userwindow::load_images(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    ui->image_list->clear();
    ui->image_list->model()->removeRows(0, ui->event_list->rowCount());
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<image>   query;
    typedef odb::result<image>  result;
    odb::core::session s;
    odb::core::transaction t(db->begin());
    result r(db->query<image>((query::event_id == eventpointer_list.at(last_clicked_row)->getId() && (query::user_id == current_user_int || query::image_accepted == true)) + "ORDER BY" + query::image_date + "ASC"));
    for (auto value : r)
        imagepointer_list << new image(value);
    t.commit();
}

void userwindow::load_track(){
    if(!tardispointer_list.isEmpty())
        this->tardispointer_list.clear();
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::core::transaction t(db->begin());
    odb::session s;
    typedef odb::query<track>	track_query;
    typedef odb::query<user>	user_query;
    typedef odb::query<tardis>	tardis_query;
    typedef odb::result<tardis>	tardis_result;
    QSharedPointer<user> current_user = db->query_one<user>(user_query::user_name == current_user_string);
    QSharedPointer<track> result_track = db->query_one<track>(track_query::user_id == current_user->getID() && track_query::event_id == eventpointer_list.at(last_clicked_row)->getId());
    if(result_track.get() != nullptr){
        int track_id = result_track->getID();
        tardis_result r(db->query<tardis>((tardis_query::track_id == track_id) + "ORDER BY" + tardis_query::tardis_date + "ASC"));
        QDateTime last_date;
        for(auto iterator : r)
            if(last_date != iterator.getDate())
                tardispointer_list << new tardis(iterator);
        ui->label->setText("Track available");
    }
    t.commit();
}

void userwindow::loadfrom_imagepointer(){
    QPixmap imagefrom;
    for (auto iterator : imagepointer_list){
        loadfrom_blob(&imagefrom , iterator->getBlob());
        if(iterator->isAccepted())
            ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom), ""));
        else
            ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom), "Not accepted"));
    }
}

void userwindow::loadfrom_blob(QPixmap *image, QByteArray blob){
    image->loadFromData(blob);
}

void userwindow::loadfrom_eventpointer(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<image_per_event>   query;
    typedef odb::result<image_per_event>   result;
    int row=0;
    for (auto iterator : eventpointer_list){
        odb::core::transaction t(db->begin());
        result count (db->query<image_per_event>(query::image::image_accepted == true));
        QString date = iterator->getDate().toString("yyyy-MM-dd");
        ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
        ui->event_list->setItem(row, 0, new QTableWidgetItem(iterator->getName()));
        ui->event_list->setItem(row, 1, new QTableWidgetItem(date));
        for(result::iterator i (count.begin ()); i != count.end (); ++i)
            if(iterator->getId() == static_cast<int>(i->event_id))
                ui->event_list->item(row,1)->setText(QString(date.append("\tImages: ").append(QString::number(static_cast<int>(i->count)))));
        if(!iterator->isAccepted())
            ui->event_list->item(row,1)->setText(QString(date.append("\tNot accepted")));
        t.commit ();
        row++;
    }
}

void userwindow::filter_events(){
    for(int iterator = 0; iterator < ui->event_list->rowCount(); iterator++)
        ui->event_list->hideRow(iterator);
    QDateTime date_from    =       QDateTime::fromString(ui->date_from->text(),"yyyy. MM. dd.");
    QDateTime date_to      =       QDateTime::fromString(ui->date_to->text(),"yyyy. MM. dd.");
    QString event_name = ui->event_name->text();
    int index = 0;
        for(auto iterator : eventpointer_list){
            if(iterator->getName().contains(event_name, Qt::CaseInsensitive) && iterator->getDate() >= date_from && date_to >= iterator->getDate())
                ui->event_list->showRow(index);
            index++;
        }
}

void userwindow::set_options(){
    ui->date_from-> setMaximumDateTime(QDateTime::currentDateTime());
    ui->date_to->   setMaximumDateTime(QDateTime::currentDateTime());
    ui->date_to->   setDateTime(QDateTime::currentDateTime());
}

int userwindow::upload_track(QString path_Q,int current_event_int,std::string current_user_string){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::core::transaction t(db->begin());
    odb::session s;
    typedef odb::query<odbevent> event_query;
    typedef odb::query<user>     user_query;
    QSharedPointer<odbevent> current_event = db->query_one<odbevent>(event_query::event_id == current_event_int);
    QSharedPointer<user> current_user = db->query_one<user>(user_query::user_name == current_user_string);
    QSharedPointer<track> new_track(new track(current_event, current_user));
    db->persist(new_track);
    t.commit();
    QFile file(path_Q);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "File open error:" << file.errorString();
        return 1;
    }
    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError()){
        inputStream.readNext();
        double lat, lon;
        if (inputStream.isStartElement()){
            odb::core::transaction t(db->begin());
            QString name = inputStream.name().toString();
            if (name == "trkpt") {
                lat = inputStream.attributes().value("lat").toDouble();
                lon = inputStream.attributes().value("lon").toDouble();
            }
            if (name == "time"){
                QSharedPointer<tardis> new_tardis(new tardis(new_track, lon, lat, (QDateTime::fromString(inputStream.readElementText(), "yyyy-MM-ddThh:mm:ssZ"))));
                new_tardis->track(new_track);
                new_track->tardises().push_back(new_tardis);
                db->update(new_track);
                db->persist(new_tardis);
                t.commit();
            }
        }
    }
    return 0;
}

void userwindow::open_track_filedialog(){//TODO
    QString file_name = QFileDialog::getOpenFileName(this, "Select the track", QDir::homePath(),tr("Tracks (*.gpx)"));
    if(isthereatrack())
        delete_track();
    QFuture<void> future = QtConcurrent::run(upload_track, file_name, eventpointer_list.at(last_clicked_row)->getId(),current_user_string);
    ui->label->setText("Track available");
    //upload_track(file_name);
}

void userwindow::delete_track(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::core::transaction t(db->begin());
    odb::session s;
    typedef odb::query<tardis>	tardis_query;
    typedef odb::result<tardis> tardis_result;
    typedef odb::query<track>	track_query;
    typedef odb::query<user>	user_query;
    QSharedPointer<user> current_user = db->query_one<user>(user_query::user_name == current_user_string);
    QSharedPointer<track> result_track = db->query_one<track>(track_query::user_id == current_user->getID() && track_query::event_id == eventpointer_list.at(last_clicked_row)->getId());
    tardis_result result_tardises(db->query<tardis>(tardis_query::track_id == result_track->getID()));
    for(tardis_result::iterator current_tardis(result_tardises.begin()); current_tardis != result_tardises.end(); ++current_tardis)
        db->erase(*current_tardis);
    db->erase(*result_track);
    t.commit();
}

void userwindow::image_upload(QString filename, int current_event_id,std::string current_user_string, QList<image*>* imagepointer_list){
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
    QSharedPointer<user>         current_user  = db->query_one<user>(u_query::user_name == current_user_string);
    QSharedPointer<odbevent>     current_event = db->query_one<odbevent>(e_query::event_id == current_event_id);
    QSharedPointer<image> new_image(new image(filename.toStdString(), current_event, current_user, date, result.GeoLocation.Longitude, result.GeoLocation.Latitude));
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

void userwindow::on_event_name_textChanged(const QString &arg1) {filter_events();}
void userwindow::on_date_from_editingFinished()                 {filter_events();}
void userwindow::on_date_to_editingFinished()                   {filter_events();}

QString userwindow::GetRandomString(){
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 12;
   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

void userwindow::on_image_download_clicked(){
    QString file_name = QFileDialog::getExistingDirectory(0, ("Select download folder"), QDir::currentPath());
    for(auto iterator : get_selectedimages()){
        QString randomfilename(file_name);
        randomfilename.append("/").append(GetRandomString()).append(".png");
        QFile newDoc(randomfilename);
        if(newDoc.open(QIODevice::WriteOnly)){
            newDoc.write(this->imagepointer_list.value(iterator)->getBlob());
        }
        newDoc.close();
    }
}

int userwindow::isthereatrack(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::core::transaction t(db->begin());
    odb::session s;
    typedef odb::query<track>	track_query;
    typedef odb::query<user>	user_query;
    QSharedPointer<user> current_user = db->query_one<user>(user_query::user_name == current_user_string);
    QSharedPointer<track> result_track = db->query_one<track>(track_query::user_id == current_user->getID() && track_query::event_id == eventpointer_list.at(last_clicked_row)->getId());
    if(result_track.get() != nullptr){
        t.commit();
        return 1;
    }
    t.commit();
    return 0;
}

void userwindow::on_image_track_refresh_clicked(){
    if(isthereatrack()){
        ui->label->setText("Track available");
        load_track();
    }
    else
        ui->label->setText("No track available");
}

void userwindow::on_event_refresh_clicked(){
    load_events();
    loadfrom_eventpointer();
}

void userwindow::on_slider_distance_sliderMoved(int position){
    ui->label_distance->setText(QString("Distance: ").append(QString::number(position)).append("m"));
    on_image_search_clicked();
}

void userwindow::on_slider_time_sliderMoved(int position){
    ui->label_time->setText(QString("Time: ").append(QString::number(position)).append("s"));
    on_image_search_clicked();
}

void userwindow::on_pushButton_clicked(){
    for(int iterator = 0; iterator < ui->event_list->rowCount(); iterator++)
        ui->image_list->item(iterator)->setHidden(false);
}

double userwindow::distance(image * image, tardis * tardis){
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = (((image->getLatitude())*3.14))/180;
    lon1r = (((image->getLongitude())*3.14))/180;
    lat2r = (((tardis->getLatitude())*3.14))/180;
    lon2r = (((tardis->getLongitude())*3.14))/180;
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000;
}
