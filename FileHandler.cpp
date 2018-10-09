//
//  FileHandler.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/9/3.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "FileHandler.hpp"
using namespace std;

FileHandler::FileHandler()
{
    
}

void FileHandler::testFile()
{
    
    
    
    vector<string> vecContent;
    string strLine;
    ifstream inFile("female.txt");
    
    double height=0;
    double weight=0;
    int num=0;
    
    while (inFile>>height>>weight) {
        
        num++;
        
        cout<<height<<" "<<weight<<" "<<endl;
        
    }
    
    cout<<"关闭"<<endl;
    inFile.close();
    inFile.open("female.txt");
    
    while (inFile)
        {
            getline(inFile, strLine);
            
        vecContent.push_back(strLine);
            
        }
    
        inFile.close();
        
        // 删除第一行
    vecContent.erase(vecContent.begin());
        
        ofstream outFile("female.txt");
    
        vector<string>::const_iterator iter = vecContent.begin();
    
        for (; vecContent.end() != iter; ++iter)
        {
        
        outFile.write((*iter).c_str(), (*iter).size());
            
            outFile << '\n';
            
        }
        
        outFile.close();
        
    

}

FileHandler::~FileHandler()
{
    
}
