//
//  Currency.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//


#include <new>
#include "illegalParameterValue.hpp"
#include "Currency.hpp"



Currency::Currency(signType theSign,unsigned long theDollars,unsigned int theCents)
{
        //创建一个Currency 类对象
    setValue(theSign, theDollars, theCents);
}

void Currency::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    //给调用对象的数据成员赋值
    if (theCents>99) {
        throw illegalParameterValue("Cents should be < 100");
    }
    
    sign = theSign;
    
    dollars = theDollars;
    
    cents = theCents;
    
    
    
}

void Currency::setValue(double theAmount)
{
    //给调用对象的数据成员赋值
    
    if (theAmount<0) {
        sign = minusv;
        theAmount = -theAmount;
    }else{
        sign = plusv;
    }
    //提取整数部分
    /*
     
     数据类型 向下转型
     
     大内存空间 double 到 unsigned long
     
     float 到 int
     
     数组指针 首地址  可以 转为首元素指针 首元素地址
     
     子类 向父类转型
     
     */

    dollars = (unsigned long) theAmount;
    
    cents = (unsigned int)((theAmount+0.001-dollars)*100);//提取两位小数
    
    
}

Currency Currency::add(const Currency &x)const
{
    //把x 和*this 相加
    
    long a1,a2,a3;
    
    Currency result;
    
    //把调用对象转化为符号整数
    
    a1 = dollars*100 + cents;
    
    if (sign == minusv) {
        a1 = -a1;
    }
    
    //把传入的外部对象x转化为符号整数
    
    a2 = x.dollars*100 + x.cents;
    if (x.sign==minusv) {
        a2 = -a2;
    }
    
    a3 = a1+a2;
    
    //转换为Currency对象的表达式
    
    if (a3<0) {
        result.sign = minusv;
        a3 = -a3;
    }else{
        
        result.sign = plusv;
    }
    
    result.dollars = a3/100;
    result.cents = a3-result.dollars*100;
    
    //返回一个对象
    return  result;
    
    
}

Currency& Currency::increment(const Currency &x)
{
    //增加x
    /*
     this 指向调用对象
     
     */
    //调用对象 加了x后 对调用对象重新赋值
    //并返回调用对象的引用
    *this = add(x);
    
    return *this;
    
}

void Currency::output()const
{
    if (sign == minusv) {
        cout<<'-';
    }
    cout<<"$"<<dollars<<".";
    if (cents<10) {
        cout<<'0';
    }
    cout<<cents;
    
}


Currency::~Currency()
{
    
}












