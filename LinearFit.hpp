//
//  LinearFit.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef LinearFit_hpp
#define LinearFit_hpp
#include "PolynomialFit.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>



/*
 GoodNess计算拟合优度R
 */
class GoodNess {
    
    //double goodness;//拟合优度
    
public:
    GoodNess():goodness(0.0){;}
    ~GoodNess(){;}
    
    void calcGoodNess(double *x,double * y,int count);
    double getGoodNess();

protected:
    virtual double func(double x) = 0;
    double goodness;//拟合优度
};
/*
 Polynomial --多项式的拟合 y=(Pn*x^n)+(Pn-1*x^n-1)+...+P1*x+P0
 setAttribute: 设置函数的阶数 曲线的截距
 
 setSample: 可以设置样本 样本数量 使能权重 每个样本的权重
 process: 阶数和样本设置后计算系数 和 拟合优度（必须先设置好多项式的阶数 和 样本）
 */

//多项式拟合
class Polynomial:public PolynomialFit,public GoodNess {
    
    
public:
    Polynomial();
    ~Polynomial();
    //设置样本
    bool setSample(double*x,double*y,int count,bool enableWeight, double* w);
    //处理 添加拟合优度的计算
    bool process();
protected:
    //原始样本内容和数量
    double* osx,*osy;
    
    int ocount;
    
    void copy(double *x,double*y,int count);
    //方程
    double func(double x);
    
};

/*对数拟合 y=P2*ln(x)+P1
 * setSample: 可以设置样本、样本数量、使能权重、每个样本的权重
 * process: 阶数和样本设置后计算系数和拟合优度（必须先设置好样本）
 */

class Logarithm:public Polynomial {
    
    
public:
    Logarithm();
    
    //设置样本
    bool setSample(double*x,double*y,int count,bool enableWeight,double*w);
    
    double func(double x);
};

/*拟合 y=P2*exp(P1*x)
 * setSample: 可以设置样本、样本数量、使能权重、每个样本的权重
 * process: 阶数和样本设置后计算系数和拟合优度（必须先设置好样本）
 */
class Exponent:public Polynomial {
    
    
public:
    
    Exponent();
    
    //设置样本
    bool setSample(double*x,double*y,int count,bool enableWeight,double* w);
    
    double func(double x);
    //系数从左到右分别对应0、1、2...n
    float getResult(int y);
};

/*
 幂函数拟合 y=P2*x^(P1)
 
 */
class Power:public Polynomial {
    
    
public:
    Power();
    
    //设置样本
    bool setSample(double*x,double*y,int count,bool enableWeight,double * w);
    
    double func(double x);
    //系数从左到右分别对应0、1、2...n
    float getResult(int y);
};

#endif /* LinearFit_hpp */
