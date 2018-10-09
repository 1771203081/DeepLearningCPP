//
//  illegalParameterValue.cpp
//  CPPB20180806
//
//  Created by admindyn on 2018/8/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "illegalParameterValue.hpp"

illegalParameterValue::illegalParameterValue()
{
    
}

illegalParameterValue::illegalParameterValue(char* theMessage)
{
    message = theMessage;
}

void illegalParameterValue::outputMessage()
{
 
    cout<< message <<endl;
    
}
