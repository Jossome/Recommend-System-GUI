/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Add or Modify Dialog Class.
 *
******************************************************************/

#include "addmodify.h"
#include "ui_addmodify.h"
#include <QMessageBox>

AddModify::AddModify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddModify)
{
    ui->setupUi(this);
}

AddModify::~AddModify()
{
    delete ui;
}

void AddModify::on_pushButton_Add_clicked()
{
    QString ISBN, title, author, year, publisher, image_s, image_m, image_l;
    ISBN      = ui->lineEdit_ISBN->text();
    title     = ui->lineEdit_Title->text();
    author    = ui->lineEdit_Author->text();
    year      = ui->lineEdit_Year->text();
    publisher = ui->lineEdit_Publisher->text();
    image_s   = ui->lineEdit_ImageS->text();
    image_m   = ui->lineEdit_ImageM->text();
    image_l   = ui->lineEdit_ImageL->text();

    Login conn;

    conn.connOpen();
    QSqlQuery q;
    q.prepare("select * from `BX-Books-New` where `ISBN` = '" + ISBN + "'");

    //Judge whether to add or to modify.
    if (q.exec()) {
        int count = 0;
        while(q.next()) count++;
        if (count >= 1) {
            QSqlQuery q1;
            q1.prepare("update `BX-Books-New` set `Book-Title` = '" + title + "', `Book-Author` = '" + author + "', `Year-Of-Publication` = " + year + ", `Publisher` = '" + publisher + "', `Image-URL-S` = '" + image_s + "', `Image-URL-M` = '" + image_m + "', `Image-URL-L` = '" + image_l + "' where `ISBN` = '" + ISBN + "'");
            if(q1.exec()) {
                QMessageBox::about(NULL, "Book", "This book is already in the database. Modification will be conducted.");
            }
        }
        else {
            QSqlQuery q1;
            q1.prepare("insert into `BX-Books-New` (`ISBN`, `Book-Title`, `Book-Author`, `Year-Of-Publication`, `Publisher`, `Image-URL-S`, `Image-URL-M`, `Image-URL-L`, `Book-Rating`) values ('" + ISBN + "', '" + title + "', '" + author + "', " + year + ", '" + publisher + "', '" + image_s + "', '" + image_m + "', '" + image_l + "', 0)");
            if(q1.exec()) {
                QMessageBox::about(NULL, "Book", "This is a new book to be added.");
            }
        }
        conn.connClose();
        this->hide();
    }
}
