/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Book, User, Rating Classes and Other Functions.
 *
******************************************************************/

#ifndef BASICINFO_H
#define BASICINFO_H

#pragma warning(disable: 4267)
#pragma warning(disable: 4244)
#pragma warning(disable: 4819)

#include <string>
#include <map>
#include <iterator>
#include <climits>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <ctime>

#define MAX_NUMBER_USER 600
#define MAX_NUMBER_BOOK 500
#define MAX_NUMBER_RATING 4000
#define MAX_ITER 10000
#define eps 0.0000001

template <class Type>
Type stringToNum(std::string& str)
{
    std::istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

template<typename S, typename U>
class MyMultimap{
public:

    typedef typename std::multimap<S, U>::iterator iter;
    std::multimap<S,U> myMap;  //basically what we do is rewritting the multimap class

    void insert(std::pair<S, U> p){ myMap.insert(p); }
    iter find(S s){  return myMap.find(s); }
    iter begin(){ return myMap.begin(); }
    iter end(){ return myMap.end(); }  //all these are iterators, need to overload it because of its a new class !=multimap in STL
    void Set(S s, U u){
        iter end = myMap.equal_range(s).second;
        iter start = myMap.equal_range(s).first;
        while (start != end){
            start->second = u;
            start++;
        }
    }

    void clear() { myMap.clear(); }
};

class User
{
public:
    std::string id;
    std::string city;
    std::string state;
    std::string country;
    int age;
    // 	int ratetobook[]; //ROW OF RATING MATRIX
    void showInfo();
    void setNewInfo(std::string newid, int newage, std::string newcity, std::string newstate, std::string newcountry);
    void setInfo(int newage, std::string newcity, std::string newstate, std::string newcountry);
};

class Book
{
public:
    std::string isbn;
    std::string title;
    std::string author;
    std::string urls;
    std::string urlm;
    std::string urll;
    std::string publisher;
    int pubyear;
    double averagerate;
    int raternumber;
    //		double ratebyuser[]; //COLUMN OF RATING MATRIX
    void setNewInfo(std::string newisbn, int newtitle, std::string newauthor, int newpubyear, std::string newpublisher, std::string newurls, std::string newurlm, std::string newurll, double newaveragerate=0, int newraternumber=0){
        isbn = newisbn;
        title = newtitle;
        author = newauthor;
        pubyear = newpubyear;
        publisher = newpublisher;
        urls = newurls;
        urlm = newurlm;
        urll = newurll;
        averagerate = newaveragerate;
        raternumber = newraternumber;
    }
    void setNewInfo(int newtitle, std::string newauthor, int newpubyear, std::string newpublisher, std::string newurls, std::string newurlm, std::string newurll, double newaveragerate=0, int newraternumber=0){
        title = newtitle;
        author = newauthor;
        pubyear = newpubyear;
        publisher = newpublisher;
        urls = newurls;
        urlm = newurlm;
        urll = newurll;
        averagerate = newaveragerate;
        raternumber = newraternumber;
    }
};

class Rating
{
public:
    std::string id;
    std::string isbn;
    double bookrating;
    void setNewInfo(std::string newid,std::string newisbn,double newrate);
};

int computeDistance(User user1, User user2);
std::string IDCheck(std::string chid, MyMultimap<std::string,int> indextable);
std::string ISBNCheck(std::string chisbn, MyMultimap<std::string,int> indextable);
std::string CommaSplit(std::string str);
std::string StarToComma(std::string str);
int RateBook(std::string str,MyMultimap<std::string,int> indextable);
double get_norm(double *x, int n);
double normalize(double *x, int n);
double product(double*a, double *b,int n);
void orth(double *a, double *b, int n);
bool svd(std::vector<std::vector<double> > A, int K, std::vector<std::vector<double> > &U, std::vector<double> &S, std::vector<std::vector<double> > &V);
void print(std::vector<std::vector<double> > &A);
float average(std::vector<std::vector<double> > A,int u,int type);
bool pearsoncorr(std::vector<std::vector<double> > A,std::vector<std::vector<double> > &B,int K);
bool predictRui(std::vector<double>  &result, std::vector<std::vector<double> > A, std::vector<std::vector<double> > &CorrU, std::vector<std::vector<double> > &CorrV,int userid, int num_of_rec, float yita, float theta, float alpha, float beta);
int determink(std::vector<double> &S, float percentage);
bool recommend4old(std::vector<double> &result, std::vector<std::vector<double> > A,int idnumber,int num_of_rec);

#endif // BASICINFO_H
