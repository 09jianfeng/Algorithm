//
//  BinTreeAlgorithm.cpp
//  Algorithm
//
//  Created by JFChen on 17/3/6.
//  Copyright © 2017年 JFChen. All rights reserved.
//

#include <stdlib.h>
#include "BinaryTreeAlgm.h"
#include <stack>

/*
 * 返回这个二叉树的根节点。
 * 输入二叉树的前序遍历跟中序遍历的数组来创建二叉树。    一定要注意数组的边界条件
 * 前序遍历的第一个节点是根节点，把中序遍历的数组分为这个根节点的左子树跟右子树。
 * 根据中序遍历平分的左右子树，把前序遍历的数组也分为左右子树。
 * 然后不断递归左右子树，子树们返回的根节点就是当前节点的左右子树。
 * 要注意最后剩下2个节点的时候的边界条件。
 */
BinNode* createBinTree(BinNodeDataType *nodePreOrder, int len, BinNodeDataType *nodeMidOrder){
    //输入异常判断
    if (!nodePreOrder || !nodeMidOrder || len <= 0) {
        return nullptr;
    }
    
    BinNode *root = new BinNode;
    root->data = nodePreOrder[0];//前序的第一个就是根节点
    printf("%c",root->data);
    
    //只有一个节点的话返回，递归返回条件
    if (len == 1) {
        root->leftTree = nullptr;
        root->rightTree = nullptr;
        return root;
    }
    
    //递归主体
    int rootDataIndexMid = 0;
    for (; rootDataIndexMid < len; rootDataIndexMid++) {
        //找到中序遍历中的根节点位置
        if (nodeMidOrder[rootDataIndexMid] == root->data) {
            break;
        }
    }
    BinNodeDataType *leftMidOder = nodeMidOrder;
    BinNodeDataType *righMidOder = nodeMidOrder + rootDataIndexMid + 1;
    // 这里要注意右子树的边界条件，如果只有2个节点，右子树是不一定存在的。
    if (righMidOder >= nodeMidOrder + len) {
        righMidOder = nullptr;
    }
    
    BinNodeDataType *leftPreOder = nodePreOrder + 1;
    BinNodeDataType *righPreOder = nodePreOrder + rootDataIndexMid + 1;
    //// 这里要注意右子树的边界条件，如果只有2个节点。右子树是不一定存在的。
    if (righPreOder >= nodePreOrder + len) {
        righPreOder = nullptr;
    }
    
    //剩下两个节点的时候
    if (rootDataIndexMid == 0) {
        leftPreOder = nullptr;
        leftMidOder = nullptr;
    }
    
    BinNode *left = createBinTree(leftPreOder, rootDataIndexMid, leftMidOder);
    BinNode *right = createBinTree(righPreOder, len - rootDataIndexMid - 1, righMidOder);
    root->leftTree = left;
    root->rightTree = right;
    
    return root;
}

BinaryTreeAlgm::BinaryTreeAlgm(BinNodeDataType *nodePreOrder, int preLen, BinNodeDataType *nodeMidOrder, int midLen){
    if (!nodePreOrder || !nodeMidOrder || preLen <= 0 | preLen != midLen) {
        return;
    }
    
    _binTree = createBinTree(nodePreOrder, preLen, nodeMidOrder);
}

BinaryTreeAlgm::~BinaryTreeAlgm(){
    
}

#pragma mark - 前序遍历
/*
 * 递归实现的方法简单。
 */
void bintreePreReadRecursion(BinNode *tree){
    if (!tree) {
        return;
    }
    printf("%c",tree->data);
    bintreePreReadRecursion(tree->leftTree);
    bintreePreReadRecursion(tree->rightTree);
}

/*
 * 前序是入栈的时候打印
 */
void bintreePreReadStack(BinNode *tree){
    if (!tree) {
        return;
    }
    
    std::stack<BinNode *> nodeStack;
    nodeStack.push(tree);
    BinNode *node = tree;
    while (!nodeStack.empty()) {
        //不断入堆左子树
        while (node) {
            printf("%c",node->data);
            node = node->leftTree;
            if (node) {
                nodeStack.push(node);
            }
        }
        
        node = nodeStack.top();
        nodeStack.pop();
        //如果右子树为空，就不断出堆栈。直到右子树不为空。
        while (!nodeStack.empty() && !node->rightTree) {
            node = nodeStack.top();
            nodeStack.pop();
        }
        
        node = node->rightTree;
        if (node) {
            nodeStack.push(node);
        }
    }
}

void BinaryTreeAlgm::preOrderRead(void){
    printf("\npreOrderRead: ");
    bintreePreReadRecursion(_binTree);
    printf("\n");
    bintreePreReadStack(_binTree);
    printf("\n");
    
}

#pragma mark - 中序遍历
void bintreeMidReadRecursion(BinNode *tree){
    if (!tree) {
        return;
    }
    
    bintreeMidReadRecursion(tree->leftTree);
    printf("%c",tree->data);
    bintreeMidReadRecursion(tree->rightTree);
}

/*
 * 中序是出栈的时候打印
 */
void bintreeMidReadStack(BinNode *tree){
    if (!tree) {
        return;
    }
    
    std::stack<BinNode *> nodeStack;
    nodeStack.push(tree);
    BinNode *node = tree;
    while (!nodeStack.empty()) {
        //不断入堆左子树
        while (node) {
            node = node->leftTree;
            if (node) {
                nodeStack.push(node);
            }
        }
        
        node = nodeStack.top();
        nodeStack.pop();
        printf("%c",node->data);
        //如果右子树为空，就不断出堆栈。直到右子树不为空。
        while (!nodeStack.empty() && !node->rightTree) {
            node = nodeStack.top();
            nodeStack.pop();
            printf("%c",node->data);
        }
        
        node = node->rightTree;
        if (node) {
            nodeStack.push(node);
        }
    }
}

void BinaryTreeAlgm::midOrderRead(void){
    printf("\nmidOrderRead: ");
    bintreeMidReadRecursion(_binTree);
    printf("\n");
    bintreeMidReadStack(_binTree);
    printf("\n");
}

#pragma mark - 后序遍历
void bintreeLastReadRecursion(BinNode *tree){
    if (!tree) {
        return;
    }
    
    bintreeLastReadRecursion(tree->leftTree);
    bintreeLastReadRecursion(tree->rightTree);
    printf("%c",tree->data);
}


//后序遍历需要额外引入堆栈保持状态。
void bintreeLastReadStact(BinNode *tree){
    if (!tree) {
        return;
    }
    
    std::stack<BinNode *> nodeStack;
    std::stack<BinNode *> markStack;
    
    nodeStack.push(tree);
    BinNode *node = tree;
    while (!nodeStack.empty()) {
        //不断入堆左子树
        while (node) {
            node = node->leftTree;
            if (node) {
                nodeStack.push(node);
            }
        }
        
        node = nodeStack.top();
        nodeStack.pop();
        while (!nodeStack.empty() && !node->rightTree) {
            printf("%c",node->data);
            
            node = nodeStack.top();
            nodeStack.pop();
        }
        
        //每次回溯节点的时候，有子节点的节点都需要标记保存
        while (node->rightTree || node->leftTree) {
            
            //回溯的过程中要考虑只有左子树或者只有右子树的情况。
            if (!markStack.empty()) {
                BinNode *markNode = markStack.top();
                //只要是回溯的节点，判断是否在mark堆栈里面。
                if (markNode->data == node->data) {
                    markStack.pop();
                    
                    printf("%c",node->data);
                    
                    if (nodeStack.empty()) {
                        break;
                    }
                    node = nodeStack.top();
                    nodeStack.pop();
                }else{
                    //当节点回溯的过程中，如果出栈的节点没有右子树，直接出栈，并且输出
                    if (!node->rightTree) {
                        printf("%c",node->data);
                        node = nodeStack.top();
                        nodeStack.pop();
                    }else{
                        markStack.push(node);
                        nodeStack.push(node);
                        node = node->rightTree;
                        nodeStack.push(node);
                        break;
                    }
                }
            }
            else{
                
                //当节点回溯的过程中，如果出栈的节点没有右子树，直接出栈，并且输出
                if (!node->rightTree) {
                    printf("%c",node->data);
                    node = nodeStack.top();
                    nodeStack.pop();
                }else{
                    markStack.push(node);
                    nodeStack.push(node);
                    node = node->rightTree;
                    nodeStack.push(node);
                    break;
                }
                
            }
        }
    }
}



void BinaryTreeAlgm::lastOrderRead(void){
    printf("\nlastOrderRead: ");
    bintreeLastReadRecursion(_binTree);
    printf("\n");
    bintreeLastReadStact(_binTree);
    printf("\n");
    
}
