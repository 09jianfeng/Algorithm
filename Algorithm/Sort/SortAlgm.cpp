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
/*
 效率最高的排序算法，时间复杂度 nlogn.
 算法思想：
  找个哨兵，遍历数组数据。大的放在哨兵的右边，小的放在哨兵左边。哨兵作为分界点，分为左边/右边子数组。
  递归子数组。
 */

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
    quickSort_in(data, length, 0, length - 1);
}


//归并排序
/*
 时间复杂度：nlogn
 算法思想：
  把数组分为左右子数组。分别把左右子数组排好序。然后在合并左右数组
 */

void mergeSort(int data[], int length ,int start, int end){
    if (start == end) {
        return;
    }
    
    int mid = (end + start)/2;
    mergeSort(data, length, start, mid);
    mergeSort(data, length, mid+1, end);
    
    int left = start;
    int right = mid + 1;
    // One extra check:  can we SKIP the merge?
    if ( data[mid] <= data[right])
        return;
    
    while (left <= mid && right <= end)
    {  // Select from left:  no change, just advance left
        if ( data[left] <= data[right])
            left++;
        // Select from right:  rotate [left..right] and correct
        else
        {
            int tmp = data[right];     // Will move to [left]
//            System.arraycopy(data, left, data, left+1, right-left);
            for (int i = right; i <= right - left; i--) {
            }
            data[left] = tmp;
            // EVERYTHING has moved up by one
            left++;  mid++;  right++;
        }
    }
    // Whatever remains in [right..last] is in place
}

void SortAlgm::mergingSort(int data[], int length){
    
}

//桶排序
void SortAlgm::bucketSort(int data[], int length){
    
}
