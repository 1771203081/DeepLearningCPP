//
//  CU.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//


#include <new>
#include "illegalParameterValue.hpp"
#include "CU.hpp"



CU::CU(signType theSign,unsigned long theDollars,unsigned int theCents)
{
    //创建一个Currency 类对象
    setValue(theSign, theDollars, theCents);
}

void CU::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
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

void CU::setValue(double theAmount)
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

signType CU::getSign()const
{
    if (amount<0) {
        return minusv;
    }else{
        return plusv;
    }
}

unsigned long CU::getDollars()const
{
    if (amount<10) {
        return (-amount)/100;
    }else
    {
        return amount/100;
    }
    
}

unsigned int CU::getCents()const
{
    if (amount<0) {
        return -amount-getDollars()*100;
    }else
    {
        return amount-getDollars()*100;
    }
}

CU CU::add(const CU &x)const
{
   
    CU y;
    y.amount = amount+x.amount;
    return y;
    
}

CU& CU::increment(const CU &x)
{
    //增加x
    /*
     this 指向调用对象
     
     */
    //调用对象 加了x后 对调用对象重新赋值
    //并返回调用对象的引用
    amount += x.amount;
    
    return *this;
    
}

void CU::output()const
{
    long theAmount = amount;
    
    if (theAmount<0) {
        cout<<"-";
        theAmount = - theAmount;
    }
    long dollars = theAmount/100;//美元
    
    cout<<"$"<<dollars<<".";
    
    int cents = theAmount-dollars*100;//美分
    if (cents<10) {
        cout<<"0";
    }
    cout<<cents;
}


CU::~CU()
{
    
}

