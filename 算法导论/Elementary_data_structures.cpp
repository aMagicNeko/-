//
//  Elementary_data_structures.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/15.
//

#include "head.hpp"
using namespace std;
class stack{
private:
    int* p;
    const int size;
    int top;
public:
    stack(int s):size(s){
        p = new int[size];
        top = 0;
    }
    void push(int x){
        if(top == size)
            throw "overflow";
        else{
            p[top++] = x;
        }
    }
    int pop(){
        if(top == 0)
            throw "underflow";
        else{
            return p[--top];
        }
    }
    ~stack(){
        delete [] p;
    }
};

class queue{
private:
    int* p;
    const int size;
    int head;
    int tail;
    int len;
public:
    queue(int s):size(s){//close interval
        p = new int[s];
        head = 0;
        tail = -1;
        len = 0;
    }
    void enqueue(int x){
        if(len == size)
            throw "overflow";
        if(tail != size - 1){
            p[++tail] = x;
        }
        else{
            tail = 0;
            p[0] = x;
        }
        len++;
    }
    int dequeue(){
        if(len == 0)
            throw "underflow";
        len--;
        if(head == size - 1){
            head = 0;
            return p[size - 1];
        }
        else{
            return p[head++];
        }
    }
    ~queue(){
        delete [] p;
    }
};

class node{
public:
    node* prev;
    node* next;
    int key;
    node(int k = -1){
        prev = NULL;
        next = NULL;
        key = k;
    }
};

class list{
private:
    node* head;
    node* tail;
public:
    list(){
        head = new node;//sentinel
        tail = new node;//sentinel
        head -> next = tail;
        tail -> prev = head;
    }
    void insert(node &x){
        x.prev = head;
        x.next = head->next;
        head->next = &x;
        x.next->prev = &x;

    }
    void del(node &x){
        x.prev -> next = x.next;
        x.next -> prev = x.prev;
    }
    node* search(const int& k){
        node* p = head -> next;
        while(p != tail){
            if(p -> key == k)
                return p;
            p = p -> next;
        }
        return NULL;
    }
    ~list(){
        delete head;
        delete tail;
    }
};

class LCRStree{
private:
    struct node{
        node* p;
        node* lc;
        node* rs;
        int key;
        node(int k){
            p = lc = rs = NULL;
            key = k;
        }
    };
    node* root;
public:
    LCRStree(){
        root = NULL;
    }
    void insert(int k){
        
    }
};
/*
int main(){
    stack s(5);
    int arr[5]{1,2,4,5,1};
    for(int i = 0; i < 5; i++)
        s.push(arr[i]);
    for(int i = 0; i < 5; i++)
        cout<<s.pop()<<' ';
    //s.pop();
    queue q(5);
    for(int i = 0; i < 5; i++)
        q.enqueue(arr[i]);
    //q.enqueue(0);
    for(int i = 0; i < 5; i++)
        cout<<q.dequeue();
    //q.dequeue();
    int arr1[4]{5,1,2,4};
    for(int i = 0; i < 4; i++)
        q.enqueue(arr1[i]);
    q.enqueue(10);
    for(int i = 0; i < 5; i++)
        cout<<q.dequeue();
    list l;
    node n[5];
    for(int i=0;i<5;i++)
        n[i].key = i;
    cout<<(NULL==l.search(11))<<endl;
    for(int i = 0; i < 5; i++){
        cout<<l.search(i)->key<<endl;
    }
}

*/
