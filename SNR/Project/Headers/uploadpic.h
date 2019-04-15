#ifndef UPLOADPIC_H
#define UPLOADPIC_H

#include <QDialog>

namespace Ui {
class UploadPic;
}

class UploadPic : public QDialog
{
    Q_OBJECT

public:
    explicit UploadPic(QWidget *parent = nullptr);
    ~UploadPic();

private:
    Ui::UploadPic *ui;
};

#endif // UPLOADPIC_H
