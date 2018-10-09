
//
//  GanZhiJi.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/4.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "GanZhiJi.hpp"

using namespace std;
/*
 Rosenblatt 算法
 
 二类分类的线性模型
 */

//学习率
const double lr = 1 ;
//特征维度
const int dim = 2 ;
//样本个数
const int n = 3 ;

//权重
double w[dim] = {0,0};
//偏移項
double b = 0;
//样本
double samples[n][dim] = {3,3,4,3,1,1};
//样本标记-> 样本分类
int labels[n] = {1,1,-1};

/*计算两个向量的内积*/
double dot(double*w,double*feature)
{
    
    double sum = 0;
    for (int i = 0; i < dim; i++) {
        
        sum += (*w) * (*feature) ;
        w ++ ;
        
        feature++;
        
    }
    
    
    return sum;
    
}

/*感知机算法 感知机的目的是确定 也就是求得W 和 b的值
 默认我们用double w[dim] = {0,0} 和 double b = 0;起步开始逐个测试
 
 通过不断的迭代 将提供的样本数据完全划分为 正类或者 父类
 整个迭代才会结束 也就确定了要使用的W 和 b 来给以后的数据做分类
 
 
 注意我们实现的算法中
    这里目标是寻找将 所有样本数据都确定为正类的 W 和 B
 
    一旦发现 样本数据的特征向量使用W 和 B 处理后为 负类
 
    就重新确定W 和 B
 
    并重新开始循环 （最外层循环）
 
 三层循环  最外层为while true 死循环
         第二层为for 循环 用来迭代取出 特征向量
         第三层为条件if for 循环 当特征向量出现负类
         就利用for循环重新计算W 和 B
 
 
 */

void perceptron()
{
    int j = 0;
    while (true) {
        
        cout<<"第 "<<j<<" 次"<<"最外部循环执行"<<endl;
        
        j++;
        int i ;
        
        for (i = 0; i < n; i++) {
            
          
            /*
             每一次循环 执行
             第一步 取出samples 特征向量数组中的 第i个特征向量
             第二步 将  权重向量 与 取出的特征向量 求内积 并与 b偏移量 求和 判断正负
             注意 根据算法 权重向量w 与 取出的特征向量x  w*x+b = 0 是分类点
             
             第三步
             
             */
            if (labels[i]*(dot(w,samples[i])+b) <= 0) {
                
                cout<<"感知机二分类" <<"第 "<< i <<" 个特征向量"<<"这里小于0 属于负类"<<endl;
                
                cout<< "w:( ";
                
                for (int j = 0; j < dim; j++) {
                    
                    w[j] = w[j] + lr * labels[i]* samples[i][j];
                    
                    cout<<w[j];
                    
                    if (j != dim - 1) {
                        cout<< ",";
                        
                    }
                    
                }
                b = b + lr*labels[i];
                
                cout<<") b: "<<b <<endl;
                
                break;
                
                
                
            }else{
                
                 cout<<"感知机二分类" <<"第 "<< i <<" 个特征向量"<<"这里大于0 属于正类"<<endl;
            }
         
            
        }
        /*First For Loop end*/
        
        if (i == n) {
            cout<<"跳出最外层"<<"循环:"<<i<<endl;
            break;
        }
        
    }
    /*While  Loop end*/
    
    
}
