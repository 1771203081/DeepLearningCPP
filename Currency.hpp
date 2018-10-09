//
//  Currency.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Currency_hpp
#define Currency_hpp
#include "ENUMTYPE.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;






class Currency {
    
    
public:
    //构造函数
    Currency(signType theSign= plusv,unsigned long theDollars = 0,unsigned int theCents = 0);
    
    //析构函数
    ~Currency();
    
    void setValue(signType,unsigned long,unsigned int);
    
    void setValue(double);
    
     //常量函数 因为这个函数不改变调用对象的值
    signType getSign() const;
     //常量函数 因为这个函数不改变调用对象的值
    unsigned long getDollars() const ;
     //常量函数 因为这个函数不改变调用对象的值
    unsigned int getCents() const;
    //常量函数 因为这个函数不改变调用对象的值
    /*
     注意这里 返回的是一个对象
     
     返回对象的值 就是 将返回的对象复制到返回的环境中
     因此需要有对应的复制构造函数
     
     这里没有实现复制构造函数
     
     C++将使用缺省复制构造函数 仅仅复制数据成员
     
     */
    Currency add(const Currency&) const;
    //非常量函数 因为这个函数会改变调用对象的值
    Currency& increment(const Currency&);
    
    void output() const;

private:
    
    signType sign;//对象的符号
    
    unsigned long dollars;//美元的数量
    unsigned int cents;//美分的数量
    
  
    
};














#endif /* Currency_hpp */
