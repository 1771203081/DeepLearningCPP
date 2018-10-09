//
//  unittest.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/16.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "ZuiXiaoErChengFa.hpp"
#include "RBTRee_MAP.hpp"
#include "ShunXuBiao2.hpp"
#include "ZuiJinLin.hpp"
#include "XianXingDanYuan.hpp"
#include "GanZhiJi.hpp"
#include "FileHandler.hpp"
#include "BayesFenLei.hpp"
#include "QuickSort.hpp"
#include "illegalParameterValue.hpp"
#include "unittest.hpp"

int lockv = 1;

void testZuiJinLin()
{
    runKNN();
}

void testXianXingDanYuan()
{
    tiDuXiaJiang();
}

void testGanZhiJi()
{
    
    perceptron();
    
}

void testFileHandler()
{
    FileHandler f = FileHandler();
    
    f.testFile();
    
}




void testBayesFenLei()
{
    In();
    
    Init();

    Normal();
    
    Find_error_rate();
    
}


void testLianBiao()
{
    
    doLianBiao();
    
}


void testRBTree()
{
    testCMAP();
}


void testCurrency()
{
    
    cout<<__FILE__<<__func__<<endl;
    Currency g,h(plusv,3,50),i,j;
    
    //使用两种形式的setvalue
    
    g.setValue(minusv, 2, 25);
    i.setValue(-6.45);
    
    //调用成员函数add和 output
    j=h.add(g);
    h.output();
    cout<<"+";
    g.output();
    cout<<"=";
    j.output();
    cout<<endl;
    
    //连续调用两次add
    cout<<"\n----:";
    i.output();
    cout<<"\n----:";
    g.output();
    cout<<"\n----:";
    i = i.add(g);
    i.output();
    cout<<"\n----:";
    j = i.add(h);
    j.output();
    cout<<"\n----:";
    
    
    //调用成员函数increment和add
    cout<<"\n######:";
    i.output();
    cout<<"\n######:";
    g.output();
    cout<<"\n######:";
    h.output();
    cout<<"\n######:";
    i.increment(g);
    cout<<"\n######:";
    i.output();
    j=i.add(h);
    cout<<"\n######:";
    j.output();
    
    //测试异常
    cout<<"Atempting to initialize with cents = 152"<<endl;
    
    try {
        i.setValue(plusv, 3, 95);
    } catch (illegalParameterValue e) {
        cout<<"Caught throw exception"<<endl;
        
        e.outputMessage();
    }
}


void testC3U()
{
   cout<<__FILE__<<__func__<<endl;
    
    
    C3U g,h(plusv,3,50),i,j;
    //使用两种形式的setValue 来赋值
    g.setValue(minusv, 2, 25);
    i.setValue(-6.45);
    
    //调用成员函数
    j=h+g;
    
    cout<<h<<"+"<<g<<"="<<j<<endl;
    //连续两次调用成员函数add
    j=i+g+h;
    
cout<<i<<"+"<<g<<"+"<<"h"<<"="<<j<<endl;
    
    //调用成员函数increment 和 add
    cout<<"Increment"<<i<<"by"<<g<<"and then add"<<h<<endl;
    
    j=(i+=g)+h;
    
    cout<<"Result is"<<j<<endl;
    cout<<"Increment object is"<<i<<endl;
      
    
    
    
    
    
    
    
    
}

void testFactorial()
{
    
    int v = fibonaqie(100);
    
    cout<<v<<endl;
}

void testFib()
{
    int num = 0;
    num= fibonaqie(10);
    printf("10以内的斐波那契数递归临界：%d\n", num);
    
    printf("res:%d\n",f1(7));
    printf("最大公约数:%d\n",gcd(112,42));
}

/*
 递归
 */
int factorial(int n)
{
    if (n<=1) {
        
        return 1;
        
    }else{
        
        return n*factorial(n-1);
        
    }
    
    
}

int fibonaqie(int n)
{
    int a = 1;
    int b = 1;
    int c = a+b;
    cout<<a<<" - "<<b<<" - "<<c<<" - ";
    while (c<n) {
        
        a=b;
        b=c;
        c=a+b;
        if (c>n) {
            break;
        }
        cout<<c<<" - ";
    }
  
    
    return c;
    
   
    
}

/*
 函数f(n)  当是偶数时 v=n/2 当是奇数时 v=f(3n+1)
 */

int f1(int n)
{
    if (n%2==0) {
        return n/2;
    }else{
        return f1(3*n+1);
    }
    
}

/*
 最大公约数
 */

int gcd(int v1,int v2)
{
    if (lockv==1) {
        cout<<v1<<" - "<<v2<<" - ";
        lockv=0;
    }
    
    if (v2==0) {
        return v1;
    }else
    {
         cout<<v2<<" - "<<v1%v2<<" - ";
        int v = gcd(v2, v1%v2);
       
       return v ;
    }
    
}


void testSort()
{
    //{4,7,6,5,3,2,8,1}
    //{4,7,6,5,3,2,1,8}
    //{1,2,3,4,5,6,7,8}
    //{1,8,7,6,5,4,3,2}
    int arr[] ={4,7,6,5,3,2,8,1};
    QuickSort q = QuickSort();
    q.length=8;
    printf("快速排序 分治法 排序前数组:\n");
    q.outArray(arr, q.length);
    q.quickSortBy(arr,0, q.length-1);
    
    int SIZE=8;
    
    int *shuzu = new int [SIZE];//动态数组，SIZE可以不为常量，直接输入
    
    srand((unsigned)time(NULL));//产生随机数种子
    for (int i=0;i<SIZE;i++)
    {
        shuzu[i] = rand()%9+1 ;
    }
    
    printf("排序前的数组为：\n");
    for (int i=0;i<SIZE;i++)
    {
        printf("%d ",shuzu[i]);
    }
    printf("\n");
    q.bubbleSortBy(shuzu, SIZE);

    
}

// 多项式拟合测试
void PolyfitTest()
{
    int degree = 2;
    int count = 5;
    double sx[] = {3.35,100.35,258.23,526.24,935.6};
    double sy[] = {0.5225,10200.8225,67000.1929,277000.0176,697000.56};
    double w[] = {1,0.02,0.01,0.005,0.001};
    Polynomial pf;
    pf.setAttribute(degree , false , 1.0);
    if( pf.setSample(sx,sy,count,false,w) &&
       pf.process() ){
        pf.print();
        std::cout << "\ngoodness: " << pf.getGoodNess() << std::endl;
    }else
        std::cout << "failed" ;
}

// 对数拟合测试
void LogarithmTest()
{
    double sx [] = {1,2,3,4,5,6,7,8,9,10};
    double sy[] = {6,12,24,32,41,50,59,68,77,86};
    Logarithm lf;
    if( lf.setSample(sx,sy,10,false,NULL) &&
       lf.process() ){
        lf.print();
        std::cout << "\ngoodness:" <<  lf.getGoodNess() << std::endl;
    }else
        std::cout << "failed" ;
}

// 指数拟合测试 eˣ
void ExponentTest()
{
    double sx [] = {1,2,3,4,5};
    double sy[] = {4.190873241,
        7.636268922,
        13.91418917,
        25.35330568,
        48};
    Exponent ef;
    if( ef.setSample(sx,sy,5,false,NULL) &&
       ef.process() ){
        ef.print();
        std::cout << "\ngoodness:" <<  ef.getGoodNess() << std::endl;
    }else
        std::cout << "failed" ;
}

// 幂函数拟合测试 X²
void PowerTest()
{
    double sx[] = {1,2,3,4,5};
    double sy[] = {1.258,
        2.615581859,
        4.013476146,
        5.438210223,
        9};
    Power pf;
    if( pf.setSample(sx,sy,5,false,NULL) &&
       pf.process() ){
        pf.print();
        std::cout << "\ngoodness:" << pf.getGoodNess() << std::endl;
    }else
        std::cout << "failed" ;
}

int testQuXianNiHe_DuoXiangShiFangFA()
{
    /*曲线拟合 采用多项式方法
     这里使用 泰勒展开式原理 来解释
     
     泰勒展开式 方式 使用多项式展开 指数函数展开
     */
    PolyfitTest();
    //    PowerTest();
    //    ExponentTest();
    //    LogarithmTest();
    
    return 0;
}
void testZuiXiaoErChengFa()
{
    printf("最小二乘法 未完成\n");
    testZuiXiaoErCheng();
}
