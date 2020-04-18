//
//  interview_algorithm.hpp
//  Algorithm
//
//  Created by JFChen on 2020/4/16.
//  Copyright © 2020 JFChen. All rights reserved.
//

#ifndef interview_algorithm_hpp
#define interview_algorithm_hpp

#include <stdio.h>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class interview_algorithm {
    
public:
};


/*
 string的使用
 接口有： c_str(); size(); append(); push_back()这个函数只能添加1个字符;
 */
class thirtySixStepPlus {
public:
    //36进制加法,要考虑正负数的情况
    void thirtyPlus(string a, string b, string &out){
        const char *a_char =  a.c_str();
        const char *b_char = b.c_str();
        stack<char> outStack;
        
        bool isNagivatev = false;
        bool sameSign = true;
        if (a_char[0] == '-' && b_char[0] == '-') {
            isNagivatev = true;
            sameSign = true;
        }else if (a_char[0] != '-' && b_char[0] != '-'){
            isNagivatev = false;
            sameSign = true;
        }else{
            sameSign = false;
            if (a_char[0] == '-') {
                   int v = compareValue(&a_char[0], b_char);
                if (v == 1 ) {
                    isNagivatev = true;
                }else if(v == -1){
                    isNagivatev = false;
                    const char *tmp = a_char;
                    a_char = b_char;
                    b_char = tmp;
                }else{
                    out = "0";
                    return;
                }
            }else{
                int v = compareValue(&a_char[0], b_char);
                if (v == 1 ) {
                    isNagivatev = false;
                }else if(v == -1){
                    isNagivatev = true;
                    const char *tmp = a_char;
                    a_char = b_char;
                    b_char = tmp;
                }else{
                    out = "0";
                    return;
                }
            }
        }
    }
    
    void inner_plus(string a, string b, string &out, bool isnagivate){
        //懒得写先。用一个进位标志，用stack来存储字符串。
    }
    
    //a must large than b
    void inner_sub(string a, string b, string &out, bool isnagivate){
        //懒得写先。用一个进位标志，用stack来存储字符串。
    }
    
    int compareValue(string a, string b){
        const char *a_char =  a.c_str();
        const char *b_char = b.c_str();
        if(a.size() > b.size()){
            return 1;
        }else if(a.size() < b.size()){
            return -1;
        }else{
            for    (int i = 0; i < b.size(); i++){
                if (a_char[i] - b_char[i] > 0) {
                    return 1;
                }else if(a_char[i] - b_char[i] < 0){
                    return -1;
                }
            }
        }
        
        return 0;
    }
};

//只出现一次的数字 用异或来解决
/*
 输入: [2,2,1]
 输出: 1
 */
class Solution {
public:
    /*
     vector 的方法有：
     初始化：std::vector<int> first;  std::vector<int> second (4,100); std::vector<int> third (second.begin(),second.end());  std::vector<int> fourth (third);
     clear(); shrink_to_fit();	注意：clear()+shrink_to_fit()用于释放vector，是C++ 11才有的特性。
     向量尾部增加一个元素push_back(); size(); 删除最后一个元素pop_back();
     
     assign、insert都是可以赋值好几个给vector，只有当vector为空的时候，assign和insert是相同的。如果vetor是空的，使用assign更好。
     */
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for(vector<int>::iterator iter = nums.begin(); iter != nums.end(); iter++){
            result = result ^ *iter;
        }
        return result;
    }
};

//对一个数组进行全排列，并且找出出现次数最多的那个元素
//全排列可以用递归的方法来做。
class arrayPermutation {
public:
    
    
};

#endif /* interview_algorithm_hpp */

















