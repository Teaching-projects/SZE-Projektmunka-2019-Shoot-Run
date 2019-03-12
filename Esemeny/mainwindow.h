#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "evententry.h"
#include "eventcontroller.h"

#include <QMainWindow>
#include <QHash>
#include <QListWidgetItem>

// Forward declaration:
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(EventController *controller, QWidget *parent = 0);

    ~MainWindow();

private:

    Ui::MainWindow *ui;

    QHash<QListWidgetItem*, EventEntry*> m_entryMap;

    EventController *m_eventController;

    void setupSignals();

private slots:
    void addEntry();
    void removeEntry();
    void editItem();
    void saveItem();
    void discardItem();
    void resetItem();
};

#endif
