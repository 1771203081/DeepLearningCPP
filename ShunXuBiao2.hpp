//
//  ShunXuBiao2.h
//  CPPB20180806
//
//  Created by admindyn on 2018/8/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef ShunXuBiao2_h
#define ShunXuBiao2_h

#include <stdio.h>
#define OK 1
#define ERROR -1
#define  MAX_SIZE 100
typedef int Status;
typedef int ElemType;
typedef struct Lnode{
    /*
     数据域 保存节点的值
     */
    ElemType data;
    /*
     指针域
     */
    struct Lnode* next;
}LNode;/*节点的类型*/

void doLianBiao();


#endif /* ShunXuBiao2_h */
