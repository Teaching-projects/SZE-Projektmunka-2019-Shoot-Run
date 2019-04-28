#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QTableWidget>
#include <QWidget>
#include <QCryptographicHash>


namespace Ui {
class eventwindow;
}

class eventwindow : public QWidget
{
    Q_OBJECT
public:
    explicit eventwindow(QWidget *parent = nullptr);
    int last_clicked_row;
    ~eventwindow();
private slots:
    void on_add_button_clicked();
    void on_logout_button_clicked();
    void on_exit_button_clicked();
    void on_search_buton_clicked();
    void on_select_button_clicked();
    void on_event_list_cellClicked(int row, int column);
    void on_search_reset_clicked();
private:
    Ui::eventwindow *ui;
    void show_eventlist();
    void search_word();
};

#endif // EVENTWINDOW_H
