//
//  Observer.hpp
//  Algorithm
//
//  Created by JFChen on 2017/12/17.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#ifndef Observer_hpp
#define Observer_hpp

#include <stdio.h>
#include "Subject.hpp"
#include <string>

class Observer {
    
public:
    Observer();
    virtual ~Observer();
    virtual void update(Subject *sub) = 0;
    
private:
    string m_objName;
    int m_obeserverState;
};

#endif /* Observer_hpp */
