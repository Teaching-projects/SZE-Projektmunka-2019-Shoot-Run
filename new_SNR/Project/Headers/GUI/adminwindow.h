#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QTableView>

#include <QTableWidget>

class image; class odbevent;

namespace Ui {
class adminwindow;
}

class adminwindow : public QWidget{
    Q_OBJECT
public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();
private slots:
    void on_exit_button_clicked();
    void on_logout_button_clicked();
    void on_event_accept_clicked();
    void on_event_delete_clicked();
    void on_event_filterreset_clicked();
    void on_event_list_itemDoubleClicked(QTableWidgetItem *item);


void on_event_name_textChanged(const QString &arg1);
void on_event_both_clicked();
void on_event_notaccepted_clicked();
void on_event_accepted_clicked();
void on_date_from_editingFinished();
void on_date_to_editingFinished();



void on_event_add_clicked();



void on_back_clicked();


void on_event_list_itemSelectionChanged();

private:
    Ui::adminwindow *ui;
//image
	int last_clicked_row = -1;
    QList<image*>   imagepointer_list;
    QList<int>      get_selectedimages();
    void            accept_images(QList<int>);
    void            delete_images(QList<int>);
    void            load_images();
    void            loadfrom_imagepointer();
    void            filter_images();
    void            image_upload_filedialog();
    void            image_upload(QString);
//event
    QList<odbevent*>    eventpointer_list;
    QList<int>          get_selectedevents();
    void                accept_events(QList<int>);
    void                delete_events(QList<int>);
    void                load_events();
    void                loadfrom_eventpointer();
    void                filter_events();



    void set_options();

};

#endif // ADMINWINDOW_H
