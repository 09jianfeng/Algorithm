//
//  main.m
//  Algorithm
//
//  Created by JFChen on 17/3/6.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "BinaryTreeAlgm.h"
#include "SortAlgm.hpp"
#include <iostream>
#include "FruitStream.hpp"
#include "interview_algorithm.hpp"

using namespace std;

void testCPlusPlusDesign(){
    testFruit();
}

void testNormalAlgorithm(){
    /* binTree
     char binPreOrder[22] = "abdglm1234zehnocfxijk";
     char binMidOrder[22] = "lgm3241dzbenhoaxfjikc";
     
     BinaryTreeAlgm *binTree = new BinaryTreeAlgm(binPreOrder, 21, binMidOrder, 21);
     binTree->preOrderRead();
     binTree->midOrderRead();
     binTree->lastOrderRead();
     */
    
    int arr[15] = {4,5,3,4,6,5,34,54,23,65,3,43,7,78,55};
    int len = 15;
    SortAlgm *sortAl = new SortAlgm();
    sortAl->headSort(arr, len);
    
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

void testAlgorithm(){
    Solution so;
    std::vector<int> num_vec = {1,2,3,4,5,1,2,3,4};
    int singleValue = so.singleNumber(num_vec);
    printf("\n siglevalue:%d \n", singleValue);
}

int main(int argc, const char * argv[]) {
    
    @autoreleasepool {
        //testCPlusPlus();
        
        testAlgorithm();
    }
    return 0;
}
