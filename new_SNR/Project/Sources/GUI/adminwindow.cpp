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
#include "exif.h"

adminwindow::adminwindow(QWidget *parent) : QWidget(parent), ui(new Ui::adminwindow){
    ui->setupUi(this);
    ui->event_list->horizontalHeader()->setVisible(true);
    ui->event_list_image->horizontalHeader()->setVisible(true);
    ui->event_list_image->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->event_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    set_options();
    filter_eventlist();
    ui->stackedWidget->setCurrentIndex(0);
    search_word();
}

adminwindow::~adminwindow(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    delete ui;
}

void adminwindow::set_options(){
    ui->date_from->setMaximumDateTime(QDateTime::currentDateTime());
    ui->date_to->setMaximumDateTime(QDateTime::currentDateTime());
    ui->date_to->setDateTime(QDateTime::currentDateTime());
    ui->filter_both->click();
    ui->filter_name->setText("");
}

void adminwindow::filter_eventlist(){
    int row=0;
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<odbevent> query;
    typedef odb::result<odbevent> result;
    odb::core::transaction t(db->begin());
    std::string search_condition("%");
    search_condition.append(ui->filter_name->text().toStdString().append("%"));
    if(ui->filter_both->isChecked() == true){
        result r(db->query<odbevent>(query::event_name.like (search_condition) && query::event_date >= QDateTime::fromString(ui->date_from->text(),"yyyy. MM. dd.") && query::event_date <= QDateTime::fromString(ui->date_to->text(),"yyyy. MM. dd.")));
        for (result::iterator i(r.begin()); i != r.end(); ++i){
            ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
            ui->event_list->setItem(row, 0, new QTableWidgetItem(i->getname()));
            ui->event_list->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
            ui->event_list->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
            row++;
        }
    }
    else if(ui->filter_accepted->isChecked() == true){
        result r(db->query<odbevent>(query::event_name.like (search_condition) && query::event_accepted == 1 && query::event_date >= QDateTime::fromString(ui->date_from->text(),"yyyy. MM. dd.") && query::event_date <= QDateTime::fromString(ui->date_to->text(),"yyyy. MM. dd.")));
        for (result::iterator i(r.begin()); i != r.end(); ++i){
            ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
            ui->event_list->setItem(row, 0, new QTableWidgetItem(i->getname()));
            ui->event_list->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
            ui->event_list->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
            row++;
        }
    }
    else if(ui->filter_notaccepted->isChecked() == true){
        result r(db->query<odbevent>(query::event_name.like (search_condition) && query::event_accepted == 0 && query::event_date >= QDateTime::fromString(ui->date_from->text(),"yyyy. MM. dd.") && query::event_date <= QDateTime::fromString(ui->date_to->text(),"yyyy. MM. dd.")));
        for (result::iterator i(r.begin()); i != r.end(); ++i){
            ui->event_list->setRowCount(ui->event_list->rowCount() + 1);
            ui->event_list->setItem(row, 0, new QTableWidgetItem(i->getname()));
            ui->event_list->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
            ui->event_list->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
            row++;
        }
    }
t.commit();
}

void adminwindow::on_filter_clicked(){
    ui->event_list->model()->removeRows(0, ui->event_list->rowCount());
    filter_eventlist();
}

void adminwindow::on_filter_reset_clicked(){
    set_options();
}

QList<int> adminwindow::getSelected(){
    QList<int> selected_list;
    for(auto iterator: ui->event_list->selectedItems()){
        if(iterator->column()==2)
        selected_list << iterator->data(Qt::DisplayRole).toInt();
    }
    return selected_list;
}

void adminwindow::on_event_accept_clicked(){
    QList<int>selected = getSelected();
    if(!selected.empty()){
    accept_events(selected);
    ui->event_list->model()->removeRows(0, ui->event_list->rowCount());
    filter_eventlist();
    }
}

void adminwindow::on_event_delete_clicked(){
    QList<int>selected = getSelected();
    if(!selected.empty()){
    delete_events(selected);
    ui->event_list->model()->removeRows(0, ui->event_list->rowCount());
    filter_eventlist();
    }
}

void adminwindow::accept_events(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<odbevent> query;
    typedef odb::result<odbevent> result;
    odb::core::transaction t(db->begin());
    result event_result(db->query<odbevent>(query::event_id.in_range(selected.begin(),selected.end()) ));
    for (result::iterator event_iterator(event_result.begin()); event_iterator != event_result.end(); ++event_iterator){
        event_iterator->Accept();
        db->update(*event_iterator);
    }
    t.commit();
}

void adminwindow::delete_events(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<odbevent> query;
    typedef odb::result<odbevent> result;
    odb::core::transaction t(db->begin());
    result event_result(db->query<odbevent>(query::event_id.in_range(selected.begin(),selected.end()) ));
    for (result::iterator event_iterator(event_result.begin()); event_iterator != event_result.end(); ++event_iterator)
        db->erase(*event_iterator);
    t.commit();
}

void adminwindow::on_logout_button_clicked(){
    mainwindow* new_login = new mainwindow;
    new_login->show();
    this->close();
}

void adminwindow::on_switchto_image_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}

void adminwindow::on_switchto_event_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
    show_eventlist();
}
//lefele image rész
void adminwindow::on_exit_button_clicked(){
    QCoreApplication::quit();
}

void adminwindow::on_search_reset_clicked(){
    ui->search_name->setText("");
    ui->event_list_image->model()->removeRows(0, ui->event_list_image->rowCount());
    show_eventlist();
}

void adminwindow::on_search_buton_clicked(){
    ui->event_list_image->model()->removeRows(0, ui->event_list_image->rowCount());
    search_word();
}

void adminwindow::on_add_button_clicked(){
    addeventdialog* event_dialog = new addeventdialog();
    event_dialog->setModal(true);
    event_dialog->show();
}

void adminwindow::show_eventlist(){
    QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<odbevent> query;
    typedef odb::result<odbevent> result;
    odb::core::transaction t(db->begin());
    result r(db->query<odbevent>(query::event_accepted == 1));
    int row=0;
    for (result::iterator i(r.begin()); i != r.end(); ++i){
        ui->event_list_image->setRowCount(ui->event_list_image->rowCount() + 1);
        ui->event_list_image->setItem(row, 0, new QTableWidgetItem(i->getname()));
        ui->event_list_image->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
        ui->event_list_image->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
        row++;
    }
t.commit();
}

void adminwindow::search_word(){
    ui->event_list_image->model()->removeRows(0, ui->event_list_image->rowCount());
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
            ui->event_list_image->setRowCount(ui->event_list_image->rowCount() + 1);
            ui->event_list_image->setItem(row, 0, new QTableWidgetItem(i->getname()));
            ui->event_list_image->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
            ui->event_list_image->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
            row++;
        }
        t.commit();
    }
    else{
        QMessageBox::information(this,"Error!", "There is no event with this name!");
        result r(db->query<odbevent>(query::event_accepted == 1));
        for (result::iterator i(r.begin()); i != r.end(); ++i){
            ui->event_list_image->setRowCount(ui->event_list_image->rowCount() + 1);
                 ui->event_list_image->setItem(row, 0, new QTableWidgetItem(i->getname()));
                 ui->event_list_image->setItem(row, 1, new QTableWidgetItem(i->getdate().toString("yyyy-MM-dd")));
                 ui->event_list_image->setItem(row, 2, new QTableWidgetItem(QString::number(i->getid())));
                 row+=1;
        }
        t.commit();
    }
}

void adminwindow::on_select_button_clicked(){
    if(last_clicked_row != -1){
	ui->stackedWidget->setCurrentIndex(2);
    }
}

void adminwindow::on_event_list_image_cellClicked(int row, int column){
    last_clicked_row = row;
}

//3.oldal

void adminwindow::list_images(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    ui->image_list->clear();
    ui->image_list->model()->removeRows(0, ui->event_list->rowCount());
	QSharedPointer<odb::core::database> db = DB::create_database();
    typedef odb::query<image>   query;
    typedef odb::result<image>  result;
    odb::core::session s;
	odb::core::transaction t(db->begin());
    if(ui->image_both->isChecked()){
        result r(db->query<image>(query::event_id == ui->event_list_image->item(last_clicked_row, 2)->text().toInt()));
        for (auto value : r){
            imagepointer_list << new image(value);
            QPixmap imagefrom;
            imagefrom.loadFromData(value.getBlob());
            ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom), ""));
        }
    }
    else if(ui->image_accepted->isChecked()){
        result r(db->query<image>(query::event_id == ui->event_list_image->item(last_clicked_row, 2)->text().toInt() && query::image_accepted == true));
        for (auto value : r) {
            imagepointer_list << new image(value);
            QPixmap imagefrom;
            imagefrom.loadFromData(value.getBlob());
            ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom), ""));
        }
    }
    else if(ui->image_waiting->isChecked()){
        result r(db->query<image>(query::event_id == ui->event_list_image->item(last_clicked_row, 2)->text().toInt() && query::image_accepted == false));
        for (auto value : r) {
            imagepointer_list << new image(value);
            QPixmap imagefrom;
            imagefrom.loadFromData(value.getBlob());
            ui->image_list->addItem(new QListWidgetItem(QIcon(imagefrom), ""));
        }
    }
t.commit();
}

QList<int> adminwindow::getselectedimagelist(){
	QList<int> return_list;
	for (auto iterator : ui->image_list->selectedItems())
		if (iterator->isSelected())
			return_list << ui->image_list->row(iterator);
	return return_list;
}

void adminwindow::open_image_filedialog(){
    QStringList file_names = QFileDialog::getOpenFileNames(this, "Select the picture", QDir::homePath());
    int uploaded_number = 0;
    ui->upload->setText(QString::number(uploaded_number).append("/").append(QString::number(file_names.size())));
    for (int i = 0; i < file_names.size(); ++i){
        upload_image(file_names.at(i));
        uploaded_number++;
        ui->upload->setText(QString::number(uploaded_number).append("/").append(QString::number(file_names.size())));
    }

}

void adminwindow::upload_image(QString filename){
	std::string path = filename.toStdString();
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

	QSharedPointer<user> current_user = db->query_one<user>(u_query::user_name == "admin");
    QSharedPointer<odbevent> current_event = db->query_one<odbevent>(e_query::event_id == ui->event_list_image->item(last_clicked_row, 2)->text().toInt());
	QSharedPointer<image> new_image(new image(path, current_event, current_user, date, result.GeoLocation.Longitude, result.GeoLocation.Latitude));
    new_image->Accept();
    db->persist(new_image);
	new_image->user(current_user); new_image->odbevent(current_event);
	current_user->images().push_back(new_image);
	current_event->images().push_back(new_image);
	db->update(current_event); db->update(current_user);
	t.commit();
}

void adminwindow::on_image_upload_clicked(){
    open_image_filedialog();
}

void adminwindow::on_back_clicked(){
    if(!imagepointer_list.isEmpty())
        this->imagepointer_list.clear();
    ui->image_list->clear();
    ui->image_list->model()->removeRows(0, ui->event_list->rowCount());
    ui->stackedWidget->setCurrentIndex(1);
}


void adminwindow::accept_images(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    for(auto iterator : selected){
        imagepointer_list.at(iterator)->Accept();
        db->update(*imagepointer_list.at(iterator));
    }
    t.commit();
}

void adminwindow::delete_images(QList<int> selected){
    QSharedPointer<odb::core::database> db = DB::create_database();
    odb::session s;
    odb::core::transaction t(db->begin());
    for(auto iterator : selected)
        db->erase(*imagepointer_list.at(iterator));
    t.commit();
}

void adminwindow::on_image_accept_clicked(){
    QList<int>selected = getselectedimagelist();
    if(!selected.empty()){
        accept_images(selected);
        list_images();
    }
}

void adminwindow::on_image_delete_clicked(){
    QList<int>selected = getselectedimagelist();
    if(!selected.empty()){
        delete_images(selected);
        list_images();
    }
}

void adminwindow::on_image_filter_clicked(){
    list_images();
}
