#ifndef GUIEVENT_H
#define GUIEVENT_H

#include <QDialog>
#include "filtereddialog.h"

#include "image-odb.hxx"
#include "user-odb.hxx"
#include "event-odb.hxx"
#include "database.h"

class image;
class user;
class event;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QListWidget;

class GuiEvent : public QDialog, public DB
{
    Q_OBJECT

public:
    explicit GuiEvent(QWidget *parent = nullptr);
	void load(QString);
private:
    QPushButton *uploadButton;
    QPushButton *backButton;
    QPushButton *trackButton;
    QPushButton *infotrackButton;
    QPushButton *okButton;
    QPushButton *dloadButton;
    QListWidget *m_listeWidget;

    FilteredDialog *filtereddialog;


public slots:
    void back();
    void filterPictures();
	void filewindow();
};
#endif // GUIEVENT_H
