/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Recommendation Class.
 *
******************************************************************/

#ifndef RECOMMEND_H
#define RECOMMEND_H

#include "basicinfo.h"
#include "login.h"

class Recommend
{
public:
    Recommend();

    int usernumber;
    int booknumber;

    MyMultimap<std::string,int> userindextable; //a index table for user, to give row number in rating matrix
    MyMultimap<std::string,int> bookindextable; //a index table for book, to give column number in rating matrix
    User user[MAX_NUMBER_USER];
    Book book[MAX_NUMBER_BOOK];
    Rating rating[MAX_NUMBER_RATING];
    double **ratingmatrix;

    void loadData();
    std::vector<std::string> newRec();
    std::vector<std::string> oldRec(std::string);
};

#endif // RECOMMEND_H
