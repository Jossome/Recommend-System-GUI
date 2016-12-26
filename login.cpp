/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Login Window Class.
 *
******************************************************************/

#include "login.h"
#include "ui_login.h"
#include <QPixmap>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //Picture
    QPixmap pix("D:/Jossome/QT/Login/pic.png"); //Need absolute directory, change if necessary.
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    //Connection
    if(!connOpen())
        ui->Status->setText("Fail to open the database.");
    else
        ui->Status->setText("Database connected.");
}

Login::~Login()
{
    delete ui;
}

void Login::connClose() {
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Login::connOpen() {
    //Connection
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/Jossome/QT/sqlite/library.db");
    if(!mydb.open()) {
        qDebug() << ("Fail to connect the database.");
        return false;
    }
    else {
        qDebug() << ("Database connected.");
        return true;
    }
}

void Login::on_pushButton_Login_clicked()
{
    QString username, password;
    username = ui->lineEdit_Username->text();
    password = ui->lineEdit_Password->text();

    if (!connOpen()) {
        qDebug() << "Fail to connect the database.";
        return;
    }

    connOpen();
    QSqlQuery q;
    q.prepare("select * from `BX-Users-N` where `User-ID` = '" + username + "' and password = '" + password + "'");

    //Check username and password
    if (q.exec()) {
        int count = 0;
        while(q.next()) count++;
        if (count == 1) {
            ui->Status->setText("Login successfully!");
            QSqlQuery q1;
            q1.prepare("update `BX-Users-N` set lasttime = DATETIME('now') where `User-ID` = '" + username + "'");
            if (q1.exec())
                ui->Status->setText("Login info updated!");

            connClose();

            //Open another window.
            this->hide();
            LibraryInfo libraryinfo;
            libraryinfo.setModal(true);
            libraryinfo.exec();
        }
        else if (count > 1)
            ui->Status->setText("Duplicate username and password!");
        else
            ui->Status->setText("Password not correct or username not exists!");
    }

}

void Login::on_pushButton_SignUp_clicked()
{
    SignUp signup;
    signup.setModal(true);
    signup.exec();

}
