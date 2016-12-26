/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Sign Up Dialog Class.
 *
******************************************************************/

#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "login.h"

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = 0);
    ~SignUp();

private slots:
    void on_pushButton_SubmitSignUp_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
