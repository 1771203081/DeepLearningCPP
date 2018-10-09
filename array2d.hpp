//
//  array2d.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/6.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef array2d_hpp
#define array2d_hpp
#include <iostream>
#include <stdio.h>
using namespace std;

//template <typename T>

// T[n] 一维数组 假设T 数据类型为int
//二维数组 T(*p)[m] 这就有m个T数组指针
//那么T**p 是第一行首元素
int make2dArray(int** &x,int numberofRows,int* b);
int loopLog(int** &p,int* size);
int make2dArray(int** &x,int numberofRows,int numberofColumns);
void delete2dArray(int** &x,int numberofRows);
void delete2dArray(int** &x,int numberofRows,int* size);
int loopLog(int** &p);
int testArray();
int changeLength1D(char* s,int len);

#endif /* array2d_hpp */
