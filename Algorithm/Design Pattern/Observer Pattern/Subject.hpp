//
//  Subject.hpp
//  Algorithm
//
//  Created by JFChen on 2017/12/17.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#ifndef Subject_hpp
#define Subject_hpp

#include <stdio.h>
#include "Observer.hpp"
#include <vector>

class Subject {
    
public:
    Subject();
    virtual ~Subject();
    Observer *m_observer;
    
    void attach(Observer *observer);
    void detach(Observer *observer);
    
    void notify();
    virtual void setState(int state) = 0;
    virtual int  getState() = 0;
    
private:
    std::vector<Observer *> m_vtObj;
};

#endif /* Subject_hpp */
