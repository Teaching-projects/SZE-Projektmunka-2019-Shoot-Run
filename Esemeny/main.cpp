#include "mainwindow.h"
#include "event.h"
#include "eventcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Event ev;
    EventController controller( &ev );
    MainWindow w( &controller );
    w.show();
    return a.exec();
}
