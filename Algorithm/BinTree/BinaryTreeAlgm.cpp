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
 * 前序是入栈的时候打印。
 * 不断入栈左子树，入完了左子树。赋值右子树，作为下一棵树进入下一次循环。
 */
void bintreePreReadStack(BinNode *tree){
    if (!tree) {
        return;
    }
    
    std::stack<BinNode *> nodeStack;
    BinNode *node = tree;
    while (!nodeStack.empty() || node) {
        //不断入堆左子树
        //边打印边入栈，以后还要借助这些根节点，进入右子树
        while (node) {
            printf("%c",node->data);
            
            nodeStack.push(node);
            node = node->leftTree;
        }
        
        //只要堆栈不为空，就继续. 左子树遍历完了，就该轮到右子树作为根节点继续了。
        if (!nodeStack.empty()) {
            node = nodeStack.top();
            nodeStack.pop();
            node = node->rightTree;
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
 * 中序是出栈的时候打印。 算法主体跟前序遍历的主体一样。
 * 不断入栈左子树，入完了左子树。赋值右子树，作为下一棵树进入下一次循环。
 */
void bintreeMidReadStack(BinNode *tree){
    if (!tree) {
        return;
    }
    
    std::stack<BinNode *> nodeStack;
    BinNode *node = tree;
    while (!nodeStack.empty() || node) {
        //不断入堆左子树
        //边打印边入栈，以后还要借助这些根节点，进入右子树
        while (node) {
            nodeStack.push(node);
            node = node->leftTree;
        }
        
        //只要堆栈不为空，就继续. 左子树遍历完了，就该轮到右子树作为根节点继续了。
        if (!nodeStack.empty()) {
            
            node = nodeStack.top();
            
            //中序遍历是在出栈的时候打印。
            printf("%c",node->data);
            nodeStack.pop();
            node = node->rightTree;
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


//后序遍历
/*
 后序遍历递归定义：先左子树，后右子树，再根节点。后序遍历的难点在于：需要判断上次访问的节点是位于左子树，还是右子树。
 若是位于左子树，则需跳过根节点，先进入右子树，再回头访问根节点；
 若是位于右子树，则直接访问根节点。
 */
void bintreeLastReadStact(BinNode* root)
{
    if (root == NULL)
        return;
    std::stack<BinNode*> s;
    //pCur:当前访问节点，pLastVisit:上次访问节点
    BinNode* pCur, *pLastVisit;
    //pCur = root;
    pCur = root;
    pLastVisit = NULL;
    
    //先把pCur移动到左子树最下边
    while (pCur)
    {
        s.push(pCur);
        pCur = pCur->leftTree;
    }
    
    while (!s.empty())
    {
        //走到这里，pCur都是空，并已经遍历到左子树底端(看成扩充二叉树，则空，亦是某棵树的左孩子)
        pCur = s.top();
        s.pop();
        //一个根节点被访问的前提是：无右子树或右子树已被访问过
        if (pCur->rightTree == NULL || pCur->rightTree == pLastVisit)
        {
            printf("%c",pCur->data);
            //修改最近被访问的节点
            pLastVisit = pCur;
        }
        
        /*这里的else语句可换成带条件的else if:
         else if (pCur->lchild == pLastVisit)//若左子树刚被访问过，则需先进入右子树(根节点需再次入栈)
         因为：上面的条件没通过就一定是下面的条件满足。仔细想想！
         */
        else
        {
            //根节点再次入栈
            s.push(pCur);
            //进入右子树，且可肯定右子树一定不为空
            pCur = pCur->rightTree;
            while (pCur)
            {
                s.push(pCur);
                pCur = pCur->leftTree;
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
