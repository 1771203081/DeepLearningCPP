//
//  QuickSort.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/20.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "QuickSort.hpp"

QuickSort::QuickSort()
{
   
    
    
}


void QuickSort::bubbleSortBy(int*arr,int len)
{
    int i=0,j=0,k=0,temp=0,num=0;
    for (i=0; i<len-1; i++) {
        /*
         可以看出6个数 最多执行5次排序
         */
        /*
         两两比较之后得到较小的数 再往前比较
         */
        for (j=len-1; j>i; j--) {
            if (arr[j-1]>arr[j]) {
                temp = arr[j-1];
                arr[j-1]=arr[j];
                arr[j]=temp;
            }
            //依次输出排序结果
            printf("第%d步排序分解:",i+1);
            for (k=0; k<len; k++) {
                printf("%d",arr[k]);
            }
            printf("\n");
        }
        
        
        printf("第%d步排序结果为:",i+1);
        num = 0;
        //依次输出排序结果
        for (k=0; k<len; k++) {
            printf("%d",arr[k]);
        }
        printf("\n");
        //如果排序在中间完成 就退出程序
        for (k=0; k<len-1; k++) {
            if (arr[k]<arr[k+1]) {
               
                /*
                 统计比较的次数
                 最多比较Len-1次 如果满足排序顺序 就加1
                 */
                num++;
            }
        }
        if (num==len-1) {
            return ;
        }
        
        
    }
   
}

void QuickSort::quickSortBy(int* arr,int startIndex,int endIndex)
{
    //递归结束条件 ：StartIndex 大等于 endIndex的时候
    if (startIndex>=endIndex) {
        return;
    }
    
    fenzhiFlag = fenzhiFlag+1;
    
    //得到基准元素的位置
    printf("第%d次分治:\n", fenzhiFlag);
    
    //分治点
    pIndex = partition(arr, startIndex, endIndex);
    printf("分治点：%d\n",pIndex);
    //用分治法递归数列的两部分
    quickSortBy(arr, startIndex, pIndex-1);
    quickSortBy(arr, pIndex+1, endIndex);
    
    
}

void QuickSort::outArray(int* arr,int length)
{
    int start = 0;
    while (start<length) {
        printf("%d,",arr[start]);
        start++;
    }
    
    printf("\n\n");
    
}

int QuickSort::partition(int*arr,int startIndex,int endIndex)
{

    //取第一个位置的元素作为基准元素
    int pelement = arr[startIndex];
    int left = startIndex;
    int right = endIndex;
    //坑的位置 初始等于pelement的位置
    int index = startIndex;
    //大循环在左右指针重合或者交错时结束
    int smallflag =0;
    int bigflag =0;
    while (right>=left) {
        //right指针从右向左进行比较
        //右侧查小 -- 移走小的值至标记位 标记小的值位值
        //跳出该循环 进行左侧查大循环
        
        
        while (right>=left) {
            printf("右侧查小%d次  ",smallflag);
            if (arr[right]<pelement) {
                printf("右侧查小%dloopend  \n",smallflag);
                outArray(arr,length);
                arr[left]=arr[right];
                index=right;
                outArray(arr,length);
                left++;
                break;
                
            }
            smallflag++;
            right--;
        }
        
        //left指针从左向右进行比较
        //左侧查大 ++ 找到大的 移走大的到小的标记位
       
        while (right>=left) {
            printf("左侧查大%d次  ",bigflag);
            if (arr[left]>pelement) {
                printf("左侧查大%d loopend--\n",bigflag);
                outArray(arr,length);
                arr[right]=arr[left];
                index=left;
                outArray(arr,length);
                right--;
                break;
            }
            bigflag++;
            left++;
        }
        /*while doen*/
    }
    /*loop closed*/
    
    outArray(arr,length);
    arr[index] = pelement;
    outArray(arr,length);
    
    return index;
    
}


QuickSort::~QuickSort(){
    
}






