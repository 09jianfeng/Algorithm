//
//  Subject.h
//  Algorithm
//
//  Created by JFChen on 2017/12/27.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#ifndef Subject_h
#define Subject_h

#include "Observer.h"
#include <vector>

using namespace std;

class Subject {
public:
    virtual void attach(Observer *obs)=0;
    virtual void detach(Observer *obs)=0;
    virtual void notify()=0;
    
private:
    vector<Observer*> m_vtobj;
};

#endif /* Subject_h */
