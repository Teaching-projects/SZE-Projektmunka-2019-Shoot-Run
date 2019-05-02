#ifndef PICTURELIST_H
#define PICTURELIST_H

#include <QWidget>
#include <QListWidget>

class image;
class tardis;

namespace Ui {
class picturelist;
}

class picturelist : public QWidget
{
    Q_OBJECT
public:
    explicit picturelist(QWidget *parent = nullptr);
    ~picturelist();
private slots:
    void on_back_clicked();
    void on_image_upload_clicked();
    void on_track_upload_clicked();
    void on_download_clicked();
    void on_searchbygpx_clicked();
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::picturelist *ui;
    void delete_track();
    void show_track_info();
    int isthereatrack();
    void list_images();
    void open_image_filedialog();
    void upload_image(QString);
    void open_track_filedialog();
    static int upload_track(QString,int ,std::string);
    int current_event_int;
    std::string current_user_string;
    QList<image*> imagepointer_list;
    QList<tardis*> tardispointer_list;
    void download_images();
    QList<int> getselectedimagelist();
    QString GetRandomString();
};

#endif // PICTURELIST_H
