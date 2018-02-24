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
        char binPreOrder[22] = "abdglm1234zehnocfxijk";
        char binMidOrder[22] = "lgm3241dzbenhoaxfjikc";
//        char binPreOrder[3] = "ab";
//        char binMidOrder[3] = "ba";
        
        BinaryTreeAlgm *binTree = new BinaryTreeAlgm(binPreOrder, 21, binMidOrder, 21);
        binTree->preOrderRead();
        binTree->midOrderRead();
        binTree->lastOrderRead();
    }
    return 0;
}
