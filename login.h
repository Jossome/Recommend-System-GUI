/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Login Window Class.
 *
******************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "libraryinfo.h"
#include "signup.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose();
    bool connOpen();
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:

    void on_pushButton_Login_clicked();

    void on_pushButton_SignUp_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
