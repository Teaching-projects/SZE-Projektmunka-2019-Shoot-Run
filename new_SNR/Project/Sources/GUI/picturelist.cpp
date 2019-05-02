#include "picturelist.h"
#include "ui_picturelist.h"
#include "eventwindow.h"

#include <QXmlStreamReader>
#include <QFileDialog>
#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QtSvg/QSvgRenderer>
#include <QtConcurrentRun>
#include <QElapsedTimer>
#include <QSet>

#include "database.h"
#include "user.h"
#include "user-odb.hxx"
#include "event.h"
#include "event-odb.hxx"
#include "image.h"
#include "image-odb.hxx"
#include "track.h"
#include "track-odb.hxx"
#include "tardis.h"
#include "tardis-odb.hxx"
#include "exif.h"


picturelist::picturelist(QWidget *parent) : QWidget(parent), ui(new Ui::picturelist){
    ui->setupUi(this);
    QSettings setting("MYDATA", "SNR");
    setting.beginGroup("TEST");
    current_event_int = setting.value("current_event").toInt();
    current_user_string = setting.value("current_user").toString().toStdString();
    setting.endGroup();

    ui->image_list->setViewMode(QListWidget::IconMode);
    ui->image_list->setIconSize(QSize(475, 475));
    ui->image_list->setResizeMode(QListWidget::Adjust);
    ui->image_list->setDragEnabled(false);
    show_track_info();
    list_images();
}

picturelist::~picturelist(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    delete ui;
}

void picturelist::show_track_info(){
    if(isthereatrack()){
        ui->track_info->setText("Track available");
    }
    else{
    ui->track_info->setText("No track");
    }
}

int picturelist::isthereatrack(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::core::transaction t(db->begin());
    odb::session s;
    typedef odb::query<track>	track_query;
    typedef odb::query<user>	user_query;
    typedef odb::query<tardis>	tardis_query;
    typedef odb::result<tardis>	tardis_result;

    QSharedPointer<user> current_user = db->query_one<user>(user_query::user_name == current_user_string);
    QSharedPointer<track> result_track = db->query_one<track>(track_query::user_id == current_user->getID() && track_query::event_id == current_event_int);


    if(result_track.get() != nullptr){
        int track_id = result_track->getID();
        tardis_result r(db->query<tardis>((tardis_query::track_id == track_id) + "ORDER BY" + tardis_query::tardis_date + "ASC"));
           QDateTime last_date;
           for(auto iterator : r)
                if(last_date != iterator.getDate())
                    this->tardispointer_list << new tardis(iterator);
        return 1;
    }
    return 0;
}

void picturelist::on_back_clicked(){
    QSettings setting("MYDATA", "SNR");
    setting.beginGroup("TEST");
    setting.setValue("current_event", "");
    setting.endGroup();

    this->close();
}

void picturelist::on_image_upload_clicked(){
    open_image_filedialog();
}

void picturelist::on_track_upload_clicked(){//TODO dialog popup hogy felül akarod e írni
    open_track_filedialog();
}

void picturelist::list_images(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<image> query;
    typedef odb::result<image> result;
    odb::core::transaction t(db->begin());
    result r(db->query<image>((query::event_id == current_event_int && query::image_accepted == true)+ "ORDER BY" + query::image_date + "ASC"));
    for (auto value : r) {
        imagepointer_list << new image(value);
        QPixmap imagefrom;
        imagefrom.loadFromData(value.getBlob());
        ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom),""));
   }
}

void picturelist::open_image_filedialog(){
    QStringList file_names = QFileDialog::getOpenFileNames(this, "Select the picture", QDir::homePath());
    for (int i = 0; i < file_names.size(); ++i)
        upload_image(file_names.at(i));
}

void picturelist::upload_image(QString path_Q){
    std::string path = path_Q.toStdString();
    char *cstr = new char[path.length() + 1];
    strcpy(cstr, path.c_str());
    FILE *fp = fopen(cstr, "rb");
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
        printf("Can't read file.\n");
        delete[] buf;
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

    QSharedPointer<user> current_user = db->query_one<user>(u_query::user_name == current_user_string);
    QSharedPointer<odbevent> current_event = db->query_one<odbevent>(e_query::event_id == current_event_int);

    QSharedPointer<image> new_image(new image(path, current_event, current_user, date, result.GeoLocation.Longitude, result.GeoLocation.Latitude));
    db->persist(new_image);
    new_image->user(current_user); new_image->odbevent(current_event);
    current_user->images().push_back(new_image);
    current_event->images().push_back(new_image);
    db->update(current_event); db->update(current_user);
    t.commit();
}

void picturelist::delete_track(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::core::transaction t(db->begin());
    odb::session s;
    typedef odb::query<tardis>	tardis_query;
    typedef odb::result<tardis> tardis_result;
    typedef odb::query<track>	track_query;
    typedef odb::query<user>	user_query;
    QSharedPointer<user> current_user = db->query_one<user>(user_query::user_name == current_user_string);
    QSharedPointer<track> result_track = db->query_one<track>(track_query::user_id == current_user->getID() && track_query::event_id == current_event_int);
    tardis_result result_tardises(db->query<tardis>(tardis_query::track_id == result_track->getID()));
    for (tardis_result::iterator current_tardis(result_tardises.begin()); current_tardis != result_tardises.end(); ++current_tardis){
        db->erase(*current_tardis);
    }
    db->erase(*result_track);
    t.commit();
}

void picturelist::open_track_filedialog(){
    QString file_name = QFileDialog::getOpenFileName(this, "Select the track", QDir::homePath());
    if(isthereatrack())
        delete_track();
    QFuture<void> future = QtConcurrent::run(upload_track, file_name,current_event_int,current_user_string);
    if(future.isFinished())
        ui->track_info->setText("Track available");
    //upload_track(file_name);
}

int picturelist::upload_track(QString path_Q,int current_event_int,std::string current_user_string){
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
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error:" << file.errorString();
        return 1;
    }
    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError()) {
        inputStream.readNext();
        double lat, lon;
        if (inputStream.isStartElement()) {
            odb::core::transaction t(db->begin());
            QString name = inputStream.name().toString();
            if (name == "trkpt") {
                lat = inputStream.attributes().value("lat").toDouble();
                lon = inputStream.attributes().value("lon").toDouble();
            }
            if (name == "time") {
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

QList<int> picturelist::getselectedimagelist(){
    QList<int> return_list;
    for(auto iterator : ui->image_list->selectedItems())
        if(iterator->isSelected())
            return_list << ui->image_list->row(iterator);
    return return_list;
}

void picturelist::download_images(){
	if(!QDir("Folder").exists())
	QDir().mkdir("C:/images");//Talán jó
    for(auto iterator : getselectedimagelist()){
        QString randomfilename("C:/images/");
        randomfilename.append(GetRandomString()).append(".png");
        QFile newDoc(randomfilename);
        if(newDoc.open(QIODevice::WriteOnly)){
            newDoc.write(this->imagepointer_list.value(iterator)->getBlob());
        }
        newDoc.close();
    }
}

QString picturelist::GetRandomString(){
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

void picturelist::on_download_clicked(){
    download_images();
}

void picturelist::on_searchbygpx_clicked(){
    QElapsedTimer timer;
        timer.start();
    ui->image_list->clear();
    QList<int> lista;
    int index = 0;
    for(auto i : tardispointer_list){
        for(int index=0;index<imagepointer_list.size();index++)
            if(i->getDate().addSecs(-7)<= imagepointer_list.at(index)->getDate() && imagepointer_list.at(index)->getDate() <= i->getDate().addSecs(7)){
                double lat1r, lon1r, lat2r, lon2r, u, v;
                lat1r = (((i->getLatitude())*3.14))/180;
                lon1r = (((i->getLongitude())*3.14))/180;
                lat2r = (((imagepointer_list.at(index)->getLatitude())*3.14))/180;
                lon2r = (((imagepointer_list.at(index)->getLongitude())*3.14))/180;
                u = sin((lat2r - lat1r)/2);
                v = sin((lon2r - lon1r)/2);
                if((2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000)<20){
                lista << index;
                qDebug() << imagepointer_list.at(index)->getDate() << "\t\t" << 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000;
                }
            }
            index++;
    }
    QSet<int> eredmeny = lista.toSet();
    for(auto i : eredmeny){
        QPixmap imagefrom;
        imagefrom.loadFromData(imagepointer_list.at(i)->getBlob());
        ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom),""));
                qDebug() << i<<"\t\t"<<eredmeny.count();
   }
     qDebug() << timer.elapsed();

    }/*


    QElapsedTimer timer;
    timer.start();
    QList<int> lista;
    int index = 0;
    int lowest_index = 0;
    for(auto i : tardispointer_list){
        if(lowest_index<imagepointer_list.size()-1){
            while(i->getDate().addSecs(-7)>=imagepointer_list.at(lowest_index)->getDate()){
                lowest_index++;
                index=lowest_index;
        }}
        else{
            index=lowest_index;
        }
        while(index < imagepointer_list.size()-1 && imagepointer_list.at(index)->getDate() <= i->getDate().addSecs(7)){
            if(i->getDate().addSecs(-7)<= imagepointer_list.at(index)->getDate() && imagepointer_list.at(index)->getDate() <= i->getDate().addSecs(7)){
                double lat1r, lon1r, lat2r, lon2r, u, v;
                lat1r = (((i->getLatitude())*3.14))/180;
                lon1r = (((i->getLongitude())*3.14))/180;
                lat2r = (((imagepointer_list.at(index)->getLatitude())*3.14))/180;
                lon2r = (((imagepointer_list.at(index)->getLongitude())*3.14))/180;
                u = sin((lat2r - lat1r)/2);
                v = sin((lon2r - lon1r)/2);
                if((2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000)<20){
                    lista << index;
                qDebug() << imagepointer_list.at(index)->getDate() << "\t\t" << 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000;
                }
            }
            index++;
        }
    }        qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";

        QSet<int> eredmeny = lista.toSet();
        for(auto i : eredmeny)
            qDebug() << i;
}
    /*for(auto i : tardispointer_list){
        if(index<imagepointer_list.size())
            while(!(i->getDate().addSecs(-7)>imagepointer_list.at(index)->getDate())){
                lowest_index++;
                index=lowest_index;
        }
        while(imagepointer_list.at(index)->getDate() <= i->getDate().addSecs(7)){
            if(i->getDate().addSecs(-7)<= imagepointer_list.at(index)->getDate() && imagepointer_list.at(index)->getDate() <= i->getDate().addSecs(7)){
                double lat1r, lon1r, lat2r, lon2r, u, v;
                lat1r = (((i->getLatitude())*3.14))/180;
                lon1r = (((i->getLongitude())*3.14))/180;
                lat2r = (((imagepointer_list.at(index)->getLatitude())*3.14))/180;
                lon2r = (((imagepointer_list.at(index)->getLongitude())*3.14))/180;
                u = sin((lat2r - lat1r)/2);
                v = sin((lon2r - lon1r)/2);
                qDebug() << QString::number(2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000) << index << "\t\t"<< lowest_index<<"\t\t<"<<imagepointer_list.size();
            }
            index++;
        }
    }*/



void picturelist::on_horizontalSlider_valueChanged(int value)
{
    ui->distance->setText(QString::number(value));
}
