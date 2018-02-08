//
//  main.m
//  Algorithm
//
//  Created by JFChen on 17/3/6.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "BinaryTreeAlgm.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        char binPreOrder[18] = "abdglmzehnocfxijk";
        char binMidOrder[18] = "lgmdzbenhoaxfjikc";
        
        BinaryTreeAlgm *binTree = new BinaryTreeAlgm(binPreOrder, 17, binMidOrder, 17);
        binTree->preOrderRead();
        binTree->midOrderRead();
        binTree->lastOrderRead();
    }
    return 0;
}
