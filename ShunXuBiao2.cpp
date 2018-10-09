//
//  ShunXuBiao2.c
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

#include "ShunXuBiao2.hpp"


/*
 头插入法建表
 从一个空表开始
 重复读入数据 生成新节点
 将读入的数据存到新节点的数据域中
 然后将新节点插入到当前链表的表头上
 直到读入结束标志为止
 
 即每一次插入的节点都作为链表的第一个节点
 */

LNode* create_LinkList(void)
{
    /*
     头插入法创建单链表
     链表的头节点head作为返回值
     */
    int data = 0;
    LNode* head,*p;
    head =(LNode*)malloc(sizeof(LNode));
    head->next=NULL;/*创建链表的表头节点head*/
    while (data<10) {
       
        p=(LNode*)malloc(sizeof(LNode));
        p->data=data;/*数据域赋值*/
        
        /*钩链 新创建的节点总是作为第一个节点*/
        //持有旧的
        p->next = head->next;
        //接入新的
        head->next = p;
       
        data = data + 1;
        
        
    }
    
    return head;
}
/*
 尾插入法建表
 
 头插入法建表 生成的链表中节点的次序 与输入的顺序相反
 
 希望两者的次序一致 采用尾插入法建表
 
 该方法将新节点插入到当前链表的表尾
 使其成为当前链表的尾节点
 */

LNode* create_LinkList_end(void)
{
    /*尾插入法创建单链表 链表的头节点head 作为返回值*/
    
    int data = 0;
    LNode*head,*p,*q;
    //p 为头节点临时变量 因为尾插才有
    head = p = (LNode*)malloc(sizeof(LNode));
    /*创建单链表的表头节点head*/
    p->next = NULL;
    
    while (data<10) {
       
       
        q=(LNode*)malloc(sizeof(LNode));
        q->data=data;/*数据域赋值*/
        
        /*钩链 新创建的节点总是作为第一个节点插入到链表头*/
        
        //MARK:这里尾插法
        /*
          q->next=p->next
         与
          q->next = NULL;
         等效果
         */
       // q->next=p->next;
        q->next = NULL;
        p->next=q;
        /*这里只是修改了临时变量的指针存储的地址
        和头插法不同 第一 头插法 最后链表的显示的数据顺讯 与 输入的顺序相反
         第二 这里 在钩链过程中 依旧是新建节点
         
         然后新建节点 next 指向 旧头节点的next
         
         然后 旧头节点的next 指向新节点
         
         不同在于 头插法 这个旧头节点没有修改过 一直是链表头
         
         但是尾插法不同 这个头节点一直在偏移 因此尾插法 新创建的节点永远是 头插法的第一步 永远是新创建的节点在链表尾部
         */
        p=q;
        
        data = data + 1;
        
    }
    return head;
    
    
}

void doLianBiao()
{
    LNode* p1 = create_LinkList();
    
    LNode* p2 = create_LinkList_end();
  
    
    
}

//ElemType get_Elem(LNode*L , int i)
//{
//    int j;
//    LNode * p;
//    p = L->next
//}









