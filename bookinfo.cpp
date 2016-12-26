#include "bookinfo.h"
#include "ui_bookinfo.h"

BookInfo::BookInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookInfo)
{
    ui->setupUi(this);
}

BookInfo::~BookInfo()
{
    delete ui;
}
