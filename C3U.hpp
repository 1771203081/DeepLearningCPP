//
//  C3U.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/16.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef C3U_hpp
#define C3U_hpp
#include "ENUMTYPE.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

class C3U {
    
    
public:
    //构造函数
    C3U(signType theSign = plusv,unsigned long theDollars = 0,unsigned int theCents=0);
    //析构函数
    ~C3U();
    
    void setValue(signType,unsigned long,unsigned int);
    
    void setValue(double);
    
    signType getSign() const;
    
    
    unsigned long getDollars() const;
    
    unsigned int getCents() const;
    
    C3U operator+(const C3U&) const;
    
    C3U& operator+=(const C3U&);
    
//    void output(ostream&) const;
    
    friend ostream& operator<<(ostream&,const C3U&);
    
private:
    long amount;
};





#endif /* C3U_hpp */
