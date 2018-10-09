//
//  main.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/6.
//  Copyright © 2018年 admindyn. All rights reserved.
//



#include "array2d.hpp"
#include "unittest.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int** p;
    int size[10]={11,12,13,14,15,16,17,18,19,20};
    make2dArray(p, 10, size);
    loopLog(p, size);
    delete2dArray(p,10,size);
    int** d2;
    make2dArray(d2, 10, 10);
    loopLog(d2);
    delete2dArray(d2,10);
    
    testArray();

    testCurrency();
    testC3U();
    testFib();
    testSort();

    testFileHandler();
    
    testBayesFenLei();
    
    testGanZhiJi();
    
    testXianXingDanYuan();
    
    testZuiJinLin();
    
    testLianBiao();
    
   // testRBTree();
    
  
    double v = 1.23e+02;
    printf("计算机的科学计数法:%f",v);
    
 testQuXianNiHe_DuoXiangShiFangFA();
    
      testZuiXiaoErChengFa();
    
    return 0;
}

int changeLength1D(char* s,int len)
{
    int sclen = strlen(s);
    printf("%d \n",sclen);
    
    return 1;
}
