#include "filtereddialog.h"
#include <QtWidgets>

FilteredDialog::FilteredDialog(QWidget *parent) :
    QDialog(parent){
    dloadButton = new QPushButton(tr("&Download"));
    dloadButton->setEnabled(true);

    backButton = new QPushButton(tr("&Back"));
    backButton->setEnabled(true);

    listWidget=new QListWidget(this);
    listWidget->setViewMode(QListWidget::IconMode);
    listWidget->setIconSize(QSize(200,200));
    listWidget->setResizeMode(QListWidget::Adjust);
    listWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Elso.jpg"),""));
    listWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Masodik.jpg"),""));
    listWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Harmadik.jpg"),""));
    listWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Negyedik.jpg"),""));
    listWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Otodik.jpg"),""));

     QGridLayout *layout = new QGridLayout;
     layout->addWidget(listWidget,0,0,1,0);
     layout->addWidget(dloadButton,1,0);
     layout->addWidget(backButton,1,1);

     setLayout(layout);
     setWindowTitle(tr("Event"));
     setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
     resize(QDesktopWidget().availableGeometry(this).size() * 0.64);
     connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
}

void FilteredDialog::back(){
    FilteredDialog::close();
}

