//
//  illegalParameterValue.hpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef illegalParameterValue_hpp
#define illegalParameterValue_hpp

#include <stdio.h>
#include <string>

using namespace std;

class illegalParameterValue {
    
    
public:
    illegalParameterValue();
    
illegalParameterValue(char* theMessage);
    
    void outputMessage();
    
private:
    string message;
    
    
};

#endif /* illegalParameterValue_hpp */
