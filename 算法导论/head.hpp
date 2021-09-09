//
//  head.hpp
//  算法导论
//
//  Created by a magic neko on 2021/4/21.
//

#ifndef head_hpp
#define head_hpp

//#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <limits>
template <class T> class Stack{
private:
    struct node{
        T val;
        node* next;
    };
    node* top;
public:
    Stack(){
        top = NULL;
    }

    void push(T key){
        node* p = new node;
        p -> val = key;
        p -> next = top;
        top = p;
    }
    T pop(){
        if(top == NULL)
            throw "underflow";
        else{
            T tmp = top -> val;
            node* t = top -> next;
            delete top;
            top = t;
            return tmp;
        }
    }
    bool isempty(){
        return top == NULL;
    }
    ~Stack(){
        node* tmp;
        while(top != NULL){
            tmp = top;
            top = top -> next;
            delete tmp;
        }
    }
};
#endif /* head_hpp */
