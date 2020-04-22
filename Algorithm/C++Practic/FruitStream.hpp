//
//  FruitStream.hpp
//  Algorithm
//
//  Created by JFChen on 2019/9/21.
//  Copyright © 2019 JFChen. All rights reserved.
//

#ifndef FruitStream_hpp
#define FruitStream_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
/*
 这里主要是练习友元函数.
 也就是声明这个函数是我这个类的朋友，可以把这个函数当自己人。可以访问我私有成员变量
 */
class Fruit{
    string name;
    string colour;
    
public:
    /*
     友元：参考https://blog.csdn.net/jackychu/article/details/3020866
     也就是声明这个函数是我这个类的朋友，可以把这个函数当自己人。可以访问我私有成员变量
     */
    friend istream& operator>> (istream& , Fruit &);
    friend ostream& operator<< (ostream& , Fruit &);
    
    void print(){
        cout << colour << " " << name << endl;
    }
    
    Fruit(const string &nstr = "apple", const string &cst = "red"):name(nstr),colour(cst){
        
    }
    
    virtual ~Fruit(){
    }
};

/*
 重载输入输出符号，不能在类里面
 */
ostream& operator<< (ostream& out, Fruit &fruit){
    out << "color" <<fruit.colour << "name" << fruit.name;
    return out;
}

istream& operator>> (istream& in, Fruit &fruit){
    in >> fruit.colour >> fruit.name;
    if (!in) {
        cerr << "wrong input" << endl;
    }
    
    return in;
}

void testFruit(){
    Fruit apple;
    cin >> apple;
    cout << apple;
}

void fileReading(){
    char ch;
    fstream openfile("xxxxxx", ios::out); //ios::out是模式，表示以什么模式来使用这个文件。这个是表示从文件输出。
    while (openfile.eof()) {
        cout << "file  is not open." << endl;
        exit(1);
    }
    
    while(openfile.eof()){ //判断是否到了文件末尾，不断的从文件读取数据出来。
        openfile.get(ch);
        cout <<  ch;
    }
    
    openfile.close();
}


/*
 下面这个模板用于练习模板参数化，连维度也可以参数化
 */
template < class type, int dim >
class Point3D{
private:
    type _coordins[ dim ];
public:
    Point3D();
    Point3D(type coordins[dim]){
        for(int i = 0; i < dim ; i++){
            _coordins[i] = coordins[i];
        }
    }
    
    //set
    type &operator[](int index){
        assert( index < dim && index >= 0);
        return _coordins[index];
    }
    
    //get
    type operator[](int index) const{
        assert(index < dim && index >= 0);
        return _coordins[index];
    }
};

template < class type, int dim >
ostream& operator << (ostream &os, const Point3D< type, dim > &ptr){
    os << "(";
    for (int i = 0; i < dim - 1; i++){
        os << ptr[i] << ",";
    os << ptr[dim-1];
        os << " ) ";
    }
};

#endif /* FruitStream_hpp */
