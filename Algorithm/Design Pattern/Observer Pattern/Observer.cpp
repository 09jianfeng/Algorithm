//
//  Observer.cpp
//  Algorithm
//
//  Created by JFChen on 2017/12/17.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#include "Observer.hpp"
#include <iostream>
#include <vector>
#include "Subject.h"
using namespace std;

ConcreteObeserver::ConcreteObeserver(string name){
    m_objName = name;
}

ConcreteObeserver::~ConcreteObeserver(){
    
}

void ConcreteObeserver::update(Subject * sub){
    m_obeserverState = sub->getState();
    cout << "update oberserver[" << m_objName << "] state:" << m_obeserverState << endl;
}
