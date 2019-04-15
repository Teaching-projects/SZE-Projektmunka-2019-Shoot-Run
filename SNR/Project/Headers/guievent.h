#ifndef GUIEVENT_H
#define GUIEVENT_H

#include <QDialog>
#include "filtereddialog.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QListWidget;

class GuiEvent : public QDialog
{
    Q_OBJECT

public:
    explicit GuiEvent(QWidget *parent = nullptr);
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

};
#endif // GUIEVENT_H
