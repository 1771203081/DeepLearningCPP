//
//  C2U.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/16.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef C2U_hpp
#define C2U_hpp
#include "ENUMTYPE.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
/*
 对现有类实现操作符重载
 
 实现+ +=操作符重载 并定义为成员函数
 
 实现<<流插入操作符 但未定义为成员函数
 
 但是添加成员函数output 成员函数 辅助对<<流插入操作符的使用
 
 因为 非成员函数不能访问类实例对象的私有成员
 */
class C2U {
    
    
public:
    //构造函数
    C2U(signType theSign = plusv,unsigned long theDollars = 0,unsigned int theCents=0);
    //析构函数
    ~C2U();
    
    void setValue(signType,unsigned long,unsigned int);
    
    void setValue(double);
    
    signType getSign() const;
    
    
    unsigned long getDollars() const;
    
    unsigned int getCents() const;
    
    C2U operator+(const C2U&) const;
    
    C2U& operator+=(const C2U&);
    
    void output(ostream&) const;
    
private:
    long amount;
    
};













#endif /* C2U_hpp */
