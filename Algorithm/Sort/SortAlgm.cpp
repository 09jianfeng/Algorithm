//
//  SortAlgm.cpp
//  Algorithm
//
//  Created by JFChen on 2018/2/27.
//  Copyright © 2018年 JFChen. All rights reserved.
//

#include "SortAlgm.hpp"
#include <stdexcept>
#include <exception>

SortAlgm::SortAlgm(void){
    
}

SortAlgm::~SortAlgm(void){
    
}

//快速排序

int randowInRange(int start, int end){
    return random()%(end - start)+start;
}

void swapData(int *a, int *b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int partition(int data[], int length, int start, int end){
    if (data == nullptr || length <= 0 || start < 0 || end >= length) {
        throw new std::exception();
        return -1;
    }
    
    int index = randowInRange(start,end);
    swapData(&data[index], &data[end]);
    int small = start -1;
    for (index = start; index < end; index++) {
        if (data[index] < data[end]) {
            small++;
            if (index != small) {
                swapData(&data[small], &data[index]);
            }
        }
    }
    
    ++small;
    swapData(&data[small], &data[end]);
    return small;
}

void quickSort_in(int data[], int length, int start, int end){
    if (start == end) {
        return;
    }
    
    int index = partition(data, length, start, end);
    if (index > start) {
        quickSort_in(data, length, start, index -1);
    }
    
    if(index < end){
        quickSort_in(data, length, index + 1, end);
    }
}

void SortAlgm::quickSort(int data[], int length){
    
}


//归并排序
void SortAlgm::mergingSort(int data[], int length){
    
}

//桶排序
void SortAlgm::bucketSort(int data[], int length){
    
}
