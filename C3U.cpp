//
//  C3U.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/16.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "C3U.hpp"
/*
 这里对流插入操作符 也是重载 但是没有作为成员函数重载而已 但是即便修改也是作为 友元函数重载
 
 声明友元函数 并重载
 */





#include <new>
#include "illegalParameterValue.hpp"




C3U::C3U(signType theSign,unsigned long theDollars,unsigned int theCents)
{
    //创建一个Currency 类对象
    setValue(theSign, theDollars, theCents);
}

void C3U::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    //给调用对象的数据成员赋值
    if (theCents>99) {
        throw illegalParameterValue("Cents should be < 100");
    }
    
    amount = theDollars*100+theCents;
    
    if (theSign==minusv) {
        amount=-amount;
    }
    
    
    
}

void C3U::setValue(double theAmount)
{
    //给调用对象的数据成员赋值
    
    
    //提取整数部分
    /*
     
     数据类型 向下转型
     
     大内存空间 double 到 unsigned long
     
     float 到 int
     
     数组指针 首地址  可以 转为首元素指针 首元素地址
     
     子类 向父类转型
     
     */
    
    
    if (theAmount<0) {
        amount=(long)((theAmount-0.001)*100);
    }else
    {
        amount=(long)((theAmount-0.001)*100);
    }
    
    
    
}

signType C3U::getSign()const
{
    if (amount<0) {
        return minusv;
    }else{
        return plusv;
    }
}

unsigned long C3U::getDollars()const
{
    if (amount<0) {
        return (-amount)/100;
    }else
    {
        return amount/100;
    }
    
}

unsigned int C3U::getCents()const
{
    if (amount<0) {
        return -amount-getDollars()*100;
    }else
    {
        return amount-getDollars()*100;
    }
}

/*
 操作符重载
 */

C3U C3U::operator+(const C3U &x) const
{
    /*把参数对象x和调用对象*this相加*/
    C3U result;
    result.amount = amount + x.amount;
    return  result;
}

C3U& C3U::operator+=(const C3U &x)
{
    amount =amount + x.amount;
    
    return *this;
}
/*这里对流插入操作符 也是重载 但是没有作为成员函数重载而已 但是即便修改也是作为 友元函数重载*/
ostream& operator<<(ostream&out,const C3U&x)
{
    long theAmount = x.amount;
    
    if (theAmount<0) {
        out<<"-";
        theAmount = - theAmount;
    }
    long dollars = theAmount/100;//美元
    
    out<<"$"<<dollars<<".";
    
    int cents = theAmount-dollars*100;//美分
    if (cents<10) {
        out<<"0";
    }
    out<<cents;
    return out;
}




C3U::~C3U()
{
    
}


