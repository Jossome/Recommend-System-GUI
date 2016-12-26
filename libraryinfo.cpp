/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Library and Recommendation Window Class.
 *
******************************************************************/

#include "libraryinfo.h"
#include "ui_libraryinfo.h"
#include <QMessageBox>

LibraryInfo::LibraryInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibraryInfo)
{
    ui->setupUi(this);
    //connection
    Login conn;
    if(!conn.connOpen())
        ui->libStatus->setText("Fail to open the database.");
    else {
        QSqlQuery q;
        q.prepare("select `User-ID` from `BX-Users-N` order by lasttime desc limit 1");
        if (q.exec())
            while (q.next())
                username = q.value(0).toString();
        ui->welcomeTag->setText("Welcome! User ID: " + username);
        ui->libStatus->setText("Database connected.");
    }
}

LibraryInfo::~LibraryInfo()
{
    delete ui;
}

void LibraryInfo::on_pushButton_PostComment_clicked()
{
    QString ISBN, rank, comment;
    ISBN = ui->lineEdit_ISBN->text();
    rank = ui->lineEdit_Rank->text();
    comment = ui->lineEdit_Comment->text();

    Login conn;
    conn.connOpen();
    QSqlQuery q;

    q.prepare("insert into `BX-Book-Ratings-N` (`User-ID`, ISBN, `Book-Rating`, Comment) values (" + username + ", '" + ISBN + "', " + rank + ", '" + comment + "')");
    if (q.exec()) {
        QSqlQuery q1;
        q1.prepare("update `BX-Books-New` set `Book-Rating` = (select avg(`Book-Rating`) from `BX-Book-Ratings-N` where ISBN = '" + ISBN + "' and `Book-Rating` != 0) where ISBN = '" + ISBN + "'");
        if (q1.exec()) {
            QMessageBox::about(NULL, "Success", "Comment and rate successfully!");
        }
        conn.connClose();
    }
}

void LibraryInfo::on_pushButton_Rank_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select * from `BX-Books-New` order by `Book-Rating` desc limit 10");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_Rec->setModel(modal);
    conn.connClose();
    qDebug() << (modal->rowCount());
}

void LibraryInfo::on_pushButton_Search_clicked()
{
    QString ISBN;
    ISBN = ui->lineEdit_ISBN->text();
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQueryModel *modal1 = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    //Request for the book information
    qry->prepare("select * from `BX-Books-New` where ISBN = " + ISBN + "");
    qry->exec();
    int count = 0;
    while (qry->next()) count++;
    if (count == 0)
        QMessageBox::about(NULL, "Warning", "No this book in the database!");
    modal->setQuery(*qry);
    ui->tableView_BookInfo->setModel(modal);

    //Request for the comment and ranking information
    QSqlQuery *qry1 = new QSqlQuery(conn.mydb);
    qry1->prepare("select `User-ID`, `Book-Rating`, `Comment` from `BX-Book-Ratings-N` where ISBN = " + ISBN + "");
    qry1->exec();
    count = 0;
    while(qry1->next()) count++; //Record the number of comments
    ui->label_commentCount->setText(QString::number(count) + " comments in total.");
    modal1->setQuery(*qry1);
    ui->tableView_Comm->setModel(modal1);
    conn.connClose();
    qDebug() << (modal->rowCount());
}

void LibraryInfo::on_pushButton_AddorModify_clicked()
{
    //Check if this account is administrator. Default administrator user id is 8.
    if (username == QString("8")) {
        AddModify addmodify;
        addmodify.setModal(true);
        addmodify.exec();
    }
    else
        QMessageBox::warning(NULL, "Warning", "You have no priority to do so.");
}

void LibraryInfo::on_pushButton_Person_clicked()
{
    int newTag;
    Login conn;
    conn.connOpen();
    Recommend recommend;

    recommend.loadData();
    QSqlQuery q;
    q.prepare("select `isOld` from `BX-Users-N` where `User-ID` = " + username);
    if (q.exec())
        while (q.next())
            newTag = q.value(0).toInt();
    std::vector<std::string> res;
    if (newTag == 0) {  //New user
        res = recommend.newRec();
        //Set as old
        QSqlQuery qup;
        qup.prepare("update `BX-Users-N` set isOld = 1 where `User-ID` = " + username);
        qup.exec();
    }
    else {  //Old user.
        res = recommend.oldRec(username.toStdString());
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);
    //QMessageBox::about(NULL, "hehfe", QString::fromStdString(res[2]));
    qry->prepare("select * from `BX-Books-New` where ISBN = " + QString::fromStdString(res[0]) + " or ISBN =" + QString::fromStdString(res[1]) + " or ISBN = " + QString::fromStdString(res[2]) + "");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_Rec->setModel(modal);
    conn.connClose();
}
