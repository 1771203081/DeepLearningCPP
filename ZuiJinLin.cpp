//
//  ZuiJinLin.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/4.
//  Copyright © 2018年 admindyn. All rights reserved.
//


#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <fstream>

#include "ZuiJinLin.hpp"

using namespace std;

/*
 KNN 最近邻算法
 
 算法应用场景
 
 训练样本（要有特征向量 比如随机变量X,Y组成的特征向量 X-> 到课率 Y-> 作业质量）
 
 对训练样本可以建立分类（也就是说在使用最近邻算法前 已经有了数据的分类标准 等价于在这之前已经用感知机 或者 线性单元 确定了分类的权重向量和 偏差值）->(分类标签-> 不及格  优秀)
 
 最后使用KNN最近邻算法 找到与我们的输入样本 比如张三同学的 X到课率 Y作业质量 来预估张三同学属于哪一个分类
 
 这里描述一下KNN最近邻算法效果（KNN算法将计算张三 到训练样本的距离 算法欧式距离 再从中选取K个最近的距离 比如k=3 那么最后我们通过比较最近的三个样本分别属于那个类别 来预估 张三的期末成绩将属于那个类别 （选择这k个最近样本中频率最高的类别作为最后评定张三的预测类别））
 
 
 */


/*
 KNN算法 步骤
 
 1）算距离：给定测试对象，计算它与训练集中的每个对象的距离
 2）找邻居：圈定距离最近的k个训练对象，作为测试对象的近邻
 3）做分类：根据这k个近邻归属的主要类别，来对测试对象分类
 */

typedef char tLabel ;
typedef double tData;
typedef pair<int, double> PAIR;
const int colLen = 2;
const int rowLen = 12;

ifstream fin;
ofstream fout;


class KNN {
private:
    tData dataSet[rowLen][colLen];
    tLabel lables[rowLen];
    tData testData[colLen];
    int k;
    map<int, double> map_index_dis;
    map<tLabel,int> map_label_freq;
    double get_distance(tData* dl,tData*d2);

public:
    KNN(int k);
    
    void get_all_distance();
    
    void get_max_freq_label();
    
    struct CmpByValue{
        bool operator()(const PAIR&lhs,const PAIR&rhs)
        {
            return lhs.second < rhs.second;
        }
        
    };
};

KNN::KNN(int k)
{
    this->k = k;
    
    fin.open("knnData.txt");

    if (!fin) {
        cout<<"can not open the file knnData.txt"<<endl;
        exit(1);
    }
    
    /*input the dataSet*/
    
    for (int i = 0; i<rowLen; i++) {
        for (int j = 0; j<colLen; j++) {
            fin>>dataSet[i][j];
        }
        fin>>lables[i];
    }
    
    /*
     算法步骤
     1）算距离：给定测试对象，计算它与训练集中的每个对象的距离
     2）找邻居：圈定距离最近的k个训练对象，作为测试对象的近邻
     3）做分类：根据这k个近邻归属的主要类别，来对测试对象分类
     注意这里 与给出的算法步骤有一点区别
     就是 我们给出了训练样本
     并且 已经确定好了分类
     
     因此 我们就省去了 给样本做分类的步骤
     直接计算k个近邻中分类的频率
     选最高频率的分类 作为我们给出的评定的预测分类
     */
    
    //张三的数据
    double a[2] = {0.4,0.6};
    double * p = testData;
    *p = a[0];
    *(p++) = a[1];
    

}

double KNN:: get_distance(tData *dl, tData *d2)
{
    double sum = 0;
    
    for (int i =0 ; i<colLen; i++) {
        sum += pow(dl[i] - d2[i], 2);
    }
    
    
    return  sqrt(sum);

}



void KNN::get_all_distance()
{
    
    double distance;
    
    int i;
    
    for (i = 0; i<rowLen; i++) {
    
        distance = get_distance(dataSet[i], testData);
        
        map_index_dis[i] = distance;
        
    }
    
    map<int,double>::const_iterator it = map_index_dis.begin();
    
   
    
    while (it != map_index_dis.end()) {
        
        cout<<"index = "<<it->first<<" distance = "<<it->second<<endl;
        it++;
        
    }
    
    
}


void KNN::get_max_freq_label()
{
    
    vector<PAIR>    vec_index_dis(map_index_dis.begin(),map_index_dis.end());
    
    sort(vec_index_dis.begin(), vec_index_dis.end(), CmpByValue());
    
    for (int i = 0; i<k; i++) {
        cout<<"the index = "<<vec_index_dis[i].first<<" the distance = "<<vec_index_dis[i].second << " the label = "<<lables[vec_index_dis[i].first]<<" the coordinate ( "<<dataSet[vec_index_dis[i].first][0]<<","<<dataSet[vec_index_dis[i].first][1]<<" )"<<endl;
        
        
        map_label_freq[lables[vec_index_dis[i].first]]++;
        
    }
    
    
    map<tLabel,int>::const_iterator map_it = map_label_freq.begin();
    
    tLabel label;
    
    int max_freq = 0 ;
    
    while (map_it != map_label_freq.end()) {
        
        if (map_it->second > max_freq) {
            max_freq = map_it->second;
            label = map_it->first;
        }
        map_it++;
        
    }
    
    cout<<"The test data belongs to the "<<label<<" label"<<endl;
    
}


void runKNN()
{
    int k = 5;
    KNN knn(k);
    knn.get_all_distance();
    knn.get_max_freq_label();
    
}







