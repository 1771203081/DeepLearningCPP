//
//  QuickSort.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/20.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef QuickSort_hpp
#define QuickSort_hpp
#include <iostream>
#include <stdio.h>
using namespace std;

class QuickSort {
    
    
public:
    QuickSort();
    void quickSortBy(int* arr,int startIndex,int endIndex);
    void outArray(int* arr,int length);
    int partition(int*arr,int startIndex,int endIndex);
    void bubbleSortBy(int*arr,int len);
    ~QuickSort();
    int length;
    int fenzhiFlag=0;
    int pIndex;//分治点
};




#endif /* QuickSort_hpp */
