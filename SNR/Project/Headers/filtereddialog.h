#ifndef FILTEREDDIALOG_H
#define FILTEREDDIALOG_H
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QListWidget;

class FilteredDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilteredDialog(QWidget *parent = nullptr);
private:
    QPushButton *dloadButton;
    QPushButton *backButton;
    QListWidget *listWidget;
public slots:
    void back();
};

#endif // FILTEREDDIALOG_H
