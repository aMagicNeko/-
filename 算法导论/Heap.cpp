//
//  Heap.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/10.
//

#include "head.hpp"
#include <limits>
using namespace std;

class heap{//Max Heap, if n = length, leaves: [n/2],...,n-1, height: [lgn]
private:
    int* data;
    const int size;
    int length;
public:
    heap(int* arr, int num):size(num), length(num), data(arr){}
    ~heap(){}
    int left(int i);
    int right(int i);
    int parent(int i);
    void heapify(int i);//top-down, time complexity: O(lgn)
    void buld_heap();//bottom-up, time complexity:O(n)
    int pop();//O(lgn)
    void change_key(int i, int key);
    void insert(int key);
    void del(int i);
    
};

int heap::left(int i){
    return 2*i+1;
}
int heap::right(int i){
    return 2*i+2;
}
int heap::parent(int i){
    return (i-1)/2;
}
void heap::heapify(int i){
    int key = data[i];
    int mindex = i;
    int l;
    int r;
    while(true){
        l = left(i);
        r = right(i);
        if(l < length && key < data[l])
            mindex = l;
        if(r < length && data[mindex] < data[r])
            mindex = r;
        if(mindex == i){
            return;
        }
        data[i] = data[mindex];
        i = mindex;
        data[i] = key;
    }
}

void heap::buld_heap(){
    for(int i = length/2-1;i >= 0;i--){
        heapify(i);
    }
}

int heap::pop(){
    int key = data[0];
    data[0] = data[length-1];
    data[length-1] = key;
    length--;
    heapify(0);
    return key;
}

void heap::change_key(int i, int key){
    if(key < data[i]){
        data[i] = key;
        heapify(i);
    }
    else{//increase key, bottom-up
        int p;
        while(true){
            if(i == 0){
                data[i] = key;
                return;}
            p = parent(i);
            if(data[p] < key){
                data[i] = data[p];
                i = p;
            }
            else{
                data[i] = key;
                return;}
        }
    }
}

void heap::insert(int key){
    if(length+1 > size)
        throw "out of size";
    length++;
    data[length-1] = numeric_limits<int>::min();
    change_key(length-1, key);
}

void heap::del(int i){
    length--;
    change_key(i , data[length]);
}


/*
int main(){
    int arr[10]{5,6,1,24,5,6,2,62,25,2};
    heap h(arr, 10);
    h.buld_heap();
    //for(int i=0; i < 10; i++)
        //cout<<h.pop()<<" ";
    h.pop();
    h.insert(-1);
    for(int i=0; i < 10; i++)
        cout<<h.pop()<<" ";
}

*/

