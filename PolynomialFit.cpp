//
//  PolynomialFit.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "PolynomialFit.hpp"
#include <math.h>
#include <memory.h>
#include <iostream>

/*
这里有一点 需要考虑 需不需要为当前类定义拷贝构造函数
 
注意:必须定义拷贝构造函数的情况：
只包含类类型成员或内置类型（但不是指针类型）成员的类，无须显式地定义拷贝构造函数也可以拷贝；有的类有一个数据成员是指针，或者是有成员表示在构造函数中分配的其他资源，这两种情况下都必须定义拷贝构造函数。
 
什么情况使用拷贝构造函数：
 类的对象需要拷贝时，拷贝构造函数将会被调用。以下情况都会调用拷贝构造函数：
 （1）一个对象以值传递的方式传入函数体
 （2）一个对象以值传递的方式从函数返回
 （3）一个对象需要通过另外一个对象进行初始化。
 */

//构造函数1
PolynomialFit::PolynomialFit()
{
    init();
}

//析构函数
PolynomialFit::~PolynomialFit()
{
    releaseSamples();
    releaseMatrix();
}
/*
 PolynomialFit::setAttribute 设置多项式的属性
 degree 设置多项式的阶数 阶数不能大于32
 intercedeEnable 设置是否使能截距
 intercede 多项式曲线的截距
 */
void PolynomialFit::setAttribute(int degree,bool intercedeEnable ,double intercede )
{
    
    this->isIntercedeEnable = intercedeEnable;
    
    if (this->isIntercedeEnable) {
        this->multiterm = degree;
        this->intercede = intercede;
    }else
    {
        this->multiterm = degree+1;
        this->intercede = 0.0;
    }
    
    this->degree = degree;
    
}

//初始化
void PolynomialFit::init()
{
    multiterm = count = degree = 0;
    sx = sy = weight = NULL;
    
    intercede = 0.0;
    isIntercedeEnable = false;
    //系数矩阵和 结果向量
    matrix = rvector = results = NULL;
}
/*PolynomialFit::setSample
 设置需要拟合曲线的样本 权重等
 
 x 样本x轴
 y 样本y轴
 count 样本数量
 endbleWeight 是否使能权重
 w 样本的权重
 返回 样本是否可以拟合
 */
bool PolynomialFit::setSample(double *x, double *y, int count, bool enableWeight, double *w)
{
    //释放样本内存
    releaseSamples();
    this->count = count;
    this->sx = new fraction[count];
    this->sy = new fraction[count];
    this->weight = new  fraction[count];
    
    
    for (int i = 0; i<count; i++) {
        this->sx[i] = x[i];
        this->sy[i] = y[i];
        if (enableWeight) {
            this->weight[i] = w[i];
        }else
        {
            this->weight[i] = 1.0;
        }
        
        
    }
    
    return  true;
    
}

//获取计算的结果
float PolynomialFit::getResult(int y)
{
    return (float)results[y];
}

//数据处理
bool PolynomialFit::process()
{
    //利用最小二乘法生成一次方程组

    if (!leastQuare()) {
        return false;
    }
    
    //通过高斯消元法解方程组
    
    AugmentedMatrix am;
    am.setMatrixData(matrix, multiterm, multiterm);
    am.setAugmentData(rvector, multiterm);
    
    if (!am.process()) {
        return false;
    }
    //解出的结果就是多项式的系数
    for (int i =0; i<multiterm; i++) {
        results[i] = am.getResult(i);
    }
    return true;
}
//打印结果
void PolynomialFit::print()
{
    int y = 0;
    std::cout<<"\n Polynomial Fit:"<<std::endl;
    for (y = 0; y<multiterm; y++) {
        for (int x =0; x<multiterm; x++) {
            std::cout<<(float)matrix[y*multiterm+x]<<"\t";
            
        }
        std::cout<<(float)rvector[y]<<std::endl;
    }
    std::cout<<"\nresults:"<<std::endl;
    
    for (y=0; y<multiterm; y++) {
        std::cout<<(float)getResult(y)<<"\t";
    }
    std::cout<<std::endl;
}

//释放内存
void PolynomialFit::releaseSamples()
{
    if (sx) {
        delete [] sx;
        sx = NULL;
    }
    if (sy) {
        delete [] sy;
        sy = NULL;
    }
    if (weight) {
        delete [] weight;
        weight = NULL;
    }
    //样本数量
    count = 0;
}
//释放矩阵内存

void PolynomialFit::releaseMatrix()
{
    if (matrix) {
        delete [] matrix;
        matrix = NULL;
    }
    
    if (rvector) {
        delete []  rvector;
        rvector = NULL;
    }
    
    if (results) {
        delete [] results;
        results = NULL;
    }
}
//利用最小二乘法 将样本转换成求解的方程组

bool PolynomialFit::leastQuare()
{
    int x = 0,y = 0;
    
    if (multiterm>count||count == 0|| multiterm == 0) {
        return false;
    }
    releaseMatrix();
    
    matrix = new fraction(multiterm*multiterm);
    rvector = new fraction(multiterm);
    results = new fraction(multiterm);
    //对角矩阵 计算各个行列的值
    for (int i =0; i<2*multiterm-1; i++) {
        if (i<multiterm) {
            x = i;
            y = 0;
        }else
        {
            x = multiterm - 1;
            y = i - x;
        }
        
        fraction r = calcMatrixUnit(x, y);
        
        for (int yi =0; yi<=i; yi++) {
            int xi = i - yi;
            if (yi<multiterm&&xi<multiterm) {
                matrix[yi*multiterm+xi] = r;
            }
        }
    }
    //计算增广列的值
    for (y = 0; y< multiterm; y++) {
        fillVectorUnit(y);
    }
    return true;
}
//计算矩阵某项的累计值

fraction PolynomialFit::calcMatrixUnit(int x, int y)
{
    fraction sum = 0.0;
    
    double n = 2*degree - x - y;
    
    for (int i = 0; i<count; i++) {
        sum += pow((double)sx[i], n) * weight[i];
    }
    return  sum;
}

//计算向量某项的累计值

void PolynomialFit::fillVectorUnit(int y)
{
    rvector[y] = 0.0;
    
    double n = degree - y;
    
    for (int i = 0; i<count; i++) {
        rvector[y] = (sy[i]-intercede)* pow((double)sx[i],n)*weight[i];
        
    }
    
}

