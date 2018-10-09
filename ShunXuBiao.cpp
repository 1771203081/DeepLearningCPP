//
//  ShunXuBiao.c
//  CPPB20180806
//
//  Created by admindyn on 2018/8/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/types.h>
#include <stdio.h>

#ifdef __APPLE__
//苹果操作系统!
#include <sys/fcntl.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>


#include <arpa/inet.h>
#if TARGET_IPHONE_SIMULATOR

// 苹果下的iOS 模拟器操作系统



#elif TARGET_OS_IPHONE
// 苹果下的iOS操作系统

#elif TARGET_OS_MAC
// 苹果下的MAC 操作系统


#else

// 苹果下的其他 操作系统

#endif

#elif __linux__
//linux操作系统!
/* for socket/bind/listen() */
#include <linux/tcp.h>          /* for TCP_NODELAY */
#include <pthread.h>

#else
//其他操作系统 可能是 UNIX 或者 Windows


#endif
#include "ShunXuBiao.hpp"


//线性表的顺序存储结构
//线性表初始化
Status Init_Sqlist(Sqlist*L)
{
    ElemType* p = (ElemType*)malloc(MAX_SIZE*sizeof(ElemType));
    L->elem_array = p ;
    if (!L->elem_array) {
        return ERROR;
    } else {
        L->length = 0 ;
        return OK;
    }
    
    
}
/*
 注意这里的i的计数  范围是 i大于等于1 小于等于n
 */
//顺序线性表的插入
/*
 将线性表L中的第i个至第n个节点后移一个位置
 将节点e插入到节点第i-1个节点之后
 线性表长度加1
 */

Status Insert_Sqlist(Sqlist*L,int i,ElemType e)
{
    int j;
    if (i<0||i>L->length-1) {
        return ERROR;
    }
    if (L->length>=MAX_SIZE) {
        printf("线性表溢出!\n");
        return ERROR;
    }
    /*
     从线性表最后开始迭代
     直到迭代到第i-1个节点结束loop
     */
    for (j=L->length-1; j>=i-1; --j) {
        //依次后移填充 i-1位置以后的所有节点后移
        L->elem_array[j+1] = L->elem_array[j];
    }
    // 在i-1位置插入节点
    L->elem_array[i-1] = e ;
    L->length++;
    return OK;
}
//顺序线性表的删除
/*
 将线性表L中的第i+1个至第n个节点依次向前移动一个位置
 线性表长度
 */
ElemType Delete_Sqlist(Sqlist*L,int i)
{
    int k;
    ElemType x;
    
    if (L->length==0) {
        printf("线性表L为空!\n");
        return ERROR;
    } else if(i<1||i>L->length)
    {
        printf("要删除的数据元素不存在!\n");
        return ERROR;
    }else{
        /*
         保存节点的值
         */
        x=L->elem_array[i-1];
        
        for (k=i; k<L->length; k++) {
            //i位置以后的所有节点前移
            L->elem_array[k-1] = L->elem_array[k];
        }
        L->length--;
        return x;
    }
    
    
}

//顺序线性表查找定位删除
/*
 在线性表L查找值为X的第一个数据元素
 将从找到的位置至最后一个节点依次向前移动一个位置
 线性表长度减1
 */

Status Locate_Delete_Sqlist(Sqlist*L,ElemType x)
{
    /*删除线性表L中值为X的第一个节点*/
    int i=0,k;
    
    while (i<L->length) {
        /*查找值为X的第一个节点*/
        if (L->elem_array[i]!=x) {
            i++;
        } else {
            for (k=i+1; k<L->length; k++) {
                L->elem_array[k-1] = L->elem_array[k];
            }
            L->length--;
            break;
            
        }
    }
    if (i>L->length) {
        printf("要删除的数据元素不存在!\n");
        return ERROR;
    }
    
    
    return OK;
    
    
}














