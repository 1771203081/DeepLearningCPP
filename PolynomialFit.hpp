//
//  PolynomialFit.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef PolynomialFit_hpp
#define PolynomialFit_hpp

#include "augmentedmatrix.hpp"
#include <stdio.h>


class PolynomialFit {
    
    
public:
    PolynomialFit();
    ~PolynomialFit();
    
    //设置多项式的属性 如函数的阶数 曲线的截距等
    void setAttribute(int degree,bool intercedeEnable = false,double intercede = 0.0);
    /*
     这里回顾一下
     
     这里 标记virtual 第一是 提醒使用者 或者 代码编写人员的编写该函数的用意 是 将用于 子类继承
     第二 virtual 对内存有什么影响
     
     第三 回顾一下 重载 overload与 重写 override（覆盖）
     在C++中 重载
     1、普通函数（非成员函数）只能被overload，不能被override，
     2、它是指我们可以定义一些名称相同的方法，通过定义不同的输入参数来区分这些方法，然后再调用函数时，就会根据不同的参数样式，来选择合适的方法执行
     
     在C++中 重写
     
     在类继承时体现
     
     */
    
    //设置曲线的样本权重，权重等
    
    virtual bool setSample(double*x,double*y,int count,bool enableWeight,double *w);
    /*
     C++多态概念梳理
     多态按字面的意思就是多种形态。当类之间存在层次结构，并且类之间是通过继承关联时，就会用到多态。
     C++ 多态意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数
     
     
     
     */
    /*
     这里虚函数 没有说必须让子类实现
     如果父类不实现 让子类实现 要定义纯虚函数
     来提供接口框架的纯虚函数
     */
    //获取计算的结果
    virtual float getResult(int y);
    virtual bool process();
    //打印
    void print();
protected:
    // 截距
    double intercede;
    //b截距使能
    bool isIntercedeEnable;
    //阶数
    int degree;
    //多项式的项数
    int multiterm;
    //样本-权重
    fraction*sx,*sy,*weight;
    //样本数量
    int count;
private:
    //系数矩阵和结果向量
    fraction* matrix,*rvector,*results;
    //利用最小二乘法 将样本转换成求解的方程组
    bool leastQuare();
    //计算矩阵某项的累计值
    fraction calcMatrixUnit(int x,int y);
    //计算向量某项的累计值
    void fillVectorUnit(int y);
    
    void init();
    //释放内存
    
    void releaseSamples();
    void releaseMatrix();
};

#endif /* PolynomialFit_hpp */
