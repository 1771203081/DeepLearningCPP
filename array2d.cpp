//
//  array2d.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/6.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <string>
#include <new>
#include "array2d.hpp"


//template <typename T>

// T[n] 一维数组 假设T 数据类型为int
//二维数组 T(*p)[m] 这就有m个T数组指针
//那么T**p 是第一行首元素

int make2dArray(int** &x,int numberofRows,int numberofColumns)
{
    //创建一个二维数组
    /*
     数组指针 必须确定某一维的大小
     
     对于二维数组开辟 某一维不确定大小 动态时必须使用new
     char(*c)[5];
    
     c= new char[n][5]
     
     而下面就开始用指针数组了 有对应关系
     但自成一体
     
     
     */
    try {
        //创建行指针
        x = new int *[numberofColumns];
        //可以省略这个优化
        int** p =x;
        
        //为每一行分配空间
        for (int i =0 ; i<numberofRows; i++) {
            
        p[i]= new int[numberofColumns];
       
        }
        
        return 1;
        
    } catch (bad_alloc) {
        return 0;
    }

    
}
//第三个参数是数组 首地址
int make2dArray(int** &x,int numberofRows,int* b)
{
    x = new int*[numberofRows];
    
    for (int i=0; i<b[i]; i++) {
        x[i] = new int[b[i]];
    }
    return 1;
}


void delete2dArray(int** &x,int numberofRows)
{
    /*
     释放二维数组 空间
     先释放每一行的分配的空间 再释放为行指针分配的空间
     */
    
    //删除行数组空间
    for (int i=0; i<numberofRows; i++) {
        
        delete [] x[i];
        
    }
    //删除行指针
    
    delete []x;
    
    x=NULL;
    
}

void delete2dArray(int** &x,int numberofRows,int* size)
{
    /*
     释放二维数组 空间
     先释放每一行的分配的空间 再释放为行指针分配的空间
     */
    
    //删除行数组空间
    
    
  
    
    for (int i=0; i<numberofRows; i++) {
        
        int* p=(*(x+i)) ;
        
        delete []p;
    }
   
    //删除行指针
    delete []x;
    x=NULL;
    
}

int testArray()
{
    cout<<__FILE__<<__func__<<endl;
    printf("二维数组数组\n");
    //二维数组
    int a[3][4]={{0xE1,0xE2,0xE3,0xE4},{0xA5,0xA6,0xA7,0xA8},{0x09,0x01,0x08,0x04}};
    
    printf("数组指针\n");
    //数组指针
    int l[4]={41,42,43,44};
    int (*k)[4];
    k=&l;
    int* v = (int*)k;
    printf("%p %p \n",*(k),*(k+1));
    printf("*(k+1) 这个打印出来的内存地址 不知道是谁的 有可能存在 有可能不存在 \n");
    printf("%d %d\n",*(v),*(v+2));
    
    //指针数组
    printf("指针数组\n");
    int* c[3] = {a[0],a[1],a[2]} ;
    //二级指针
    printf("二级指针 只和 指针数组对应\n");
    int**p=c;
    printf("%p,%p\n",*(p),*(p+1));
    printf("%x,%x\n",*(*(p)),*(*(p+1)));
    
  
   printf("一级指针 和 数组对应\n");
    int b[4]={0x11,0x12,0x13,0x14};
    int*t = b;
    printf("%x %x\n",*t,*(t+1));
    
    printf("三级指针 只和 指针数组对应\n");
    int** d[3];
    int***h = d;
    
    printf("三级指针 以字符串举例\n");
    int temp = 0x66;
    int temp2 = 12;
    printf("指针常量 指针所指向不可以修改\n");
    int* const value =&temp;
    printf("%x\n",*value);
    //value= &temp2;
    printf("常量指针 指针指向可以修改 但是内容不可以修改\n");
    int const* value2 = &temp;
    value2 = &temp2;
    //"Enter" "New" "Point" "First"
    char z1[]= {'E','n','t','e','r'};
    char z2[]= {'N','e','w'};
    char z3[]= {'P','o','i','n','t'};
    char z4[]= {'F','i','r','s','t'};
    char* pz1 = z1;
    char* pz2 = z2;
    char* pz3 = z3;
    char* pz4 = z4;
   // char* s2[4]={pz1,pz2,pz3,pz4};
    char* s2[4]={pz4,pz3,pz2,pz1};
    char** pp2 = s2;
    printf("%s  ;\n",*pp2);
    printf("%zu ;\n",strlen(*pp2));
    printf("%s  ;\n",*(pp2+1));
    printf("%zu ;\n",strlen(*(pp2+1)));
    /*
     p2+3,p2+2,p2+1,p2都是指向数组p2每个元素的地址。现在要将数组元素的地址放在数组中，
     存放一个变量(也可以是字符串)地址时，需要的是指针，那么存放一个地址的地址，就需要一个二重指针(因为只有指针可以存放地址，这里是存放一个地址的地址，所以要用二重指针)
     */
    char** s3[4]={pp2,pp2+1,pp2+2,pp2+3};
    char*** p3 = s3;
    
    printf("%s;\n",**p3);
    printf("%s;\n",**(p3+1));
    
    return 1;
}

int loopLog(int** &p)
{
    /*指针数组规则 因为二级指针对应 指针数组开辟的空间*/
  
        int* r;
        for (int i=0; i<10; i++) {
            r= (*(p+i));
            for (int j=0; j<10; j++) {
            int* v = (int*)(r+j);
                *v = i*10+j;
            }
        }
        for (int i=0; i<10; i++) {
            r= (*(p+i));
            for (int j=0; j<10; j++) {
            int* v = (int*)(r+j);
                printf(" %d ",*v);
            }
            printf("\n\n");
        }

    
    
    return 1;
    
}


int loopLog(int** &p,int* size)
{
    
    int* temp;
  
    for (int i=0; i<10; i++) {
        temp=(*(p+i));
        for (int j=0; j<size[i]; j++) {
             int* v = (int*)(temp+j);
            *v=i*10+j;
        }
    }

    for (int i=0; i<10; i++) {
        temp=(*(p+i));
        for (int j=0; j<size[i]; j++) {
            
            int* v = (int*)(temp+j);
        
            printf("  %d   ",*v);
        }
        printf("\n\n");
     
    }
    
    
    
    return 1;
}



