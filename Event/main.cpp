#include "event.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Event e;
    e.show();

    return a.exec();
}
