//
//  BayesFenLei.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//

/*
 贝叶斯分类器 C++
 
 贝叶斯分类器原理
 
 随机变量 W(类别标识 W1 W2 W3 W4) X(特征向量)
 
 三种概率
 
 P(W1) = 表示在所有分类结果中出现第一类的概率是多少  显然我们认为界定分类后 概率也就固定了 是四分之一
 
 
 接下来就是概率论中的条件概率了
 p(W1|X)= 表示在已知特征向量X的条件下最后分类结果为第一类的概率是多少
 根据贝叶斯条件概率知识 我们知道
     p(W1|X)= P(W1,X)/P(X)
 
 以上是我们的目标 拿到特征向量 立马就能知道是哪一类数据的概率
 
 但是上面明显不能立马得到结果 很多概率不知道
 
 ------让上面不知道的 联合概率P(W1,X) P(X) 知道 就是我们要重点解决的问题--
 
 
 P(X|W_) = 表示在某一个确定类别情况下，特征向量为X（已知特征向量）的概率 （看成是某一类别情况下该样本属于某一个特征的概率---概率密度函数）
 
 这里由于W_此时为变量 对所有分类作出计算
 我们在这里称为类条件概率密度
 
 
在这里补充贝叶斯全概率公式计算
 P(X) =∑P(X|W1)P(W1)
 
 
 
 */





#include <cmath>
#include <cstdio>
#include "BayesFenLei.hpp"


const int MAXN = 1000;
const double pi = 3.1415926;
/*
 C++文件流
 https://www.cnblogs.com/gyq8962/p/9201820.html
 以下类型需要包含头文件 < fstream>
 
 ofstream 输出流：是从内存（控制台）读到硬盘;
 ifstream 输入流：是从硬盘读到内存（控制台）.
 fstream 文件流：是可对打开的文件进行读写操作.
 
 getline()的原型是istream& getline ( istream &is , string &str , char delim );
 
 其中 istream &is 表示一个输入流，譬如cin；string&str表示把从输入流读入的字符串存放在这个字符串中（可以自己随便命名，str什么的都可以）；char delim表示遇到这个字符停止读入，在不设置的情况下系统默认该字符为'\n'，也就是回车换行符（遇到回车停止读入）。
 
 */

ifstream cin1("female.txt");

ifstream cin2("male.txt");

ifstream cin3("test.txt");

// ofstream 输出流：是从内存（控制台）读到硬盘;
ofstream cout1("result.txt");


struct HUMAN
{
    double height;
    double weight;
    
};

HUMAN female[MAXN];
HUMAN male[MAXN];

int female_num;

int male_num;

double P_female;
double P_male;
struct NORMAL {
    double mu1;
    double mu2;
    double delta1;
    double delta2;
    double rho;
};

NORMAL female_normal;

NORMAL male_normal;


/*
 读入文件数据
 */

void In()
{
    male_num = 0;
    female_num = 0;
    
    /*
     需要男女两张身高体重表
     
     cin1 读取女性（两个维度）身高 体重 表
     统计 女性数目
     */
    while (cin1>>female[female_num+1].height>>female[female_num+1].weight) {
        female_num++;
    }
    /*
     cin2 读取男性（两个维度） 身高 体重 表
     统计 男性数目
     */
    while (cin2>>male[male_num+1].height>>male[male_num+1].weight) {
        male_num++;
    }
    
}

void Init()
{
    /*
     人为分类 总共两大类
     因此 各自概率为定值 都是二分之一
     */
    P_female = 0.5;
    P_male = 0.5;
}

/*
 读入样本数量个样本
 并求出该样本的二维正态分布
 */

void Normalization(struct HUMAN* human,int human_num,struct NORMAL&human_normal)
{
  
    double mu1,mu2,deltal1,deltal2,rho;
    
    mu1 = 0; mu2 = 0; deltal1 = 0; deltal2 = 0 ;
    
    rho = 0;
    
     /*计算两个维度各自的期望 平均值*/
    
    for (int i = 1; i<human_num; i++) {
        mu1 += human[i].height;
        mu2 += human[i].weight;
    }
    
    mu1 /= human_num;
    
    mu2 /= human_num;
    
    /*计算两个维度各自的方差 */
    
    for (int i=1; i<human_num; i++) {
        deltal1 += (human[i].height-mu1)*(human[i].height-mu1);
        
        deltal2 += (human[i].weight-mu2)*(human[i].weight-mu2);
    }
    
    deltal1 /= human_num;
    
    deltal2 /= human_num;
    
    /*计算两个维度各自的标准差 */
    
    deltal1 = sqrt(deltal1);
    
    deltal2 = sqrt(deltal2);
    /*某个随机变量的标准差的求法2 以上是先求方差再求标准差*/
    /*
     方法二
     方差 由 E(X²)-E²(X) 求得
     再开根号 求的标准差
     */
    
    /*计算两个维度的相关系数 rho 皮尔逊相关系数*/
    for (int i=1; i<human_num; i++) {
        rho += human[i].height*human[i].weight;
    }
    
    /*计算E(X*Y) 的期望*/
    rho /= human_num;
    /*将E(X*Y) 的期望 减去 E(X)*E(Y)两个期望的积*/
    rho -= mu1*mu2;
    /*以上两个实际上是 协方差 的计算方法 cov(X,Y)*/
    /*将协方差 除以 两个随机变量的 标准差之积*/
    rho /= (deltal1 * deltal2);
    
    /* 以上求得相关系数*/
    
    human_normal.mu1 = mu1;
    
    human_normal.mu2 = mu2;
    
    human_normal.delta1 = deltal1;
    
    human_normal.delta2 = deltal2;
    
    human_normal.rho = rho;
    
    cout<<mu1<<" "<< deltal1 <<" "<<mu2<<" "<< deltal2 <<" "<<rho<<endl;
    
}

/*
 在分布为normal的条件下特征为(x1,x2)的条件概率
 */

double P(struct NORMAL& normal,double x1,double x2)
{
    /*
     这里 使用标准正态分布 估计出
     P(height|male)=(1/√(2𝞹𝛅²))*exp((-(height-期望)²/(2𝛅²)))
   
     
     
     */
    double ans;
    
    double mu1 = normal.mu1;
    
    double mu2 = normal.mu2;
    
    double delta1 = normal.delta1;
    
    double delta2 = normal.delta2;
    
    double rho = normal.rho;
    
    rho = 0;
    
    /*
     以下根据已经获得的 两个维度的随机变量的 期望 标准差 相关系数
     
     进行概率估计
     
    但是这里需要注意的是这里是二维正态分布 考虑相关系数
     这里我们暂时忽略相关系数
     
     
     */
    /*
     (X,Y) 服从参数为 u1,u2,𝛅1,𝛅2,𝞺(相关系数) 的二维正态分布
     
     分布函数
     𝐅(X,Y)=(2𝞹𝛅1𝛅2√(1-𝞺²))exp〔-1/(2(1-𝞺²))[(X-u1)²/𝛅1²-2𝞺(X-U1)(Y-U2)/𝛅1𝛅2+(Y-U2)²/𝛅2² ]〕
     
     */
    /*
     sqrt 开平方
     */
    double d1 = (1/(2*pi*delta1*delta2)*sqrt(1-rho*rho));
    /*
     exp 以e为底的指数运算
     */
    double d2 = -1/(2*sqrt(1-rho*rho));
    
    double d3 = ((x1-mu1)*(x1-mu1))/(delta1*delta1);
    
    double d4 = ((x2-mu2)*(x2-mu2))/(delta2*delta2);
    
    double d5 = (2*rho*(x1-mu1)*(x2-mu2)/(delta1*delta2));
    
    double d6 = (d3 - d5 + d4);
    
    d6 = exp(d2*d6);
    
    
    
    ans = d1*d6;
    
    return ans;
    
}

/*
 归为normal的后验概率
 t为0表示female 1表示male
 */
double Posterior_probability1(double x1,double x2,bool t)
{
  
    double PW;
    struct NORMAL normal;
    
    double d1 = P(female_normal, x1, x2)*P_female;
    

    double d2 = P(male_normal, x1, x2)*P_male;
    
    double d3 = P(female_normal, x1, x2)*P_female+P(male_normal, x1, x2)*P_male;
    
    if (t==0) {
       
        return  d1/d3;
    }else
    {
        return  d2/d3;
        
    }
    
}

/*
 判断是那个类别 返回0表示female 1表示male
 */

bool Classify(double x1,double x2)
{
    if (Posterior_probability1(x1, x2, 0)>=Posterior_probability1(x1, x2, 1)) {
        return 0;
    }else
    {
        return 1;
    }
    
}


/*
 得到错误率并将错误率输出到result.txt中
 */
void Find_error_rate()
{
    
    double height,weight;
    
    char c;
    
    int right_num = 0;
    
    int wrong_num = 0;
    
    while (cin3>>height>>weight>>c) {
        if ((c=='f'||c=='F')&&Classify(height, weight)==0) {
            
           //分类为女性并且正确
            right_num++;
        }else if((c=='m'||c=='M')&&Classify(height, weight)==1)
        {
            //分类为男性并且正确
            right_num++;
        }else
        {
            wrong_num++;
        }
        
        cout1<<height<<" "<<weight<<" "<<Classify(height, weight)<<endl;
    }
    
    
    
    cout<<"error rate is "<<(double)wrong_num/(double)(wrong_num+right_num)<<endl;
    
}

//二维正态分前 先标准正态分布
void Normal()
{
    
Normalization(female,female_num,female_normal);
    
Normalization(male,male_num,male_normal);

}







