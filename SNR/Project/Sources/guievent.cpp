#include "guievent.h"
#include <QtWidgets>

GuiEvent::GuiEvent(QWidget *parent) :
    QDialog(parent)
{
    uploadButton = new QPushButton(tr("&Upload pictures"));
    uploadButton->setEnabled(true);
    backButton = new QPushButton(tr("&Back"));
    backButton->setEnabled(true);
    trackButton = new QPushButton(tr("&Track upload"));
    trackButton->setEnabled(true);
    infotrackButton = new QPushButton(tr("&Track info"));
    infotrackButton->setEnabled(true);
    okButton = new QPushButton(tr("&List pictures"));
    okButton->setEnabled(true);
    dloadButton = new QPushButton(tr("&Download pictures"));
    dloadButton->setEnabled(true);

    m_listeWidget=new QListWidget(this);
    m_listeWidget->setViewMode(QListWidget::IconMode);
    m_listeWidget->setIconSize(QSize(200,200));
    m_listeWidget->setResizeMode(QListWidget::Adjust);
    m_listeWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Elso.jpg"),""));
    m_listeWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Masodik.jpg"),""));
    m_listeWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Harmadik.jpg"),""));
    m_listeWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Negyedik.jpg"),""));
    m_listeWidget->addItem(new QListWidgetItem(QIcon("C:/Users/Kocsis/Desktop/Project/Gui/Otodik.jpg"),""));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(uploadButton, 1,0);
    layout->addWidget(infotrackButton, 3,0);
    layout->addWidget(dloadButton, 2,0);
    layout->addWidget(trackButton, 1,1);
    layout->addWidget(okButton, 2,1);
    layout->addWidget(backButton, 3,1);
    layout->addWidget(m_listeWidget, 0,0,1,0);

    setLayout(layout);
    setWindowTitle(tr("Event"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.64);

    filtereddialog=new FilteredDialog(this);

    connect(okButton, SIGNAL(clicked()), this, SLOT(filterPictures()));
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
}

void GuiEvent::back(){
   GuiEvent::close();
}

void GuiEvent::filterPictures(){
    filtereddialog->show();
}
