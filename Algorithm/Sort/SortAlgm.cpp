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
#include <algorithm>

using namespace std;

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


/*
 * 1、父节点跟两个子节点比较，跟大的子节点交换。
 * 2、检查变化后的子节点，使其符合大/小顶堆的规则。
 */
void max_heapify(int arr[], int start, int end) {
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { //若子节点指标在范围内才做比较
        if (son + 1 <= end && arr[son] < arr[son + 1]) //先比较两个子节点大小，选择最大的
            son++;
        if (arr[dad] > arr[son]) //如果父节点大於子节点代表调整完毕，直接跳出函数
            return;
        else { //否则交换父子内容再继续子节点和孙节点比较
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}


/*
 * 1、先建立初始堆
 * 2、根节点跟最后的一个节点交换。
 * 3、重建堆，使堆符合大顶堆或者小顶堆。
 * 4、对剩下还没排序的节点重复2、3步骤。
 */
void heap_sort(int arr[], int len) {
    //初始化，i从最後一个父节点开始调整。调整完所有的父节点，建立初始堆
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    
    
    //先将第一个元素和已经排好的元素前一位做交换，再从新调整(刚调整的元素之前的元素)，直到排序完毕
    for (int i = len - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}


void SortAlgm::headSort(int data[], int length){
    heap_sort(data, length);
}

