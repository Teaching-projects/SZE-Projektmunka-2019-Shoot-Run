#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QTableView>
#include <QTableWidget>

class image; class odbevent; class tardis;
namespace Ui {
class userwindow;
}

class userwindow : public QWidget
{
    Q_OBJECT

public:
    explicit userwindow(QWidget *parent = nullptr);
    ~userwindow();

private slots:
    void on_exit_button_clicked();
    void on_logout_button_clicked();
    void on_event_filterreset_clicked();
    void on_event_add_clicked();
    void on_image_upload_clicked();
    void on_back_clicked();
    void on_image_track_upload_clicked();
    void on_image_search_clicked();
    void on_event_list_itemDoubleClicked(QTableWidgetItem *item);
    void on_event_name_textChanged(const QString &arg1);
    void on_date_from_editingFinished();
    void on_date_to_editingFinished();

    void on_image_download_clicked();

private:
    Ui::userwindow*     ui;
    std::string         current_user_string;
//image
    int                 last_clicked_row = -1;
    QList<image*>       imagepointer_list;
    QList<int>          get_selectedimages();
    void                load_images();
    void                loadfrom_imagepointer();
    void                loadfrom_blob(QPixmap*,QByteArray);
    void                filter_images();
    void                image_upload_filedialog();
    static void         image_upload(QString,int,std::string,QList<image*>*);
//event
    QList<odbevent*>    eventpointer_list;
    QList<int>          get_selectedevents();
    void                load_events();
    void                loadfrom_eventpointer();
    void                filter_events();

    void set_options();
    QString             GetRandomString();

//track
    static int          upload_track(QString,int,std::string);
    void                open_track_filedialog();
    int                 isthereatrack();
    void                delete_track();
//tardis
    QList<tardis*>      tardispointer_list;
};

#endif // USERWINDOW_H
