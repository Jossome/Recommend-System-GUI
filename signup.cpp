/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Sign Up Dialog Class.
 *
******************************************************************/

#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_SubmitSignUp_clicked()
{
    QString country, state, city, age, password, repeat;
    country  = ui->lineEdit_Country->text();
    state    = ui->lineEdit_State->text();
    city     = ui->lineEdit_City->text();
    age      = ui->lineEdit_Age->text();
    password = ui->lineEdit_Password->text();
    repeat   = ui->lineEdit_Repeat->text();

    Login conn;
    if (!conn.connOpen()) {
        qDebug() << "Fail to connect the database.";
        return;
    }

    //conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into `BX-Users-N` (`User-ID`, Age, city, state, country, password, isOld) select (MAX(`User-ID`)+1), " + age + ", '" + city + "', '" + state + "', '" + country + "', '" + password + "', 0 from `BX-Users-N`");
    if (password == repeat) {
        if (qry.exec()) {
            qry.prepare("select MAX(`User-ID`) from `BX-Users-N`");
            if (qry.exec()){
                while (qry.next())
                    QMessageBox::about(NULL, "Success", "Sign up successfully! Your user ID is: " + qry.value(0).toString());
            }
            conn.connClose();
            this->hide();
        }
    }
    else {
        QMessageBox::about(NULL, "Fail", "Password not the same, please input again.");
    }

}
