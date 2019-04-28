#define earthRadiusKm 6371.0        //TODO valami könyvtárra cserélni
#define M_PI 3.14159265358979323846    //TODO

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
    return a.exec();
}
