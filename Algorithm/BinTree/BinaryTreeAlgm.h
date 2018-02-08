//
//  BinTreeAlgorithm.hpp
//  Algorithm
//
//  Created by JFChen on 17/3/6.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#pragma once
#include <stdio.h>

typedef char BinNodeDataType;

typedef struct BinNode{
    BinNodeDataType data;
    struct BinNode *leftTree;
    struct BinNode *rightTree;
}BinNode;

typedef BinNode* BinTree;

class BinaryTreeAlgm {

private:
    BinTree _binTree;
    
public:
    BinaryTreeAlgm(BinNodeDataType *nodePreOrder, int preLen, BinNodeDataType *nodeMidOrder, int midLen);
    ~BinaryTreeAlgm(void);
    
    void preOrderRead(void);
    void midOrderRead(void);
    void lastOrderRead(void);
};
