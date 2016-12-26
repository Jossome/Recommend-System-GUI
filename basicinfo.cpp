/*****************************************************************
 *
 * Copyright:   C++ Group WXYZ
 * Authors:     Shaojie Wang, Zhaohua Yang, Rui Xiong, Xin Zhang
 * Date:        2016-12-22
 * Description: Book, User, Rating Classes and Other Functions.
 *
******************************************************************/

#include "basicinfo.h"

void User::showInfo(){
    std::cout << "The User's ID is "<< id <<", age is "<< age << ", city is "<<city<<", state is "<<state<< ", country is "<<country<<std::endl;
    std::cout << "********************************"<<std::endl;
}

void User::setNewInfo(std::string newid, int newage, std::string newcity, std::string newstate, std::string newcountry){
    id = newid;
    city = newcity;
    state = newstate;
    country = newcountry;
    age = newage;
}

void User::setInfo(int newage, std::string newcity, std::string newstate, std::string newcountry){
    city = newcity;
    state = newstate;
    country = newcountry;
    age = newage;
}

void Rating::setNewInfo(std::string newid,std::string newisbn,double newrate){
    id = newid;
    isbn = newisbn;
    bookrating = newrate;
}

int computeDistance(User user1, User user2) {
    int age_dif = abs(user1.age - user2.age) / 5;
    int country_dif = (user1.country == user2.country && user1.country != "n/a") ? 0 : 1;
    int state_dif = (user1.state == user2.state && user1.state != "n/a") ? 0 : 1;
    int county_dif = (user1.city == user2.city && user1.city != "n/a") ? 0 : 1;
    int dis = age_dif * 6 + country_dif * 3 + state_dif * 2 + county_dif * 1;
    return dis;
}

std::string IDCheck(std::string chid, MyMultimap<std::string,int> indextable){
    int flag =1;
    int k = 0;
    std::string testid;
    testid = chid;
    while(flag){
        MyMultimap<std::string,int>::iter p = indextable.find(testid);
        if (p!=indextable.end()){
            flag = 0;
        }
        else {
            std::cout << "YOUR ID DOESN'T EXIST, TRY TO INPUT AGAIN:";
            std::cin >> testid;
            k++;
            if(k>=3){
                std::cout << "DON'T REMEMBER? EXIST INPUT 0, CONTINUE INPUT 1:";
                std::cin >> flag;
                testid="error";
            }
        }
    }
    return testid;
}

std::string ISBNCheck(std::string chisbn, MyMultimap<std::string,int> indextable){
    int flag =1;
    int k=0;
    std::string testisbn;
    testisbn = chisbn;
    while(flag){
            MyMultimap<std::string,int>::iter p = indextable.find(testisbn);
            if (p!=indextable.end()){
                flag = 0;
            }
            else {
                std::cout << "THIS ISBN DOESN'T EXIST, TRY TO INPUT AGAIN:";
                std::cin >> testisbn;
                k++;
                if(k>=3){
                    std::cout << "DON'T REMEMBER? EXIST INPUT 0, CONTINUE INPUT 1:";
                    std::cin >> flag;
                    testisbn="error";
                }
            }
        }
    return testisbn;
}

std::string CommaSplit(std::string str){
    std::string testcmd,left,middle,right;
    testcmd = str;
    int pos,pos2,pos3;
    pos = testcmd.find_first_of('\"');
    if(pos!=std::string::npos)
    {
        pos2 = testcmd.find_first_of('\"',pos+1);
         left = testcmd.substr(0,pos);
         middle = testcmd.substr(pos+1,pos2-pos-1);
         right = testcmd.substr(pos2+1);
        pos3 = middle.find_first_of(',');
        while(pos3!=std::string::npos)
        {
            middle[pos3] = '*';
            pos3 = middle.find_first_of(',',pos3+1);
        }
        testcmd = left+middle+right;
    }
    return testcmd;
}

std::string StarToComma(std::string str){
    std::string testcmd;
    testcmd = str;
    int pos;
    pos = testcmd.find_first_of('*');
    if(pos!=std::string::npos)
    {
        while(pos!=std::string::npos)
        {
            testcmd[pos] = ',';
            pos = testcmd.find_first_of('*',pos+1);
        }
    }
    return testcmd;
}

int RateBook(std::string str,MyMultimap<std::string,int> indextable){
    int flag=1;
    std::string testisbn;
    int k=0;
    int rate;
    testisbn = str;
    while(flag){
        MyMultimap<std::string,int>::iter p = indextable.find(testisbn);
        if (p!=indextable.end()){
            std::cout <<"INPUT THE RATE(INTEGER FROM 1-10): ";
            std::cin >> rate;
            flag=0;
        }
        else {
            std::cout << "THE ISBN DOESN'T EXIST,TRY TO INPUT AGAIN:";
            std::cin >> testisbn;
            k++;
            if(k>=3){
                std::cout << "DON'T REMEMBER? EXIST INPUT 0, CONTINUE INPUT 1:";
                std::cin >> flag;
                rate = -1;
            }
        }
    }
    return rate;
}

double get_norm(double *x, int n){
    double r=0;
    for(int i=0;i<n;i++)
        r+=x[i]*x[i];
    return sqrt(r);
}

double normalize(double *x, int n){
    double r=get_norm(x,n);
    if(r<eps)
        return 0;
    for(int i=0;i<n;i++)
        x[i]/=r;
    return r;
}

double product(double*a, double *b,int n){
    double r=0;
    for(int i=0;i<n;i++)
        r+=a[i]*b[i];
    return r;
}

void orth(double *a, double *b, int n){
    double r=product(a,b,n);
    for(int i=0;i<n;i++)
        b[i]-=r*a[i];

}

bool svd(std::vector<std::vector<double> > A, int K, std::vector<std::vector<double> > &U, std::vector<double> &S, std::vector<std::vector<double> > &V){
    int M=A.size();
    int N=A[0].size();
    U.clear();
    V.clear();
    S.clear();
    S.resize(K,0);
    U.resize(K);
    for(int i=0;i<K;i++)
        U[i].resize(M,0);
    V.resize(K);
    for(int i=0;i<K;i++)
        V[i].resize(N,0);


    srand(time(0));
    double *left_vector=new double[M];
    double *next_left_vector=new double[M];
    double *right_vector=new double[N];
    double *next_right_vector=new double[N];
    while(1){
        for(int i=0;i<M;i++)
            left_vector[i]= (float)rand() / RAND_MAX;
        if(normalize(left_vector, M)>eps)
            break;
    }
    for(int col=0;col<K;col++){
        double diff=1;
        double r=-1;
        for(int iter=0;diff>=eps && iter<MAX_ITER;iter++){
            memset(next_left_vector,0,sizeof(double)*M);
            memset(next_right_vector,0,sizeof(double)*N);
            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                    next_right_vector[j]+=left_vector[i]*A[i][j];

            r=normalize(next_right_vector,N);
            if(r<eps) break;
            for(int i=0;i<col;i++)
                orth(&V[i][0],next_right_vector,N);
            normalize(next_right_vector,N);

            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                    next_left_vector[i]+=next_right_vector[j]*A[i][j];
            r=normalize(next_left_vector,M);
            if(r<eps) break;
            for(int i=0;i<col;i++)
                orth(&U[i][0],next_left_vector,M);
            normalize(next_left_vector,M);
            diff=0;
            for(int i=0;i<M;i++){
                double d=next_left_vector[i]-left_vector[i];
                diff+=d*d;
            }

            memcpy(left_vector,next_left_vector,sizeof(double)*M);
            memcpy(right_vector,next_right_vector,sizeof(double)*N);
        }
        if(r>=eps){
            S[col]=r;
            memcpy((char *)&U[col][0],left_vector,sizeof(double)*M);
            memcpy((char *)&V[col][0],right_vector,sizeof(double)*N);
        }else
            break;
    }
    delete [] next_left_vector;
    delete [] next_right_vector;
    delete [] left_vector;
    delete [] right_vector;

    return true;
}

void print(std::vector<std::vector<double> > &A){
    for(int i=0;i<A.size();i++){
        for(int j=0;j<A[i].size();j++){
            std::cout<<std::setprecision(3)<<A[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
}

float average(std::vector<std::vector<double> > A,int u,int type){
    if (type==1){
        int count=0;
        float sum=0;
        int flag=0;
        for(int j=0;j<A[u].size();j++){
            {
                if(A[u][j]!=0){
                    sum=sum+A[u][j];
                    count++;
                    flag=1;
                }
            }
        }
        if (flag==1)return (float)sum/(float)count;
        else return 0;
    }
    else{
        int count=0;
        float sum=0;
        int flag=0;
        for(int j=0;j<A.size();j++){
            {
                if(A[j][u]!=0){
                    flag=1;
                    sum=sum+A[j][u];
                    count++;}
            }
        }
        if (flag==1)return (float)sum/(float)count;
        else return 0;

    }
}

bool pearsoncorr(std::vector<std::vector<double> > A,std::vector<std::vector<double> > &B,int K){
    int N=A[0].size();
    float fenzi,fenmu1,fenmu2;
    float aveRi,aveRj;
    B.clear();
    B.resize(N);
    for(int i=0;i<N;i++) B[i].resize(N,0);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            aveRi=average(A,i,2);
            aveRj=average(A,j,2);
            fenzi=0;fenmu1=0;fenmu2=0;
            for(int k=0;k<K;k++){
                fenzi=fenzi+(A[k][i]-aveRi)*(A[k][j]-aveRj);
                fenmu1=fenmu1+(A[k][i]-aveRi)*(A[k][i]-aveRi);
                fenmu2=fenmu2+(A[k][j]-aveRj)*(A[k][j]-aveRj);
            }
            if(fenmu1*fenmu2!=0){B[i][j]=fenzi/(sqrt(fenmu1*fenmu2));}
            else{B[i][j]=0;}

        }
    }


    return true;

}

bool predictRui(std::vector<double>  &result, std::vector<std::vector<double> > A, std::vector<std::vector<double> > &CorrU, std::vector<std::vector<double> > &CorrV,int userid, int num_of_rec, float yita, float theta, float alpha, float beta)
{
    float UserCF, ItemCF,ave_u,ave_i,ave_a,ave_b,fenzi=0,fenmu=0;
    bool flag=0;
    int bookid=0, count=0;
    float rec[3][500], rec2[2][10];

    result.clear();
    result.resize(num_of_rec);


    for(bookid=0;bookid<A[userid].size();bookid++)
    {
        if(A[userid][bookid]==0)
        {
            //calculate recommendation index based on user similarity
            fenzi=0;fenmu=0;flag=0;
            for(int a=0;a<CorrU[userid].size();a++){
                if(CorrU[userid][a]>yita && a!=userid && A[a][bookid]){
                    flag=1;
                    ave_a=average(A,a,1);
                    fenzi=fenzi+CorrU[userid][a]*(A[a][bookid]-ave_a);
                    fenmu=fenmu+CorrU[userid][a];
                }
            }
            if(flag==1){
                ave_u=average(A,userid,1);
                UserCF=(ave_u+fenzi/fenmu);}
            else{ UserCF=0;}

            //calculate recommendation index based on book similarity
            fenzi=0;fenmu=0;flag=0;
            for(int b=0;b<CorrV[bookid].size();b++){
                if(CorrV[bookid][b]>theta && b!=bookid && A[userid][b]!=0){
                    flag=1;
                    ave_b=average(A,b,2);
                    fenzi=fenzi+CorrV[bookid][b]*(A[userid][b]-ave_b);
                    fenmu=fenmu+CorrV[bookid][b];
                }
            }
            if(flag==1){
                ave_i=average(A,bookid,2);
                ItemCF=(ave_i+fenzi/fenmu);}
            else{ItemCF=0;}
            rec[0][count]=bookid;
            rec[1][count]=alpha*UserCF+beta*ItemCF;
            rec[2][count]=0;
            count++;
        }
    }


    // select top 3 (num_of_rec) books
    //initiate matrix result
    bool mark2=0;
    for(int j=0;j<num_of_rec;j++)
    {
        rec2[0][j]=0;
        rec2[1][j]=0;
        int mark=0;
        for(int i= 0; i<count; i++){
            if(rec[1][i]>rec2[1][j] && rec[2][i] ==0){
                rec2[1][j]=rec[1][i];
                rec2[0][j]=rec[0][i];
                mark=i;
                mark2=1;
            }
        }
        rec[2][mark]=j+1;
    }

    for(int j=0;j<num_of_rec;j++)
    {
        result[j]=rec2[0][j];
    }
    if(mark2)    return true;
    else return false;

}

int determink(std::vector<double> &S, float percentage)
{
    int K=S.size(),sum1=0,sum2=0,threshold;
    for(int j=0;j<S.size();j++)
    {
        sum1=sum1+S[j];
    }
    threshold=sum1*percentage;
    for(int j=0;j<S.size();j++)
    {
        sum2=sum2+S[j];
        if(sum2>threshold){ K=j+1; break;}
    }
    return K;
}

bool recommend4old(std::vector<double>  &result, std::vector<std::vector<double> > A,int idnumber,int num_of_rec) {
    int K=5;
    double yita=0.7,theta=0.7,alpha=0.5,beta=1-alpha; //设置推荐参数
    std::vector<std::vector<double> > U;
    std::vector<double> S;
    std::vector<std::vector<double> > V;
    svd(A,K,U,S,V);
    std::vector<std::vector<double> > CorrU;
    pearsoncorr(U,CorrU,K);
    std::vector<std::vector<double> > CorrV;
    pearsoncorr(V,CorrV,K);
    bool warm;
    warm = predictRui(result, A,CorrU,CorrV,idnumber, num_of_rec,  yita,  theta,  alpha,  beta);

    return warm;
}
