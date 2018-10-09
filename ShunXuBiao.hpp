//
//  ShunXuBiao.h
//  CPPB20180806
//
//  Created by admindyn on 2018/8/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef ShunXuBiao_h
#define ShunXuBiao_h

#include <stdio.h>
#define OK 1
#define ERROR -1
#define  MAX_SIZE 100
typedef int Status;
typedef int ElemType;
typedef struct sqlist{
    ElemType Elem_array[MAX_SIZE];
    ElemType* elem_array;
    int length;
}Sqlist;





#endif /* ShunXuBiao_h */
