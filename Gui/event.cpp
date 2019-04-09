#include "event.h"
#include <QtWidgets>

Event::Event(QWidget *parent) :
    QDialog(parent)
{
    uploadButton = new QPushButton(tr("&Upload"));
    uploadButton->setEnabled(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(uploadButton, 0,1);

    setLayout(layout);
    setWindowTitle(tr("Event"));
}
