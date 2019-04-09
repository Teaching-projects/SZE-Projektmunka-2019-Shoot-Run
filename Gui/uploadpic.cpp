#include "uploadpic.h"
#include "ui_uploadpic.h"

UploadPic::UploadPic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadPic)
{
    ui->setupUi(this);
}

UploadPic::~UploadPic()
{
    delete ui;
}
