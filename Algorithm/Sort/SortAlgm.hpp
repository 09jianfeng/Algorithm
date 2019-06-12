//
//  SortAlgm.hpp
//  Algorithm
//
//  Created by JFChen on 2018/2/27.
//  Copyright © 2018年 JFChen. All rights reserved.
//

#pragma once

#include <stdio.h>

class SortAlgm {
public:
    
    SortAlgm(void);
    virtual ~SortAlgm(void);
    
    //快速排序
    void quickSort(int data[], int length);
    //归并排序
    void mergingSort(int data[], int length);
    //桶排序
    void bucketSort(int data[], int length);
    //堆排序
    void headSort(int data[], int length);
    
};
