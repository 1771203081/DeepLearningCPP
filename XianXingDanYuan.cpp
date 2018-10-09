//
//  XianXingDanYuan.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/4.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "XianXingDanYuan.hpp"
/*
 梯度下降和delta法则
 Liner Unit 线性单元
 线性单元（linear unit），delta法则：
 为了解决样例不是线性可分的问题，核心为梯度下降法来搜索可能的权向量的假设空间。
 理解为训练一个无阈值的感知器，也就是一个线性单元（linear unit）。
 */
using namespace std;


const int DataRow = 4;

const int DataColumn = 3;

const double learning_rate = 0.01;

double DataTable[DataRow][DataColumn];

double Theta[DataColumn-1];
//训练误差
const double loss_theta = 0.001;
//梯度下降的最大训练次数应小于100
const int iterator_n = 100;

void Init_TiDuXiaJiang()
{
    
    ifstream fin("data.txt");
    
    for (int i=0; i<DataRow; i++) {
        for (int j=0; j<DataColumn; j++) {
            
            fin>>DataTable[i][j];
            
        }
    }
    
    if (!fin) {
        cout<<"fin error";
        exit(1);
    } else {
        fin.close();
    }
    
    
    for (int i = 0; i<DataColumn-1; i++) {
        
        Theta[i] = 0.5;
    }
    
}
/*
 梯度下降变体被称为增量梯度下降算法（incremental gradient descent）或者随机梯度下降（stochastic gradient descent）。
 */

//MARK:标准梯度下降
void batch_grandient()
{
    double loss = 1000;
    for (int i=0; i<iterator_n&&loss>=loss_theta; i++) {
        /*
         梯度下降的终止条件是
         当梯度下降次数 超过100 并且
         当梯度下降的训练误差小于 目标训练误差0.001 将终止
         梯度下降算法的目标函数E(W) 也就是求得使得目标函数值也就是训练误差最小的权重W向量
         
         我们假设样本用例集合D
         td 是训练样例d的目标输出
         od 是线性单元对训练样例d的输出
         目标函数            ∑
            E(w) = (1/2) * 累和 (td-od)²
                           d∊D
         
         这里的目标函数 有点在计算方差的影子
         
         梯度下降算法 就是对目标函数求偏导 对变量W（权重向量）求偏导
         使得目标函数求得最小值成立
         */
        
        double Thetasum[DataColumn-1] = {0};
        
        for (int j = 0; j<DataRow; j++) {
            double error = 0;
            /*
             梯度下降算法第一步
             W权重向量 与 样本数据中取出第i个特征向量 做内积
             
             （这里没有加 偏差項 b）
             */
            for (int k = 0; k< DataColumn - 1; k++) {
                
                //error += DataTable[j][k]*Theta[k]+b;
                /*
                 每一个特征向量的每一个维度作为输入元素x
                 与 权重每一维度 相乘 再累和
                 
                 这是内积
                 */
                
                error += DataTable[j][k]*Theta[k];
                
            }
            
            /*
             第二步 误差项计算
             
             上一步 内积得到的error 就是 节点的加权输入net
             net = Wx + b
             
             这里W是权重向量 x是样本的特征向量 b是偏差項
             
             我们假定函数F激活函数存在满足：
             net为节点的加权输入 F 是激活函数
             O为对应的第i个net加权输入 对应的输出项
             O = F(net)
             
             以上的激活函数也满足：
             这里线性单元的激活函数为
             y = 𝐅(x) = x
            
             误差项计算 y是目标值 O是训练样例的输出
             
             误差等于 特征向量的第i个元素减去加权输入net的差值
             
             */
            error = DataTable[j][DataColumn-1]-error;
            /*
             第三步 权重向量更新
             权重更新的法则：
             w = 𝛈*(td - Od)*x(i)
             w 是权重向量的某一维度
             𝛈 是学习率
             td 是目标输出值
             Od 是线性单元对训练样本的输出
             x(i) 时训练样本的某一维度
             */
          
            for (int k = 0; k<DataColumn - 1; k++) {
                
                Thetasum[k] += learning_rate* error * DataTable[j][k];
                
            }
        }
        
        /*
         标准的梯度下降是在权值更新前对所有的样例汇总误差，而随机梯度下降的权值是通过考查每个训练样例来更新的
         */
        double a = 0;
        
        for (int k = 0; k<DataColumn - 1; k++) {
            Theta[k] += Thetasum[k];
            /*
             目标函数为 
             */
            a+=abs(Thetasum[k]);
        }
        
        loss = a/(DataColumn - 1);
        
    }
    
}


//MARK:随机梯度下降

void stochastic_gradient()
{
    double loss = 1000;
    for (int i = 0; i<iterator_n&&loss>=loss_theta; i++) {
        
       // double Thetasum[DataColumn-1] = {0};
        
        for (int j = 0; j < DataRow; j++) {
            double error = 0;
            
            for (int k = 0; k< DataColumn -1; k++) {
                double v = DataTable[j][k];
                error += v*Theta[k];
                
            }
            
            double t = DataTable[j][DataColumn - 1];
            
            error = abs(t - error);
            
            double a = 0;
            /*
             权重更新的法则：
             w = 𝛈*(td - Od)*x(i)
             w 是权重向量的某一维度
             𝛈 是学习率
             td 是目标输出值
             Od 是线性单元对训练样本的输出
             x(i) 时训练样本的某一维度
             */
            for (int k = 0 ; k<DataColumn - 1; k++) {
                
                Theta[k] += learning_rate*error*DataTable[j][k];
            a+=abs(learning_rate*error*DataTable[j][k]);
                
            }
            
            loss=a/(DataColumn-1);
            if (loss<=loss_theta) {
                cout<<"最外层循环了"<<i<<"次"<<endl;
                break;
                
            }
        }
        
    }
}


void printTheta()
{
    
    for (int i=0; i<DataColumn-1; i++) {
        cout<<Theta[i]<<" ";
    }
    cout<<endl;
    
}

void tiDuXiaJiang()
{
    int da = 10;
    cout<<"10的abs绝对值函数的值:"<<abs(da)<<endl;
    Init_TiDuXiaJiang();
    //batch_grandient();
    stochastic_gradient();
    printTheta();
}
