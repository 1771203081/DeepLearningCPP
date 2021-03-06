//
//  LinearFit.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "LinearFit.hpp"

/*
 计算拟合优度
 */

void GoodNess::calcGoodNess(double *x, double *y, int count)
{
    double sum0 = 0.0,dy = 0.0;
    //回归平方和
    double ESS = 0.0;
    //残差平方和
    double RSS = 0.0;
    //总体平方和
    double TSS = 0.0;
    
    int i = 0;
    
    for (i = 0; i<count; i++) {
        sum0 += y[i];
    }
    
    dy = sum0/count;
    
    for (i = 0; i<count; i++) {
        ESS += pow(func(x[i])-dy, 2);
        
        RSS += pow(y[i]-func(x[i]),2);
    }
    
    TSS = ESS + RSS ;
    if (TSS == 0.0) {
        goodness = 0.0;
    }else
    {
        goodness = ESS/TSS;
    }
    
}

double GoodNess::getGoodNess()
{
    return goodness;
}

/*多项式*/
//构造函数
/*
 这里继承自父类PolynomialFit GoodNess 多继承
 在初始化函数 构造函数执行时 要对多个成员变量进行初始化
 所以 这里在实现构造函数时 在函数名后
 添加了 在类初始化时 对应需要一起进行初始化的成员变量列表
 */
Polynomial::Polynomial():PolynomialFit(),GoodNess(),osx(NULL),osy(NULL),ocount(0)
{
    
}

//析构函数
Polynomial::~Polynomial()
{
    if (osx!=NULL) {
        delete [] osx;
    }
    if (osy!=NULL) {
        delete [] osy;
    }
}

//设置样本--x:x轴数据 y:y轴数据 w:w权重系数 count样本数量

bool Polynomial::setSample(double *x, double *y, int count, bool enableWeight, double *w)
{
    copy(x, y, count);
    return PolynomialFit::setSample(x, y, count, enableWeight, w);
}
//曲线的原型 - y=(Pn*x^n)+(Pn-1*x^n-1)+...+P1*x+P0

double Polynomial::func(double x)
{
    
    double result = 0;
    if (!isIntercedeEnable) {
        for (int i = 0; i<=degree; i++) {
            result += getResult(i)*pow(x, degree-i);
        }
    }else{
        for (int i = 0; i<degree; i++) {
            result += getResult(i)*pow(x, degree-i);
        }
        result += intercede;
    }
    
    return  result;
    
}
//处理 添加拟合优度的计算

bool Polynomial::process()
{
    bool ret = PolynomialFit::process();
    
    if (ret == false) {
        return false;
    }
    calcGoodNess(osx, osy, ocount);
    
    return true;
}

void Polynomial::copy(double *x, double *y, int count)
{
    ocount = count;
    
    osx = new double(count);
    osy = new double[count];
    
    for (int i = 0; i<count; i++) {
        osx[i] = x[i];
        osy[i] = y[i];
        
    }
}


/*
 对数
 
 */

Logarithm::Logarithm():Polynomial()
{
    
    setAttribute(1,false);
}


bool Logarithm::setSample(double *x, double *y, int count, bool enableWeight, double *w)
{
    //留取一份样本
    copy(x,y,count);
    
    //处理
    double *px = new double[count];
    for(int i(0) ; i<count ; i++){
        if(x[i] <= 0.0){
            delete [] px;
            return false;
        }
        
        px[i] = log(x[i]);
    }
    
    bool ret = PolynomialFit::setSample(px,y,count,enableWeight,w);
    delete [] px;
    return ret;
}

double Logarithm::func(double x)
{
    return getResult(0) * log(x) + getResult(1);
}


//////////////////////////////////////////////////////////////////////////////
/**
 * 指数 y = P2*exp(P1*x)
 */
Exponent::Exponent() :
Polynomial()
{
    setAttribute(1,false);
}

//设置样本
bool Exponent::setSample(double *x, double *y, int count, bool enableWeight, double *w)
{
    //留取一份样本
    copy(x,y,count);
    
    //处理
    double *py = new double[count];
    for(int i(0) ; i<count ; i++){
        if(y[i] <= 0.0){
            delete [] py;
            return false;
        }
        
        py[i] = log(y[i]);
    }
    
    bool ret = PolynomialFit::setSample(x,py,count,enableWeight,w);
    delete [] py;
    return ret;
}

//
double Exponent::func(double x)
{
    return getResult(0) * exp(x*getResult(1));
}

// 系数从左到右分别对应0、1、2...y
float Exponent::getResult(int y)
{
    if(y==0)
        return exp(PolynomialFit::getResult(1)) ;
    else
        return PolynomialFit::getResult(0);
}


//////////////////////////////////////////////////////////////////////////////
/**
 * 幂函数 y = P2*x^P1
 */
Power::Power() : Polynomial()
{
    setAttribute(1,false);
}

//设置样本
bool Power::setSample(double *x, double *y, int count, bool enableWeight, double *w)
{
    //留取一份样本
    copy(x,y,count);
    
    //处理
    double *px = new double[count];
    double *py = new double[count];
    for(int i(0) ; i<count ; i++){
        if(y[i] <= 0.0 || x[i] <= 0.0){
            delete [] px;
            delete [] py;
            return false;
        }
        
        px[i] = log(x[i]);
        py[i] = log(y[i]);
    }
    
    bool ret = PolynomialFit::setSample(px,py,count,enableWeight,w);
    delete [] px;
    delete [] py;
    return ret;
}

//
double Power::func(double x)
{
    return getResult(0) * pow(x ,(double)getResult(1));
}

// 系数从左到右分别对应0、1、2...y
float Power::getResult(int y)
{
    if(y==0)
        return exp(PolynomialFit::getResult(1)) ;
    else
        return PolynomialFit::getResult(0);
}

