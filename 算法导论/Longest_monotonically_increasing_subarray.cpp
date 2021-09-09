//
//  Longest_monotonically_increasing_subarray.cpp
//  算法导论
//
//  Created by Ekko on 2021/8/9.
//

#include "head.hpp"
using namespace std;
template<class T>class node{
public:
    node<T>* next;
    T val;
    int order;
    node(T& v):val(v){next = NULL;}
};
template<class T>class list{
private:
    class sentinel{
    public:
        node<T>* next;
    };
    sentinel* head;
public:
    list(){
        head = new sentinel;//sentinel
        head -> next = NULL;
    }
    void insert(T key, int o){
        node<T>* x = new node<T>(key);
        x -> next = head -> next;
        head -> next = x;
        x -> order = o;
    }
    node<T>* search(T key, int i){
        node<T>* p = head -> next;
        while(p != NULL){
            if(p -> val <= key && p -> order < i)
                return p;
            p = p -> next;
        }
        throw"error";
    }
    node<T>* show()const{
        return head -> next;
    }
    ~list(){
        delete head;
    }
};
template<class T> int binary_search(T* arr, int n, T key){
    int l = 0;
    int r = n - 1;
    int m = (l+r)/2;
    while(m != l){
        if(arr[m] <= key){
            l = m;
        }
        else{
            r = m;
        }
        m = (l + r) / 2;
    }
    if(arr[l] > key) return l;
    return r;
}
template<class T>
Stack<T>* find_LMIS(T* arr, int n){
    list<T> l[n];//ith elements of subarrays
    T last[n];//minimum of the last element of subarrays of a certain length
    last[0] = arr[0];
    l[0].insert(last[0], 0);
    int k = 0;
    int j = 0;
    for(int i = 1; i < n; i++){
        if(arr[i] >= last[k]){
            l[++k].insert(arr[i], i);
            last[k] = arr[i];
        }
        else{
            j = binary_search<T>(last, k + 1, arr[i]);
            last[j] = arr[i];
            l[j].insert(arr[i], i);
        }
    }
    Stack<T>*res = new Stack<T>;
    node<T>* p = l[k].show();
    int i = p -> order;
    T now = p -> val;
    res -> push(now);
    while(k > 0){
        k--;
        p = l[k].search(now, i);
        now = p -> val;
        i = p -> order;
        res -> push(now);
    }
    return res;
}
/*
int main(){
    int arr[]{3,1,5,4,2,6,2,3,5,1,4,2};
    auto s = find_LMIS<int>(arr,12);
    while(!s -> isempty())
        cout<< s -> pop();
}
*/
