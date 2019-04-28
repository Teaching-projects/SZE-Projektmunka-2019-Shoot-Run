#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QTableView>

class image;
namespace Ui {
class adminwindow;
}

class adminwindow : public QWidget{
    Q_OBJECT
public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();
private slots:
    void on_filter_clicked();
    void on_filter_reset_clicked();
    void on_event_accept_clicked();
    void on_event_delete_clicked();
    void on_logout_button_clicked();
    void on_switchto_image_clicked();
    void on_switchto_event_clicked();
    void on_exit_button_clicked();
    void on_search_reset_clicked();
    void on_search_buton_clicked();
    void on_add_button_clicked();
    void on_select_button_clicked();
    void on_event_list_image_cellClicked(int row, int column); 
    void on_image_upload_clicked();
    void on_back_clicked();
    void on_image_accept_clicked();
    void on_image_delete_clicked();
    void on_image_filter_clicked();

private:
    Ui::adminwindow *ui;
	int last_clicked_row = -1;
    QList<image*> imagepointer_list;
    void filter_eventlist();
    void set_options();
    QList<int> getSelected();
    void accept_events(QList<int>);
    void delete_events(QList<int>);
    void show_eventlist();
    void search_word();
	QList<int> getselectedimagelist();
    void open_image_filedialog();
    void upload_image(QString);
    void list_images();
    void delete_images(QList<int>);
    void accept_images(QList<int>);
};

#endif // ADMINWINDOW_H
