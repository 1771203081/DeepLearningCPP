//
//  ZuiXiaoErChengFa.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "ZuiXiaoErChengFa.hpp"
using namespace std;


class LeastSquare {
    double a,b;
    
public:
    LeastSquare(const vector<double>&x,const vector<double>& y)
    {
        double t1 = 0,t2 = 0, t3 = 0, t4 = 0;
        
        for (int i = 0; i<x.size(); ++i) {
            t1 += x[i]*x[i];
            t2 += x[i];
            t3 += x[i]*y[i];
            t4 += y[i];
        }
        
        a = (t3*x.size()-t2*t4)/(t1*x.size()-t2*t2);
        
        b = (t1*t4 - t2*t3)/(t1*x.size()-t2*t2);
        
    }
    
    double getY(const double x) const
    {
        return  a*x + b;
    }
    void print()const
    {
        cout<<"y= "<<a<<"x + "<<b<<"\n";
    }
};

void testZuiXiaoErCheng()
{
    vector<double> x;
    
    ifstream fin("zuixiaodata.txt");
    
    for (double d; fin>>d;) {
        x.push_back(d);
        
    }
    
    int sz = x.size();
    
    vector<double> y(x.begin()+sz/2,x.end());
    
    x.resize(sz/2);
    
    LeastSquare ls(x, y);
    
    ls.print();
    
    cout<<"Input x:\n";
    double xV;
    
    while (cin>>xV) {
        if(xV<1)
        {
            break;
        }
        cout<<"y = "<<ls.getY(xV)<<endl;
        cout<<"Input x:\n";
    }
}
