/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Add or Modify Dialog Class.
 *
******************************************************************/

#ifndef ADDMODIFY_H
#define ADDMODIFY_H

#include <QDialog>
#include "login.h"

namespace Ui {
class AddModify;
}

class AddModify : public QDialog
{
    Q_OBJECT

public:
    explicit AddModify(QWidget *parent = 0);
    ~AddModify();

private slots:
    void on_pushButton_Add_clicked();

private:
    Ui::AddModify *ui;
};

#endif // ADDMODIFY_H
