//
//  C2U.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/16.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "C2U.hpp"



//
//  CU.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//


#include <new>
#include "illegalParameterValue.hpp"




C2U::C2U(signType theSign,unsigned long theDollars,unsigned int theCents)
{
    //创建一个Currency 类对象
    setValue(theSign, theDollars, theCents);
}

void C2U::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
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

void C2U::setValue(double theAmount)
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

signType C2U::getSign()const
{
    if (amount<0) {
        return minusv;
    }else{
        return plusv;
    }
}

unsigned long C2U::getDollars()const
{
    if (amount<0) {
        return (-amount)/100;
    }else
    {
        return amount/100;
    }
    
}

unsigned int C2U::getCents()const
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

C2U C2U::operator+(const C2U &x) const
{
    /*把参数对象x和调用对象*this相加*/
    C2U result;
    result.amount = amount + x.amount;
    return  result;
}

C2U& C2U::operator+=(const C2U &x)
{
    amount =amount + x.amount;
    
    return *this;
}
/*这里对流插入操作符 也是重载 但是没有作为成员函数重载而已 但是即便修改也是作为 友元函数重载*/
ostream& operator<<(ostream&out,const C2U&x)
{
    x.output(out);
    
    return out;
}

/**/
void C2U::output(ostream&out)const
{
    long theAmount = amount;
    
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
}


C2U::~C2U()
{
    
}









