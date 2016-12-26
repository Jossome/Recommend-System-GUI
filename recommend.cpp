/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Recommendation Class.
 *
******************************************************************/

#include "recommend.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
using namespace std;

Recommend::Recommend() { }

void Recommend::loadData() {
    usernumber=1;
    booknumber=1;
    //READ-IN FILE
    QSqlQuery q;
    q.prepare("select `User-ID`, Age, city, state, country from `BX-Users-N`");
    if (q.exec()) {
        while(q.next()) {
            user[usernumber].id = q.value(0).toString().toStdString();
            user[usernumber].age = q.value(1).toInt();
            user[usernumber].city = q.value(2).toString().toStdString();
            user[usernumber].state = q.value(3).toString().toStdString();
            user[usernumber].country = q.value(4).toString().toStdString();

            usernumber++;
        }
        usernumber--;
    }

    QSqlQuery q1;
    q1.prepare("select `ISBN`, `Book-Title`, `Book-Author`, `Year-Of-Publication`, `Publisher`, `Image-URL-S`, `Image-URL-M`, `Image-URL-L` from `BX-Books-New`");
    if (q1.exec()) {
        while(q1.next()) {
            book[booknumber].isbn = q1.value(0).toString().toStdString();
            int x = book[booknumber].isbn.size();
            for (int i = 0; i < 10 - x; i++) {
                string b = "0";
                b += book[booknumber].isbn;
                book[booknumber].isbn = b;
            }
            book[booknumber].title = q1.value(1).toString().toStdString();
            book[booknumber].author = q1.value(2).toString().toStdString();
            book[booknumber].pubyear = q1.value(3).toInt();
            book[booknumber].publisher = q1.value(4).toString().toStdString();
            book[booknumber].urls = q1.value(5).toString().toStdString();
            book[booknumber].urlm = q1.value(6).toString().toStdString();
            book[booknumber].urll = q1.value(7).toString().toStdString();
            booknumber++;
        }
        booknumber--;
    }

    int irate = 1;
    QSqlQuery q2;
    q2.prepare("select `User-ID`, `ISBN`, `Book-Rating` from `BX-Book-Ratings-N`");
    if (q2.exec()) {
        while(q2.next()) {
            rating[irate].id = q2.value(0).toString().toStdString();
            rating[irate].isbn = q2.value(1).toString().toStdString();
            rating[irate].bookrating = q2.value(2).toDouble();
            irate++;
        }
        irate--;
    }

    for(int i = 0;i<usernumber;i++)
        userindextable.insert(make_pair(user[i+1].id,i));

    for(int i = 0;i<booknumber;i++)
        bookindextable.insert(make_pair(book[i+1].isbn,i));

    ratingmatrix = new double *[usernumber];
    for (int i = 0; i < usernumber; i++) {
        ratingmatrix[i] = new double[booknumber];
    }
    for (int i=0;i<usernumber;i++)
        for(int j=0;j<booknumber;j++)
        {
            ratingmatrix[i][j] = 0;
        }

        for (int i = 0;i<irate-1;i++){
            int rownumber,columnnumber;

            MyMultimap<string,int>::iter p = userindextable.find(rating[i+1].id);
            rownumber = p->second;
            MyMultimap<string,int>::iter q = bookindextable.find(rating[i+1].isbn);
            columnnumber = q->second;
            ratingmatrix[rownumber][columnnumber] = rating[i+1].bookrating;
        }

    for (int i=0;i<booknumber;i++){
        int count = 0;
        double sum = 0;
        for(int j=0;j<usernumber;j++)
        {
            if(ratingmatrix[j][i] != 0) {
                count++;
                sum = sum+ratingmatrix[j][i];
            }
        }
        book[i+1].averagerate = sum/count*1.0;
        book[i+1].raternumber = count;
    }
}

vector<string> Recommend::newRec() {

    int min_dis=INT_MAX;
    User min_user;
    int num=1;
    int i;
    for(i=1;i<=usernumber;i++){
        int dis;
        dis=computeDistance(user[usernumber],user[i]);
        if(dis<min_dis){
            min_dis=dis;
            min_user=user[i];
            num=i;
        }
    }

    double rt[MAX_NUMBER_RATING];
    for(i=1;i<=booknumber;i++){
        rt[i]=ratingmatrix[num][i];
    }

    //QMessageBox::about(NULL, "dwd", QString::number(booknumber));
    sort(ratingmatrix[num],ratingmatrix[num]+booknumber);

    int target1=0,target2=0,target3=0;
    int mark1,mark2;
    int mark=booknumber;
    for(i=mark;i>=1;i--){
        if(ratingmatrix[num][i-1]!=ratingmatrix[num][i]){
            mark1=i-1;
            mark=i-1;
            break;
        }
    }
    for(i=mark;i>=1;i--){
        if(ratingmatrix[num][i-1]!=ratingmatrix[num][i]){
            mark2=i-1;
            break;
        }
    }
    for(i=1;i<=booknumber;i++){
        if(rt[i]==ratingmatrix[num][booknumber]){
            target1=i;
        }
        if(rt[i]==ratingmatrix[num][mark1]){
            target2=i;
        }
        if(rt[i]==ratingmatrix[num][mark2]){
            target3=i;
        }
    }

    vector<string> tmp;
    tmp.push_back(book[target1].isbn);
    tmp.push_back(book[target2].isbn);
    tmp.push_back(book[target3].isbn);

    return tmp;
}

vector<string> Recommend::oldRec(string id) {
    int idnumber, num_of_rec=3;
    MyMultimap<string,int>::iter p = userindextable.find(id);
    idnumber = p->second;
    vector<vector<double> > A;
    A.resize(usernumber);
    for(int i=0;i<usernumber;i++){
        A[i].resize(booknumber);
        for(int j=0;j<booknumber;j++)
            A[i][j]=ratingmatrix[i][j];
    }
    vector<double> result;

    bool warm;//indicate if cold start exists
    warm=recommend4old(result,A,idnumber,num_of_rec);
    if(warm){
        vector<string> tmp;
        for(int i=0;i<num_of_rec;i++)
        {
            tmp.push_back(book[(int)result[i]+1].isbn);
        }
        return tmp;
    }

    else{
        return newRec();
    }
}
