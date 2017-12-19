//
//  BinTreeAlgorithm.hpp
//  Algorithm
//
//  Created by JFChen on 17/3/6.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#ifndef BinTreeAlgorithm_hpp
#define BinTreeAlgorithm_hpp

#include <stdio.h>

#endif /* BinTreeAlgorithm_hpp */

typedef char BinNodeDataType;

typedef struct BinNode{
    BinNodeDataType data;
    BinNode *leftTree;
    BinNode *rightTree;
}BinNode;

typedef BinNode* BinTree;

class BinaryTreeAlgm {

private:
    BinTree binTree;
    
public:
    BinaryTreeAlgm(BinNodeDataType *node, int length);
    ~BinaryTreeAlgm(void);
    
    void preOrderRead(void);
    void midOrderRead(void);
    void lastOrderReaad(void);
};
