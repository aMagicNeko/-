//
//  insertion_sort.cpp
//  算法导论
//
//  Created by a magic neko on 2021/6/5.
//

#include "../head.hpp"

using namespace std;

void insertion_sort(int* A, int len)//From small to large
{
    int n = 0;
    int key;
    int i;
    while(n < len-1){
        i = n;
        n++;
        key = A[n];
        while(key < A[i] && i >= 0){
            A[i+1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
    return;
}
/*
int main(){
    int A[10]{4,2,10,1,7,2,5,1,7,8};
    insertion_sort(A, 10);
    for(int i = 0; i < 10; i++){
        cout<<A[i];
    }
}
*/
