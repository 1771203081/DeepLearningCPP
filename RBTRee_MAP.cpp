//
//  RBTRee_MAP.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//



#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "RBTRee_MAP.hpp"

using namespace std;

/*
 红黑树 C++ Map的实现原理
 */




//MARK:原理是红黑树
void evluate_map()
{
    /*
     创建了红黑树map 数据结构
     */
    map<int, string> mapStudent;
    /*
     往红黑树数据结构中 连续插入 键值对
     */
    mapStudent[1] = "student_one";
    mapStudent[2] = "student_two";
    mapStudent[3] = "student_three";
    /*
     红黑树的迭代器
     */
    map<int,string>::iterator iter;
    
    for (iter = mapStudent.begin(); iter != mapStudent.end(); iter++) {
        cout<<iter->first<<"  "<<iter->second<<endl;
    }
    
    /*map 使用pair 键值对 进行存储*/
    
    pair<int, string> kv1 = pair<int, string>(100,"轮船");
    
    mapStudent.insert(kv1);
    
    /*直接使用mapStudent 所使用的关联数据类型 初始化一个需要插入的键值对 */
    
    map<int,string>::value_type v = map<int,string>::value_type(101,"航空母舰");
    
    mapStudent.insert(v);
    
    for (iter = mapStudent.begin(); iter != mapStudent.end(); iter++) {
        
        /*
           __map_iterator()
         */
        
        cout<<iter->first<<"  "<<iter->second<<endl;
      
    
    }
    
    cout<<"map的最大容量:"<<mapStudent.max_size()<<endl;
    
    
}

//MARK:原理是动态数组 又名向量
void evaluate_vector()
{
    //vector 又名向量
    /*
     vector 实际是一个动态数组 但是该类使用了 模版类实现
     我们初始化了一个动态数组
     并明确该动态数组要存储的是整型数据
     */
    vector<int> v;
    
    /*vector的压缩*/
    cout<<"Default-constructed capacity is "<<v.capacity()<<"\n";
    
    v.resize(100);
    /*
     size表示vector中已有元素的个数，容量表示vector最多可存储的元素的个数；为了降低二次分配时的成本，vector实际配置的大小可能比客户需求的更大一些，以备将来扩充，这就是容量的概念。即capacity>=size，当等于时，容器此时已满，若再要加入新的元素时，就要重新进行内存分配，整个vector的数据都要移动到新内存。二次分配成本较高，在实际操作时，应尽量预留一定空间，避免二次分配。
     */
    cout<<"Capacity of a 100-element vector is "<<v.capacity()<<"\n";
    
    cout<<"size of  a 100-element vector is "<<v.size()<<"\n";
    
    v.clear();
    
    cout<<"capacity after clear() is "<<v.capacity()<<"\n";
    
    cout<<"size after clear() is "<<v.size()<<"\n";
    
    v.shrink_to_fit();
    
    cout<<"capacity after shrink_to_fit() is "<< v.capacity() <<"\n";
    
    cout<<"size after shrink_to_fit() is "<<v.size()<<"\n";
    /*上述代码为vector的内存空间压缩*/
    
    
    /*创建一个空的vector动态数组*/
    vector<int> c;
    
    for (int i = 0; i<8; i++) {
        //在数组的最后添加一个数据
        c.push_back(i);
    }
    
    //去掉数组的最后一个数据
    c.pop_back();
    
    /*创建一个空的vector动态数组,但是存储空间确定为100的动态数组*/
    int n = 100;
    vector<int> c1(n);
    
    /*创建一个存储空间只有100的动态数组 并且全部数据项都初始化为baseStr*/
    string baseStr = "初始值";
    
    vector<string> c2(n,baseStr);
    
    //
    
    vector<int> arV;
    
    arV.push_back(10);
    arV.push_back(20);
    arV.push_back(30);
    arV.push_back(40);
    arV.push_back(50);
    arV.push_back(60);
    
    
    vector<int>::iterator pl = arV.begin();
    
    for (; pl!=arV.end(); pl++) {
        /*
         迭代器 迭代到的当前存储的值的内存地址 与当前存储值
         */
        /*
         __wrap_iter()
         */
        cout<<*pl<<" "<<pl.base()<<endl;
        //cout<<pl.operator->()<<endl;
    }
    
    cout<<endl<<pl.base()<<endl;
    
    cout<<*(--pl) << " " <<pl.base()<<endl;
    
    
}
//MARK:原理是链表
void evaluate_list()
{
    list<int> c;
    
    //链表插入数据
    for (int i =0; i<8; i++) {
        c.push_back(i);
    }
    
    //删除数据
    
    list<int>::iterator iter = c.begin();
    
    while (iter != c.end()) {
        if (*iter == 3) {
            iter = c.erase(iter);
        }else
        {
            iter++;
        }
    }

    
}
/*
 这个adapter 将iterator的赋值assigin操作改变为
 insert操作，并将iterator右移一个位置。
 如此便可让user连续执行 表面上assign而实际上insert 的行为
 */

/*模版类 ->这里 模仿 STL 库中insert_iterator 的模版*/
template <class Container>
class insertm_iterator {
protected:
    
    Container* container;//底层容器
    typename Container::iterator iter;
   
public:
    typedef output_iterator_tag iterator_category;//注意类型
    
    insertm_iterator(Container&x,typename Container::iterator i):container(&x),iter(i){
        
    }
    
    insertm_iterator<Container>& operator=(const typename Container::value_type& value)
    {
        /*关键转调用insert*/
        iter = container->insert(iter,value);
        /*令insertm iterator 永远随其target贴身移动*/
        ++iter;
        
        return *this;
    }
    
};

/*
 辅助函数
 inserterm
 模仿STL库中的 inserter 辅助函数
 */
template <class Container,class Iterator>
inline insert_iterator<Container>

inserterm(Container&x,Iterator i)
{
    typedef typename Container::iterator iter;
    
    return insert_iterator<Container>(x, iter(i));
}

/*模版函数 copym 这里模仿STL库中模版函数 copy */
template <class InputIterator,class OutputIterator>
OutputIterator copym(InputIterator first,InputIterator last,OutputIterator result) {
    while (first!= last) {
        *result = *first;
        ++result;
        ++first;
    }
    return result;
}
//MARK:迭代适配器inserter
void inserter_tag()
{
    int myints[] = {10,20,30,40,50,60,70};
    
    vector<int> myvec(7);
    
   /*
    C++ copy
    与
     memcpy(<#void *__dst#>, <#const void *__src#>, <#size_t __n#>)
    对比
    */
    
    copy(myints, myints+7, myvec.begin());
    
    list<int> foo,bar;
    
    for (int i = 1; i<=5; i++) {
        foo.push_back(i);
        bar.push_back(i*10);
    }
    
    list<int>::iterator it = foo.begin();
    
    /*迭代器向前迭代三次*/
    advance(it, 3);
    
    /*插入迭代器*/
    copy(bar.begin(), bar.end(), inserter(foo, it));
    
}

//MARK:ostream_iterator X适配器
void ostream_tag()
{
    vector<int> myvec;
    
    for (int i = 1; i<10; i++) {
        myvec.push_back(i*10);
    }
    
    ostream_iterator<int> out_it (cout,",");
    
    copy(myvec.begin(), myvec.end(), out_it);
    
    
}
//MARK:istream_iterator X适配器
void istream_tag()
{
    double val1 = 0,val2 = 0;
    
    cout<<"Please insert two values:";
    
    //end-of-stream iterator
    istream_iterator<double> eos;
    //stdin iterator
    
    istream_iterator<double> iit (cin);
    
    if (iit!=eos) {
        val1 = * iit;
    }
    
    iit++;
    
    if (iit!=eos) {
        
        val2 = *iit;
        
    }
    
    cout<<val1<<"*"<<val2<<"="<<(val1*val2)<<"\n";
    
}

//MARK:sort排序算法 - c++结构体可以定义函数

bool myFunc(int i,int j)
{
    
    return (i<j);
    
}

struct myclass {
    bool operator()(int i,int j) {
        return (i<j);
    }
}myObjFunc;



void sort_tag()
{
    int myins[] = {32,71,12,45,26,80,57,93};
    
    vector<int> myvec(myins,myins+8);
    
    /*排序后结果覆盖了源数组的内容*/
    sort(myvec.begin(), myvec.end());
    
    sort(myvec.begin(), myvec.end(), myFunc);
    
    sort(myvec.begin(), myvec.end(), myObjFunc);
    
}

void testCMAP()
{
    evluate_map();
    
    evaluate_list();
    
    evaluate_vector();
    
    inserter_tag();
    
    ostream_tag();
    
    istream_tag();
    
    sort_tag();
    
}







