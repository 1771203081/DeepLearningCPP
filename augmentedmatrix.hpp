//
//  augmentedmatrix.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef augmentedmatrix_hpp
#define augmentedmatrix_hpp
#include <math.h>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <stdio.h>

/*
 augmented 增强的
 
 增强的矩阵
 
 AR Augmented Reality 虚拟现实
 */


//分数的定义-- 提高计算的精度

class Fraction {
    
    
public:
    double numerator;//分子
    double denominator;//分母
    
    Fraction()
    {
        numerator = 1.0;
        denominator = 1.0;
    }
    
    Fraction(double numerator,double denominator)
    {
        this->numerator = numerator;
        this->denominator = denominator;
    }
    
    Fraction(double n)
    {
        numerator = n;
        denominator = 1.0;
    }
    //=
    inline void operator=(double numerator)
    {
        this->numerator = numerator;
        this->denominator = 1.0;
    }
    //=
    inline void operator=(Fraction&a)
    {
        this->numerator = a.numerator;
        this->denominator = a.denominator;
    }
    /*
     友元关系不具对称性。即 A 是 B 的友元，但 B 不一定是 A 的友元。 友元关系不具传递性。即 B 是 A 的友元，C 是 B 的友元，但是 C 不一定是 A 的友元。
     这里注意定义一个友元函数 需要考虑：
     友元函数的使用
     因为友元函数没有this指针，则参数要有三种情况：
     要访问非static成员时，需要对象做参数；
     要访问static成员或全局变量时，则不需要对象做参数；
     如果做参数的对象是全局对象，则不需要对象做参数.
     可以直接调用友元函数，不需要通过对象或指针
     */
    //-
    friend inline Fraction operator-(Fraction&a,Fraction&b)
    {
        double n = a.numerator*b.denominator-a.denominator*b.numerator;
        double d = a.denominator*b.denominator;
        
        return Fraction(n,d);
    }
    //+
    friend inline Fraction operator+(Fraction&a,Fraction&b)
    {
        Fraction ret;
        ret.numerator = a.numerator*b.denominator+a.denominator*b.numerator;
        ret.denominator = a.denominator*b.denominator;
        
        return ret;
    }
    //-=
    
    inline void operator -=(Fraction&a)
    {
        numerator= a.denominator*numerator-a.numerator*denominator;
        denominator = a.denominator*denominator;
        
        
    }
    //*
    friend inline Fraction operator*(Fraction&a,Fraction&b)
    {
        double n = a.numerator*b.numerator;
        double d = a.denominator*b.denominator;
        
        return Fraction(n,d);
    }
    //x=
    
    inline void operator *=(Fraction &a)
    {
        numerator *= a.numerator;
        denominator *= a.denominator;
    }
    
    // /
    friend inline Fraction operator/(Fraction&a,Fraction &b)
    {
        Fraction ret;
        ret.numerator = a.numerator*b.denominator;
        ret.denominator = a.denominator*b.numerator;
        return  ret;
    }
    
    // ==
    
    inline bool operator==(Fraction &a)
    {
        /*
         这里判断分数相同 不是判断分子 分母 数字相同
         而是 十字交叉的积 相同
         
         因为 存在约分
         比如 1/2 == 2/4
         */
        return this->numerator*a.denominator == this->denominator*a.numerator;
    }
    
    // ==
    
    inline bool operator==(double a)
    {
        return this->numerator == this->denominator*a;
    }
};


#if !defined(fraction)
typedef long double fraction;
#endif

/*
 class AugmentedMatrix
 增广矩阵 利用高斯消元的方法求解一次方程组
 
 计算线性拟合的结果
 
 矩阵的定义-矩阵的坐标如图所示
 //-|------------->x
 // |
 // |
 // |
 // |
 // \/
 // y
 矩阵数据 和 增光列 如下所示
 // |--------matrix-------|--augment--|----result----|
 // |--2a + 3b + 11c + 5d =  2 -------|--1 0 0 0|-2--|
 // |--1a +  b +  5c + 2d =  1 -------|--0 1 0 0| 0--|
 // |--2a +  b +  3c + 2d = -3 -------|--0 0 1 0| 1--|
 // |--1a +  b +  3c + 3d = -3 -------|--0 0 0 1|-1--|
 
 
 */


class AugmentedMatrix {

    
    
public:
    AugmentedMatrix();//构造函数1
    ~AugmentedMatrix();//析构函数
    
    //矩阵导入数据
    bool setMatrixData(fraction*values,int width,int height);
    //设置增广列数据
    bool setAugmentData(fraction*values,int height);
    
    inline fraction getResult(int y){
        return augment[y];
    }
    // 处理数据
    bool process();
    //打印结果
    void print();
    
    
private:
    //矩阵数据-- 定义称分数形式提高精度（最多32组）
    fraction* matrix[32];
    //增加的一列
    
    fraction augment[32];
    //矩阵的宽高
    int width,height;
    //释放内存
    void releaseData();
    //高斯消元法 求解多元方程组的值
    bool augmentedMatrixTrans();
    //排序
    bool sortLines(int p);
    //消元
    void elimination(int p);
    //交换两行
    void swap(fraction*a,fraction*b);
    //消元
    void elimination_inv(int x);
    //华为单位矩阵
    void identityMatrix();
    
};







#endif /* augmentedmatrix_hpp */
