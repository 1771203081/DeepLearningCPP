//
//  BayesFenLei.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef BayesFenLei_hpp
#define BayesFenLei_hpp
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;



/*
 读入文件数据
 */

void In();

void Init();

/*
 读入样本数量个样本
 并求出该样本的二维正态分布
 */
/*函数说明
 第一参数 为样本数组  数组指针
 第二参数 为样本总数  整型
 第三参数 为样本统计分析后结构体存储统计结果 各自的期望 各自的标准差 两个维度的相关系数 使用引用传值
 */
void Normalization(struct HUMAN* human,int human_num,struct NORMAL&human_normal);
/*
 在分布为normal的条件下特征为(x1,x2)的条件概率
 */

double P(struct NORMAL& normal,double x1,double x2);
/*
 归为normal的后验概率
 t为0表示female 1表示male
 */
double Posterior_probability1(double x1,double x2,bool t);
/*
 判断是那个类别 返回0表示female 1表示male
 */

bool Classify(double x1,double x2);

/*
 得到错误率并将错误率输出到result.txt中
 */
void Find_error_rate();


//二维正态分前 先标准正态分布
void Normal();
#endif /* BayesFenLei_hpp */
