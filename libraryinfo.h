/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Library and Recommendation Window Class.
 *
******************************************************************/

#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <QDialog>
#include "login.h"
#include "addmodify.h"
#include "recommend.h"

namespace Ui {
class LibraryInfo;
}

class LibraryInfo : public QDialog
{
    Q_OBJECT

public:
    QString username; //Operation all under this account.
    explicit LibraryInfo(QWidget *parent = 0);
    ~LibraryInfo();

private slots:
    void on_pushButton_PostComment_clicked();

    void on_pushButton_Rank_clicked();

    void on_pushButton_Search_clicked();

    void on_pushButton_AddorModify_clicked();

    void on_pushButton_Person_clicked();

private:
    Ui::LibraryInfo *ui;
};

#endif // LIBRARYINFO_H
